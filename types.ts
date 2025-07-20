
export enum View {
  Dashboard = 'Dashboard',
  NetworkMonitor = 'Network Monitor',
  ThreatProtection = 'Threat Protection',
  AIAssistant = 'AI Assistant',
}

export interface ChatMessage {
  role: 'user' | 'model';
  content: string;
}

export interface NetworkLog {
  id: number;
  timestamp: string;
  sourceIp: string;
  destinationIp: string;
  protocol: 'TCP' | 'UDP' | 'ICMP' | 'HTTP';
  threat: 'None' | 'SYN Flood' | 'Port Scan' | 'Suspicious Payload';
  status: 'Allowed' | 'Blocked';
}
