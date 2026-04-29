using System.Diagnostics;
using System.Diagnostics.Eventing.Reader;
using System.Xml.Linq;

namespace Amatelight
{
    // ==========================================
    // ③ OS専用コレクター（生ログの解読ロジック）
    // ==========================================
    public class WindowsLogCollector : IAuditLogCollector
    {
        public List<AuditLogEntry> CollectLogs()
        {
            var logs = new List<AuditLogEntry>();
            try
            {
                // セキュリティログから「ログオン成功 (EventID: 4624)」を最新順に取得
                string queryStr = "*[System[(EventID=4624)]]";
                using EventLogReader reader = new EventLogReader(new EventLogQuery("Security", PathType.LogName, queryStr) { ReverseDirection = true });

                int count = 0;
                // テスト用に最新の10件のみを抽出します
                for (EventRecord eventInstance = reader.ReadEvent(); eventInstance != null && count < 10; eventInstance = reader.ReadEvent())
                {
                    // イベントのXML表現から確実なキー名で値を抽出する美しいアプローチですわ
                    string xmlString = eventInstance.ToXml();
                    var doc = XDocument.Parse(xmlString);
                    XNamespace ns = "http://schemas.microsoft.com/win/2004/08/events/event";
                    var eventData = doc.Descendants(ns + "EventData").Elements(ns + "Data");

                    // 抽出用ローカル関数
                    string GetData(string name) => eventData.FirstOrDefault(x => (string?)x.Attribute("Name") == name)?.Value ?? "";

                    string targetUser = GetData("TargetUserName");

                    // 実運用向けの実装：システム（裏側）の自動ログイン等のノイズを除外します
                    if (targetUser.EndsWith("$") || targetUser == "SYSTEM" || targetUser == "DWM-1" || targetUser == "UMFD-0") continue;

                    string logonTypeStr = GetData("LogonType");
                    string logonType = logonTypeStr switch
                    {
                        "2" => "Interactive (コンソール直接)",
                        "3" => "Network (ネットワーク共有)",
                        "10" => "RemoteInteractive (RDP遠隔)",
                        _ => $"その他 (Type {logonTypeStr})"
                    };

                    logs.Add(new AuditLogEntry
                    {
                        Timestamp = eventInstance.TimeCreated ?? DateTime.Now,
                        AccountName = targetUser,
                        SourceIpOrHost = GetData("IpAddress"),
                        SessionId = GetData("TargetLogonId"),
                        LogonType = logonType,
                        IsSuccess = true,
                        ProcessName = GetData("ProcessName")
                    });

                    count++;
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine($"※Windowsログ取得エラー: {ex.Message}");
            }
            return logs;
        }
    }

    public class LinuxLogCollector : IAuditLogCollector
    {
        public List<AuditLogEntry> CollectLogs()
        {
            var logs = new List<AuditLogEntry>();
            try
            {
                // Linuxは 'last' コマンドに '-F (完全な日時表示)' と '-i (IP表示)' オプションを付与してパースの確実性を高めます
                var processInfo = new ProcessStartInfo
                {
                    FileName = "last",
                    Arguments = "-F -i -n 15",
                    RedirectStandardOutput = true,
                    UseShellExecute = false,
                    CreateNoWindow = true,
                };

                using var process = Process.Start(processInfo);
                if (process != null)
                {
                    string output = process.StandardOutput.ReadToEnd();
                    process.WaitForExit();

                    // 行ごとに分割
                    var lines = output.Split(new[] { '\r', '\n' }, StringSplitOptions.RemoveEmptyEntries);
                    foreach (var line in lines)
                    {
                        // システムログのフッターや空行はスキップ
                        if (line.StartsWith("wtmp begins") || line.StartsWith("reboot") || line.Trim().Length == 0) continue;

                        // 空白で分割 (例: root pts/0 192.168.1.10 Wed Apr 29 10:00:00 2026 ...)
                        var parts = line.Split(' ', StringSplitOptions.RemoveEmptyEntries);
                        if (parts.Length >= 8)
                        {
                            string account = parts[0];
                            string tty = parts[1];
                            string ipOrHost = parts[2] == "0.0.0.0" ? "Localhost" : parts[2];

                            // 端末情報からLogonTypeを推測しますわ
                            string logonType = tty.StartsWith("pts") ? "RemoteInteractive (SSH等の仮想端末)" : "Interactive (コンソール直接)";

                            // 分割された文字列から日時の部位を抽出し、C#のDateTime型へ組み立て直します
                            string timeStr = $"{parts[4]} {parts[5]} {parts[7]} {parts[6]}"; // 例: "Apr 29 2026 10:00:00"
                            DateTime.TryParseExact(timeStr, "MMM d yyyy HH:mm:ss", System.Globalization.CultureInfo.InvariantCulture, System.Globalization.DateTimeStyles.None, out DateTime timestamp);

                            logs.Add(new AuditLogEntry
                            {
                                Timestamp = timestamp,
                                AccountName = account,
                                SourceIpOrHost = ipOrHost,
                                SessionId = "N/A (lastコマンド制限)", // lastコマンドではセッションIDが出ないためMVPの代替値とします
                                LogonType = logonType,
                                IsSuccess = true,
                                ProcessName = "sshd / login"
                            });
                        }
                    }
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine($"※Linuxログ取得エラー: {ex.Message}");
            }
            return logs;
        }
    }
}
