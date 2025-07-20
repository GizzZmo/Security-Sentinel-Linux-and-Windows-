
import React from 'react';
import Icon from './Icon';

interface HeaderProps {
  title: string;
}

const Header: React.FC<HeaderProps> = ({ title }) => {
  return (
    <header className="flex items-center justify-between p-4 bg-slate-900/50 backdrop-blur-sm border-b border-slate-700/50">
      <h2 className="text-2xl font-semibold text-white">{title}</h2>
      <div className="flex items-center px-3 py-1 bg-green-500/20 border border-green-400/50 rounded-full text-sm text-green-300">
        <Icon name="shield" className="w-4 h-4 mr-2" />
        <span>Protected</span>
      </div>
    </header>
  );
};

export default Header;
