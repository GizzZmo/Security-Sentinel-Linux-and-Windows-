import React from 'react';
import { BarChart, Bar, XAxis, YAxis, CartesianGrid, Tooltip, Legend, ResponsiveContainer } from 'recharts';
import Card from './Card';
import Icon from './icon';

const chartData = [
  { name: 'Mon', 'Blocked Threats': 4, 'Scans': 10 },
  { name: 'Tue', 'Blocked Threats': 3, 'Scans': 12 },
  { name: 'Wed', 'Blocked Threats': 5, 'Scans': 8 },
  { name: 'Thu', 'Blocked Threats': 2, 'Scans': 15 },
  { name: 'Fri', 'Blocked Threats': 8, 'Scans': 11 },
  { name: 'Sat', 'Blocked Threats': 12, 'Scans': 20 },
  { name: 'Sun', 'Blocked Threats': 7, 'Scans': 18 },
];

const Dashboard: React.FC = () => {
  return (
    <div className="p-6 space-y-6">
      <div className="grid grid-cols-1 md:grid-cols-2 lg:grid-cols-4 gap-6">
        <Card title="System Status">
          <div className="flex items-center text-green-400">
            <Icon name="shield" className="w-10 h-10 mr-4" />
            <div>
              <p className="text-2xl font-bold">Secure</p>
              <p className="text-sm text-slate-400">No active threats detected.</p>
            </div>
          </div>
        </Card>
        <Card title="Threats Blocked (24h)">
          <div className="flex items-center text-blue-400">
            <p className="text-4xl font-bold mr-4">137</p>
            <p className="text-sm text-slate-400">Malicious attempts neutralized</p>
          </div>
        </Card>
        <Card title="Network Scans Detected">
          <div className="flex items-center text-yellow-400">
            <p className="text-4xl font-bold mr-4">42</p>
            <p className="text-sm text-slate-400">Reconnaissance activities logged</p>
          </div>
        </Card>
        <Card title="Firewall Rules">
          <div className="flex items-center text-slate-300">
            <p className="text-4xl font-bold mr-4">2,154</p>
            <p className="text-sm text-slate-400">Active protection rules</p>
          </div>
        </Card>
      </div>
      
      <Card title="Weekly Security Overview">
        <div style={{ width: '100%', height: 300 }}>
          <ResponsiveContainer>
            <BarChart data={chartData}>
              <CartesianGrid strokeDasharray="3 3" stroke="rgba(255, 255, 255, 0.1)" />
              <XAxis dataKey="name" stroke="#94a3b8" />
              <YAxis stroke="#94a3b8" />
              <Tooltip
                contentStyle={{ 
                  backgroundColor: 'rgba(30, 41, 59, 0.8)',
                  borderColor: '#475569',
                  color: '#e2e8f0',
                }}
              />
              <Legend wrapperStyle={{color: '#e2e8f0'}}/>
              <Bar dataKey="Blocked Threats" fill="#60a5fa" />
              <Bar dataKey="Scans" fill="#facc15" />
            </BarChart>
          </ResponsiveContainer>
        </div>
      </Card>
    </div>
  );
};

export default Dashboard;
