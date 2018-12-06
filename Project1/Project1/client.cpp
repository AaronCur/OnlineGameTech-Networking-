#include <iostream>
#include <string>
#include <WS2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

using namespace std;

#include "Client.h"

Client::Client()
{

	/// <summary>
	/// Constructor
	/// </summary>


											// Initialize WinSock

	WSAData data;
	WORD ver = MAKEWORD(2, 2);
	int wsResult = WSAStartup(ver, &data);
	if (wsResult != 0)
	{
		cerr << "Can't start Winsock, Err #" << wsResult << endl;
		return;
	}

	// Create socket
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET)
	{
		cerr << "Can't create socket, Err #" << WSAGetLastError() << endl;
		WSACleanup();
		return;
	}

	// Fill in a hint structure
	hint.sin_family = AF_INET;
	hint.sin_port = htons(port);
	inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);

	
}

Client::~Client()
{
}



bool Client::run()
{

	// Connect to server
	int connResult = connect(sock, (sockaddr*)&hint, sizeof(hint));
	if (connResult == SOCKET_ERROR)
	{
		cerr << "Can't connect to server, Err #" << WSAGetLastError() << endl;
		closesocket(sock);
		WSACleanup();
		return false;
	}

	return true;



}

void Client::receive()
{


	// Wait for response
	ZeroMemory(buf, 4096);
	int bytesReceived = recv(sock, buf, 4096, 0);
	if (bytesReceived > 0)
	{
		// Echo response to console
		cout << "SERVER> " << string(buf, 0, bytesReceived) << endl;
	}




}

void Client::sendMessage(std::string message)
{
	string userInput;
	userInput = message;
	int sendResult = send(sock, userInput.c_str(), userInput.size() + 1, 0);
	

}

