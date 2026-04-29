using System.Runtime.InteropServices;

namespace Amatelight
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("ログ監査ミドルウェア MVP版の起動シーケンスを開始しますわ。");

            // ① OS判定メソッドの呼び出し
            IAuditLogCollector collector = OSSTATE.DetectOS();
            if(collector == null ) {
                Console.WriteLine("このOSはサポート対象外ですわ。");
                return;
            }

            List<AuditLogEntry> logs = collector.CollectLogs();

            // ③ テキスト出力メソッドの呼び出し
            OUTPUT.OutputToTextFile(logs, "AuditLog_Structured.txt");

            Console.WriteLine("\n処理が美しく完了いたしましたわ。");

            // Visual Studio等で実行した際にコンソールがすぐ閉じるのを防ぐため
            Console.ReadLine();
        }
    }
}