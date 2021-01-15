#pragma once

class TemSocket
{
public:
	static std::vector<std::string> ReceivedMessages;
	static std::vector<std::string> ConnectedClients;
	static std::vector<std::string> MessageQueue;
	static const std::string MD;

	static bool IsConnected;
	static bool MessageIsComplete;

	static std::thread ListenLoopThread;
	static std::thread ProcessMessageQueueThread;
	
	static std::string StaticError;
	static std::string ReceivedMessage;
	static std::string Error;
	static std::string MessageBufer;

	static SOCKET ConnectSocket;
	static SOCKET ListenSocket;
	static SOCKET MessageSocket;
	static SOCKET ClientSocket;

	static void ListenLoop(LPVOID lpParameter);
	static void ReceiveMessage(LPVOID lpParameter);
	static void ProcessMessageQueue();
	static int ReadyToReceive(int sock, int interval = 1);
	static void ConnectToServer(std::string message);
	static void SendSocketMessage(std::string message);
	static void Exit();
};