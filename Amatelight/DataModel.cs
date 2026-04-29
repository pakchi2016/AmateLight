using System;
using System.Collections.Generic;
using System.Text;

namespace Amatelight
{
    // ==========================================
    // ① 共通データモデル（美しい記入用紙）
    // ==========================================
    public record AuditLogEntry
    {
        public DateTime Timestamp { get; init; }
        public string AccountName { get; init; } = string.Empty;
        public string SourceIpOrHost { get; init; } = string.Empty;
        public string SessionId { get; init; } = string.Empty;
        public string LogonType { get; init; } = string.Empty;
        public bool IsSuccess { get; init; }
        public string ProcessName { get; init; } = string.Empty;
    }

    // ==========================================
    // ② 共通インターフェース（翻訳家への絶対の約束事）
    // ==========================================
    public interface IAuditLogCollector
    {
        // 「OSが何であれ、必ずAuditLogEntryのリスト形式で返しなさい」というルール
        List<AuditLogEntry> CollectLogs();
    }
}