using System.Runtime.InteropServices;

namespace Amatelight
{
    class OSSTATE
    {
        // ==========================================
        // ① OS判定メソッド
        // ==========================================
        public static IAuditLogCollector DetectOS()
        {
            if (RuntimeInformation.IsOSPlatform(OSPlatform.Windows))    return new WindowsLogCollector();
            if (RuntimeInformation.IsOSPlatform(OSPlatform.Linux))      return new LinuxLogCollector();    
            return null;
        }
    }
}
