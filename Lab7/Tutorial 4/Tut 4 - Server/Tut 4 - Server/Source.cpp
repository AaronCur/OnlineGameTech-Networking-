/*
Author: Pindrought
Date: 2/21/2016
This is the solution for the server that you should have at the end of tutorial 4.
*/
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib,"ws2_32.lib")
#include <WinSock2.h>
#include <string>
#include <iostream>

SOCKET Connections[100];
int TotalConnections = 0;

enum Packet
{
	P_ChatMessage,
	P_Test
};

bool ProcessPacket(int ID, Packet packettype)
{
	switch (packettype)
	{
	case P_ChatMessage:
	{
		int bufferlength; //Length of the string
		//Logic for receiving a string
		int recvcheck = recv(Connections[ID], (char*)&bufferlength, sizeof(int), NULL); //get buffer length
		char * buffer = new char[bufferlength]; //Allocate buffer
		recv(Connections[ID], buffer, bufferlength, NULL); //get buffer message from client
		for (int i = 0; i < TotalConnections; i++) //For each client connection
		{
			if (i == ID) //Don't send the chat message to the same user who sent it
				continue; //Skip user
			Packet chatmessagepacket = P_ChatMessage; //create chat message packet to be sent
			send(Connections[i], (char*)&chatmessagepacket, sizeof(Packet), NULL); //send chat message packet
			send(Connections[i], (char*)&bufferlength, sizeof(int), NULL);//send the buffer length to client at index i
			send(Connections[i], buffer, bufferlength, NULL);//send the chat message to client at index i
		}
		delete[] buffer; //Deallocate buffer to stop from leaking memory
		break;
	}
	default:
		std::cout << "Unknown packet received." << std::endl;
		break;
	}
	return true;
}

void ClientHandlerThread(int ID) //ID = the index in the SOCKET Connections array
{
	while (true)
	{
		//First get the packet type
		Packet packettype;
		recv(Connections[ID], (char*)&packettype, sizeof(Packet), NULL); //Receive packet type from client

		//Once we have the packet type, process the packet
		if (!ProcessPacket(ID, packettype)) //If the packet is not properly processed
			break; //break out of our client handler loop
	}
	closesocket(Connections[ID]); //close the socket that was being used for the client's connection
}

int main()
{
	//Winsock Startup
	WSAData wsaData;
	WORD DllVersion = MAKEWORD(2, 1);
	if (WSAStartup(DllVersion, &wsaData) != 0) //If WSAStartup returns anything other than 0, then that means an error has occured in the WinSock Startup.
	{
		MessageBoxA(NULL, "WinSock startup failed", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}
	
	SOCKADDR_IN addr; //Address that we will bind our listening socket to
	int addrlen = sizeof(addr); //length of the address (required for accept call)
	addr.sin_addr.s_addr = inet_addr("127.0.0.1"); //Broadcast locally
	addr.sin_port = htons(1111); //Port
	addr.sin_family = AF_INET; //IPv4 Socket

	SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL); //Create socket to listen for new connections
	bind(sListen, (SOCKADDR*)&addr, sizeof(addr)); //Bind the address to the socket
	listen(sListen, SOMAXCONN); //Places sListen socket in a state in which it is listening for an incoming connection. Note:SOMAXCONN = Socket Oustanding Max Connections

	SOCKET newConnection; //Socket to hold the client's connection
	int ConnectionCounter = 0; //# of client connections
	for (int i = 0; i < 100; i++)
	{
		newConnection = accept(sListen, (SOCKADDR*)&addr, &addrlen); //Accept a new connection
		if (newConnection == 0) //If accepting the client connection failed
		{
			std::cout << "Failed to accept the client's connection." << std::endl;
		}
		else //If client connection properly accepted
		{
			std::cout << "Client Connected!" << std::endl;
			Connections[i] = newConnection; //Set socket in array to be the newest connection before creating the thread to handle this client's socket.
			TotalConnections += 1; //Incremenent total # of clients that have connected
			CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientHandlerThread, (LPVOID)(i), NULL, NULL); //Create Thread to handle this client. The index in the socket array for this thread is the value (i).
			std::string buftest = "MOTD: Welcome! This is the message of the day!.";
			int size = buftest.size(); //Get size of message in bytes and store it in int size
			Packet chatmessagepacket = P_ChatMessage; //Create packet type: Chat Message to be sent to the server
			send(Connections[i], (char*)&chatmessagepacket, sizeof(Packet), NULL); //Send packet type: Chat Message
			send(Connections[i], (char*)&size, sizeof(int), NULL); //send Size of message
			send(Connections[i], buftest.c_str(), buftest.size(), NULL); //send Message

			Packet testpacket = P_Test;
			send(Connections[i], (char*)&testpacket, sizeof(Packet), NULL); //Send test packet
		}
	}
	
	system("pause");
	return 0;
}