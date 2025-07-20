
import React from 'react';

interface CardProps {
  title: string;
  children: React.ReactNode;
  className?: string;
}

const Card: React.FC<CardProps> = ({ title, children, className }) => {
  return (
    <div className={`bg-slate-800/50 backdrop-blur-sm border border-slate-700/50 rounded-lg p-4 shadow-lg ${className}`}>
      <h3 className="text-md font-semibold text-slate-300 mb-2">{title}</h3>
      <div className="text-slate-200">{children}</div>
    </div>
  );
};

export default Card;
