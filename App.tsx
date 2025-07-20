
import React, { useState } from 'react';
import { View } from './types';
import Sidebar from './components/Sidebar';
import Header from './components/Header';
import Dashboard from './components/Dashboard';
import NetworkMonitor from './components/NetworkMonitor';
import ThreatProtection from './components/ThreatProtection';
import AIAssistant from './components/AIAssistant';

const App: React.FC = () => {
  const [currentView, setCurrentView] = useState<View>(View.Dashboard);

  const renderView = () => {
    switch (currentView) {
      case View.Dashboard:
        return <Dashboard />;
      case View.NetworkMonitor:
        return <NetworkMonitor />;
      case View.ThreatProtection:
        return <ThreatProtection />;
      case View.AIAssistant:
        return <AIAssistant />;
      default:
        return <Dashboard />;
    }
  };

  return (
    <div className="flex h-screen w-screen overflow-hidden">
      <Sidebar currentView={currentView} onViewChange={setCurrentView} />
      <main className="flex-1 flex flex-col bg-slate-900">
        <Header title={currentView} />
        <div className="flex-1 overflow-y-auto">
          {renderView()}
        </div>
      </main>
    </div>
  );
};

export default App;
