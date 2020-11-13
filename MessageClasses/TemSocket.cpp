#include "pch-il2cpp.h"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>
#include <Windowsx.h>
#include <string>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <stdio.h>
#include <thread>
#include <vector>
#include <filesystem>

#include "StringUtils.h"
#include "ManagerDef.h"
#include "GhostHandler.h"

#include "TemSocket.h"

//WINSOCKET
static const char* IpAdress = "134.209.241.56";
char** argv;

#define DEFAULT_PORT "9999"
#define DEFAULT_CLIENT_LISTEN_PORT "9998"
#define DEFAULT_BUFLEN 512
#define MESSAGE_SIZE_WIDTH 8
#define MESSAGE_DELIMITER "|;?;|"

std::vector<std::string> TemSocket::ConnectedClients;
std::vector<std::string> TemSocket::ReceivedMessages = std::vector<std::string>();
std::vector<std::string> TemSocket::MessageQueue = std::vector<std::string>();
bool TemSocket::IsConnected = false;
bool TemSocket::MessageIsComplete = false;
std::string TemSocket::StaticError = "";
std::string TemSocket::ReceivedMessage = "";
std::thread TemSocket::ListenLoopThread;
std::thread TemSocket::ProcessMessageQueueThread;
std::string TemSocket::Error = "";
std::string TemSocket::MessageBufer = "";
SOCKET TemSocket::ConnectSocket = INVALID_SOCKET;
SOCKET TemSocket::ListenSocket = INVALID_SOCKET;
SOCKET TemSocket::ClientSocket = INVALID_SOCKET;
SOCKET TemSocket::MessageSocket = INVALID_SOCKET;
const std::string TemSocket::MD = "|;?;|";

void TemSocket::ConnectToServer(std::string message)
{
	//WINSOCKET
	WSADATA wsaData;
	int iResult;

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		Error = "WSAStartup failed";
		IsConnected = false;
		return;
	}

	struct addrinfo* result = NULL, * ptr = NULL, hints;

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	// Resolve the server address and port
	iResult = getaddrinfo(IpAdress, DEFAULT_PORT, &hints, &result);
	if (iResult != 0) {
		Error = "getaddrinfo failed";
		IsConnected = false;
		WSACleanup();
		return;
	}

	// Attempt to connect to the first address returned by
	// the call to getaddrinfo
	ptr = result;

	// Create a SOCKET for connecting to server
	ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,
		ptr->ai_protocol);

	if (ConnectSocket == INVALID_SOCKET) {
		Error = "Error at socket";
		IsConnected = false;
		freeaddrinfo(result);
		WSACleanup();
		return;
	}

	// Connect to server.
	iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
	if (iResult == SOCKET_ERROR) {
		Error = "Error at socket";
		IsConnected = false;
		closesocket(ConnectSocket);
		ConnectSocket = INVALID_SOCKET;
	}

	// Should really try the next address returned by getaddrinfo
	// if the connect call failed
	// But for this simple example we just free the resources
	// returned by getaddrinfo and print an error message

	freeaddrinfo(result);

	if (ConnectSocket == INVALID_SOCKET) {
		Error = "Unable to connect to server";
		IsConnected = false;
		WSACleanup();
		return;
	}

	IsConnected = true;
	MessageQueue.push_back(message);

	ListenLoopThread = std::thread(ListenLoop, (LPVOID)ConnectSocket);
	ListenLoopThread.detach();
	//WINSOCKET
}

int TemSocket::ReadyToReceive(int sock, int interval)
{
	fd_set fds;
	FD_ZERO(&fds);
	FD_SET(sock, &fds);

	timeval tv;
	tv.tv_sec = interval;
	tv.tv_usec = 0;

	return select(sock + 1, &fds, 0, 0, &tv);
}

void TemSocket::ListenLoop(LPVOID lpParameter)
{
	ListenSocket = (SOCKET)lpParameter;

	int bytesSent;
	int bytesRecv = SOCKET_ERROR;
	char sendbuf[2000] = "";
	int recvbuflen = DEFAULT_BUFLEN;
	char recvbuf[2000] = "";
	int isBytesLeft = -1;

	while (TemSocket::IsConnected == true)
	{
		isBytesLeft = ReadyToReceive(ListenSocket, 0);// recv(ListenSocket, recvbuf, recvbuflen, MSG_PEEK);

		if (isBytesLeft > 0)
		{
			int messageSize = -1;
			int sizeRecvBufLen = MESSAGE_SIZE_WIDTH;
			char sizeRecvBuf[MESSAGE_SIZE_WIDTH];
			messageSize = recv(ListenSocket, sizeRecvBuf, MESSAGE_SIZE_WIDTH, 0);
			std::string tempMessage = std::string(sizeRecvBuf, MESSAGE_SIZE_WIDTH);
			
			if (messageSize != -1)
			{
				int messageLength = std::stoi(tempMessage);

			TryReadingMore:
				while (isBytesLeft > 0 && TemSocket::IsConnected == true)
				{
					ZeroMemory(recvbuf, sizeof(recvbuf));
					bytesRecv = recv(ListenSocket, recvbuf, recvbuflen, 0);

					if (bytesRecv == SOCKET_ERROR)
					{
						StaticError = "Print failed";
						IsConnected = false;
						closesocket(ListenSocket);
						WSACleanup();
						return;
					}

					if (bytesRecv > 0)
					{
						MessageBufer += std::string(recvbuf, bytesRecv);
					}

					//ZeroMemory(recvbuf, sizeof(recvbuf));
					isBytesLeft = ReadyToReceive(ListenSocket, 0); //recv(ListenSocket, recvbuf, recvbuflen, MSG_PEEK);
				}

				if (MessageBufer.size() >= messageLength)
				{
					ReceivedMessage = MessageBufer.substr(0, messageLength);
					MessageIsComplete = true;

					if (MessageBufer.size() > 0)
						MessageBufer = MessageBufer.substr(messageLength, std::string::npos);
				}
				else if (MessageBufer.size() < messageLength && TemSocket::IsConnected == true)
				{
					isBytesLeft = 1;
					goto TryReadingMore;
				}
			}
			else
			{
				IsConnected = false;
				closesocket(ListenSocket);
				WSACleanup();
			}
		}

		if (MessageIsComplete == true && ReceivedMessage.size() > 0)
		{
			MessageIsComplete = false;
			auto message = sutil::SplitTem(ReceivedMessage, TemSocket::MD);

			switch (sutil::hash(message[0].data()))
			{
			case sutil::hash("1"):
			{
				bytesSent = send(ListenSocket, sendbuf, strlen(sendbuf), 0);

				if (bytesSent == SOCKET_ERROR)
				{
					IsConnected = false;
					closesocket(ListenSocket);
					WSACleanup();
				}
			}
			break;

			case sutil::hash("2"):
			{
				bytesSent = send(ListenSocket, sendbuf, strlen(sendbuf), 0);

				if (bytesSent == SOCKET_ERROR)
				{
					IsConnected = false;
					closesocket(ListenSocket);
					WSACleanup();
				}
			}
			break;

			case sutil::hash("exit"):
			{
				IsConnected = false;
				closesocket(ListenSocket);
				WSACleanup();
			}
			break;

			case sutil::hash("SENDINGGHOSTS"):
			{
				auto ghosts = sutil::SplitTem(message[3], "\\t\\b");
				srand(time(NULL));

				for (auto& ghost : ghosts)
				{
					if (ghost.size() > 1024)
					{
						int randomNumber = rand() % 10000000;
						sutil::Write(ManagerPath + "\\RaceSettings\\" + message[2] + "\\ghosts\\" + "og1764" + ".ghost", ghost); //std::to_string(randomNumber)
					}
				}
			}
			break;

			case sutil::hash("GETGHOSTSYNC"):
			{
				if (message.size() > 0)
				{
					GhostHandler::LastReadGhostFrame = std::stoi(message[1]);

					if (message.size() > 2)
					{
						GhostHandler::InsertGhostFrames(message[2]);
						GhostHandler::ReadMessages.push_back(message[2]);

						if (GhostHandler::WaitingOnLastFrame)
						{
							sutil::Write(ManagerPath + "TestGhostSync.data", GhostHandler::AllStreamGhostFrames);

							for (auto frame : GhostHandler::ReadMessages)
							{
								sutil::Append(ManagerPath + "TestGhostSyncVector.data", frame);
							}
						}
					}
				}
				GhostHandler::ServerRespond = true;
			}
			break;

			case sutil::hash("GETGHOSTS"):
			{
				if (message.size() > 2)
				{
					std::filesystem::path ghostFolder = ManagerPath + "Ghosts\\" + message[1];

					if (std::filesystem::exists(ghostFolder) == false)
						std::filesystem::create_directories(ghostFolder);

					for (int i = 2; i < message.size(); i+= 2)
					{
						sutil::Write(ghostFolder.string() + "\\" + message[i], message[i + 1]);
					}
				}
			}
			break;
			}

			ReceivedMessage = "";
		}

		ProcessMessageQueue();
	}

	closesocket(ListenSocket);
	WSACleanup();
}

void TemSocket::ProcessMessageQueue()
{
	while (MessageQueue.size() > 0 && TemSocket::IsConnected == true)
	{
		auto message = MessageQueue[0];

		std::stringstream ss;
		ss << std::setw(MESSAGE_SIZE_WIDTH) << std::setfill('0') << message.size();
		std::string s = ss.str();

		message = s + message;
		std::size_t position = 0;
		int bytesSent;
		char sendbuf[4096] = "";

		while (position < message.size() && TemSocket::IsConnected == true)
		{
			std::fill(sendbuf, sendbuf + 4096, 0);
			message.copy(sendbuf, 4096, position);

			bytesSent = send(ListenSocket, sendbuf, std::min<int>(message.size() - position, 4096), 0);

			if (bytesSent == SOCKET_ERROR) {
				StaticError = "Print failed";
				IsConnected = false;
				closesocket(ListenSocket);
				WSACleanup();
				return;
			}

			position += bytesSent;
		}

		MessageQueue.erase(MessageQueue.begin());
	}
}

void TemSocket::SendSocketMessage(std::string message)
{
	if (TemSocket::IsConnected == true || (TemSocket::IsConnected == false && TemSocket::MessageQueue.size() < 256))
		MessageQueue.push_back(message);
}

void TemSocket::Exit()
{
	StaticError = "Exiting";
	IsConnected = false;
	SendSocketMessage("EXIT");
	closesocket(ListenSocket);

	WSACleanup();
}

void TemSocket::ReceiveMessage(LPVOID lpParameter)
{
	SOCKET AcceptSocket = (SOCKET)lpParameter;
	int bytesRecv = SOCKET_ERROR;
	int recvbuflen = DEFAULT_BUFLEN;
	char recvbuf[DEFAULT_BUFLEN] = "";

	ZeroMemory(recvbuf, sizeof(recvbuf));
	bytesRecv = recv(AcceptSocket, recvbuf, recvbuflen, 0);

	if (bytesRecv == SOCKET_ERROR) {
		StaticError = "Print failed";
		IsConnected = false;
		closesocket(AcceptSocket);
		WSACleanup();
		return;
	}

	if (bytesRecv > 0)
	{
		MessageBufer += std::string(recvbuf, bytesRecv);

		std::size_t teoIndex = MessageBufer.find("@TEO||");
		std::size_t eotIndex = MessageBufer.find("||EOT@");
		if (teoIndex != std::string::npos && eotIndex != std::string::npos && teoIndex < eotIndex)
		{
			ReceivedMessage = MessageBufer.substr(teoIndex, eotIndex + 6);
			MessageBufer = MessageBufer.substr(eotIndex + 6, std::string::npos);
			MessageIsComplete = true;
			return;
		}
	}

	return;
}