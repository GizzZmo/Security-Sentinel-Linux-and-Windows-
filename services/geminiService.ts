
import { GoogleGenAI, Chat, GenerateContentResponse } from "@google/genai";
import { SYSTEM_INSTRUCTION } from '../constants';
import type { ChatMessage } from '../types';

if (!process.env.API_KEY) {
  throw new Error("API_KEY environment variable not set");
}

const ai = new GoogleGenAI({ apiKey: process.env.API_KEY });

let chat: Chat | null = null;

function getChatInstance(): Chat {
  if (!chat) {
    chat = ai.chats.create({
      model: 'gemini-2.5-flash',
      config: {
        systemInstruction: SYSTEM_INSTRUCTION,
      },
    });
  }
  return chat;
}

export async function sendMessageStream(
  _history: ChatMessage[], // eslint-disable-line @typescript-eslint/no-unused-vars
  message: string
): Promise<AsyncGenerator<GenerateContentResponse>> {
  const chatInstance = getChatInstance();
  
  // The Gemini API for chat doesn't need the full history sent every time
  // as the Chat object maintains state. We just send the new message.
  const result = await chatInstance.sendMessageStream({ message });
  return result;
}
