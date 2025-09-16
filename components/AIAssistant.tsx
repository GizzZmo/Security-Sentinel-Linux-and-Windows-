
import React, { useState, useRef, useEffect } from 'react';
import type { ChatMessage } from '../types';
import { sendMessageStream } from '../services/geminiService';
import Icon from './icon';
import Spinner from './Spinner';

const AIAssistant: React.FC = () => {
  const [messages, setMessages] = useState<ChatMessage[]>([]);
  const [input, setInput] = useState('');
  const [isLoading, setIsLoading] = useState(false);
  const messagesEndRef = useRef<HTMLDivElement>(null);

  const scrollToBottom = () => {
    messagesEndRef.current?.scrollIntoView({ behavior: 'smooth' });
  };

  useEffect(() => {
    scrollToBottom();
  }, [messages, isLoading]);

  const handleSend = async () => {
    if (!input.trim() || isLoading) return;

    const userMessage: ChatMessage = { role: 'user', content: input };
    setMessages(prev => [...prev, userMessage]);
    setInput('');
    setIsLoading(true);

    const modelMessage: ChatMessage = { role: 'model', content: '' };
    setMessages(prev => [...prev, modelMessage]);

    try {
      const stream = await sendMessageStream(messages, input);
      let currentContent = '';
      for await (const chunk of stream) {
        currentContent += chunk.text;
        setMessages(prev =>
          prev.map((msg, index) =>
            index === prev.length - 1 ? { ...msg, content: currentContent } : msg
          )
        );
      }
    } catch (error) {
      console.error('Error sending message:', error);
      const errorMessage: ChatMessage = {
        role: 'model',
        content: 'Sorry, I encountered an error. Please check the console or try again later.',
      };
      setMessages(prev => [...prev.slice(0, -1), errorMessage]);
    } finally {
      setIsLoading(false);
    }
  };

  const handleKeyPress = (e: React.KeyboardEvent<HTMLInputElement>) => {
    if (e.key === 'Enter' && !e.shiftKey) {
      e.preventDefault();
      handleSend();
    }
  };

  return (
    <div className="p-6 h-full flex flex-col bg-slate-900/20">
      <div className="flex-grow overflow-y-auto pr-4 space-y-6">
        {messages.map((msg, index) => (
          <div key={index} className={`flex items-start gap-4 ${msg.role === 'user' ? 'justify-end' : ''}`}>
            {msg.role === 'model' && (
              <div className="w-8 h-8 flex-shrink-0 bg-blue-500/20 rounded-full flex items-center justify-center">
                <Icon name="bot" className="w-5 h-5 text-blue-300" />
              </div>
            )}
            <div
              className={`max-w-xl p-4 rounded-xl whitespace-pre-wrap ${
                msg.role === 'user'
                  ? 'bg-blue-600 text-white rounded-br-none'
                  : 'bg-slate-700/80 text-slate-200 rounded-bl-none'
              }`}
            >
              {msg.content}
              {isLoading && msg.role === 'model' && index === messages.length - 1 && (
                <span className="inline-block w-2 h-4 bg-white animate-pulse ml-1" />
              )}
            </div>
            {msg.role === 'user' && (
              <div className="w-8 h-8 flex-shrink-0 bg-slate-600 rounded-full flex items-center justify-center">
                <Icon name="user" className="w-5 h-5 text-slate-200" />
              </div>
            )}
          </div>
        ))}
        <div ref={messagesEndRef} />
      </div>
      <div className="mt-6 flex items-center gap-4 p-2 bg-slate-800/50 backdrop-blur-sm border border-slate-700/50 rounded-lg">
        <input
          type="text"
          value={input}
          onChange={e => setInput(e.target.value)}
          onKeyPress={handleKeyPress}
          placeholder="Ask the security assistant..."
          className="w-full bg-transparent focus:outline-none text-slate-200 placeholder-slate-400"
          disabled={isLoading}
        />
        <button
          onClick={handleSend}
          disabled={isLoading || !input.trim()}
          className="p-2 rounded-md bg-blue-600 text-white hover:bg-blue-500 disabled:bg-slate-600 disabled:cursor-not-allowed transition-colors"
        >
          {isLoading ? <Spinner /> : <Icon name="send" className="w-5 h-5" />}
        </button>
      </div>
    </div>
  );
};

export default AIAssistant;
