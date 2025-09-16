
import React, { useState, useEffect, useRef } from 'react';
import type { NetworkLog } from '../types';
import Card from './Card';

const generateRandomIp = () => `${Math.floor(Math.random() * 255)}.${Math.floor(Math.random() * 255)}.${Math.floor(Math.random() * 255)}.${Math.floor(Math.random() * 255)}`;

const protocols: NetworkLog['protocol'][] = ['TCP', 'UDP', 'ICMP', 'HTTP'];
const threats: NetworkLog['threat'][] = ['None', 'SYN Flood', 'Port Scan', 'Suspicious Payload'];

const generateLogEntry = (id: number): NetworkLog => {
  const threat = threats[Math.floor(Math.random() * threats.length)];
  return {
    id,
    timestamp: new Date().toLocaleTimeString(),
    sourceIp: generateRandomIp(),
    destinationIp: `192.168.1.${Math.floor(Math.random() * 254) + 1}`,
    protocol: protocols[Math.floor(Math.random() * protocols.length)],
    threat,
    status: threat !== 'None' ? 'Blocked' : 'Allowed',
  };
};

const getStatusColor = (status: NetworkLog['status']) => {
  return status === 'Blocked' ? 'text-red-400' : 'text-green-400';
}

const getThreatColor = (threat: NetworkLog['threat']) => {
  switch(threat) {
    case 'SYN Flood': return 'bg-red-500/20 text-red-300';
    case 'Port Scan': return 'bg-yellow-500/20 text-yellow-300';
    case 'Suspicious Payload': return 'bg-orange-500/20 text-orange-300';
    default: return 'bg-slate-700/50 text-slate-300';
  }
}


const NetworkMonitor: React.FC = () => {
  const [logs, setLogs] = useState<NetworkLog[]>([]);
  const logContainerRef = useRef<HTMLDivElement>(null);
  const idCounter = useRef(0);

  useEffect(() => {
    const initialLogs = Array.from({ length: 15 }, (_, i) => generateLogEntry(i));
    idCounter.current = 15;
    setLogs(initialLogs);

    const interval = setInterval(() => {
      setLogs(prevLogs => {
        const newLog = generateLogEntry(idCounter.current++);
        const updatedLogs = [newLog, ...prevLogs];
        if (updatedLogs.length > 50) {
          updatedLogs.pop();
        }
        return updatedLogs;
      });
    }, 2000);

    return () => clearInterval(interval);
  }, []);

  useEffect(() => {
    if (logContainerRef.current) {
      logContainerRef.current.scrollTop = 0;
    }
  }, [logs]);

  return (
    <div className="p-6 h-full flex flex-col">
      <Card title="Real-time Network Traffic" className="flex-grow flex flex-col">
        <div className="grid grid-cols-6 gap-4 px-4 py-2 font-semibold text-slate-400 border-b border-slate-700">
          <div>Timestamp</div>
          <div>Source IP</div>
          <div>Destination IP</div>
          <div>Protocol</div>
          <div>Threat Detected</div>
          <div className="text-right">Status</div>
        </div>
        <div ref={logContainerRef} className="overflow-y-auto flex-grow">
          {logs.map(log => (
            <div key={log.id} className="grid grid-cols-6 gap-4 px-4 py-3 border-b border-slate-800 animate-fade-in text-sm items-center">
              <div className="text-slate-400">{log.timestamp}</div>
              <div>{log.sourceIp}</div>
              <div>{log.destinationIp}</div>
              <div><span className="px-2 py-1 text-xs rounded-full bg-slate-700">{log.protocol}</span></div>
              <div><span className={`px-2 py-1 text-xs rounded-full ${getThreatColor(log.threat)}`}>{log.threat}</span></div>
              <div className={`text-right font-semibold ${getStatusColor(log.status)}`}>{log.status}</div>
            </div>
          ))}
        </div>
      </Card>
    </div>
  );
};

export default NetworkMonitor;
