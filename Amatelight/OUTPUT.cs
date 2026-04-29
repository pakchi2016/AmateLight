using System;
using System.Collections.Generic;
using System.Text;

namespace Amatelight
{
    class OUTPUT
    {
        // ==========================================
        // ③ テキスト出力メソッド
        // ==========================================
        public static void OutputToTextFile(List<AuditLogEntry> content, string fileName)
        {
            // 実行ファイルと同じディレクトリに出力
            string filePath = Path.Combine(AppDomain.CurrentDomain.BaseDirectory, fileName);
            var sb = new StringBuilder();

            sb.AppendLine("=== 監査ログ抽出結果 ===");
            foreach (var log in content)
            {
                sb.AppendLine($"[{log.Timestamp:yyyy/MM/dd HH:mm:ss}] 成功:{log.IsSuccess}");
                sb.AppendLine($"  アカウント: {log.AccountName}");
                sb.AppendLine($"  接続元    : {log.SourceIpOrHost}");
                sb.AppendLine($"  経路/種別 : {log.LogonType}");
                sb.AppendLine($"  セッション: {log.SessionId}");
                sb.AppendLine($"  プロセス  : {log.ProcessName}");
                sb.AppendLine("------------------------");
            }

            File.WriteAllText(filePath, sb.ToString());
            Console.WriteLine($"\n以下のパスに構造化されたログを出力しましたわ:\n{filePath}");
            Console.WriteLine(sb.ToString());
        }
    }
}
