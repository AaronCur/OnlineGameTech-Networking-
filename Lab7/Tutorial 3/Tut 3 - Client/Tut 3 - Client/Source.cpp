/*
Author: Pindrought
Date: 11/13/2015
This is the solution for the client that you should have at the end of tutorial 3.
*/
#pragma comment(lib,"ws2_32.lib") //Required for WinSock
#include <WinSock2.h> //For win sockets
#include <string> //For std::string
#include <iostream> //For std::cout, std::endl, std::cin.getline

SOCKET Connection;//This client's connection to the server

void ClientThread()
{
	int bufferlength; //Holds the length of the message we are receiving
	while (true)
	{
		recv(Connection, (char*)&bufferlength, sizeof(int), NULL); //receive buffer
		char * buffer = new char[bufferlength+1]; //Allocate buffer
		buffer[bufferlength] = '\0'; //Set last character of buffer to be a null terminator so we aren't printing memory that we shouldn't be looking at
		recv(Connection, buffer, bufferlength, NULL);
		std::cout << buffer << std::endl; //print out buffer
		delete[] buffer; //Deallocate buffer
	}
}

int main()
{
	//Winsock Startup
	WSAData wsaData;
	WORD DllVersion = MAKEWORD(2, 1);
	if (WSAStartup(DllVersion, &wsaData) != 0)
	{
		MessageBoxA(NULL, "Winsock startup failed", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}
	
	SOCKADDR_IN addr; //Address to be binded to our Connection socket
	int sizeofaddr = sizeof(addr); //Need sizeofaddr for the connect function
	addr.sin_addr.s_addr = inet_addr("127.0.0.1"); //Address = localhost (this pc)
	addr.sin_port = htons(1111); //Port = 1111
	addr.sin_family = AF_INET; //IPv4 Socket

	Connection = socket(AF_INET, SOCK_STREAM, NULL); //Set Connection socket
	if (connect(Connection, (SOCKADDR*)&addr, sizeofaddr) != 0) //If we are unable to connect...
	{
		MessageBoxA(NULL, "Failed to Connect", "Error", MB_OK | MB_ICONERROR);
		return 0; //Failed to Connect
	}

	std::cout << "Connected!" << std::endl;
	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientThread, NULL, NULL, NULL); //Create the client thread that will receive any data that the server sends.


	std::string userinput; //holds the user's chat message
	while (true)
	{
		std::getline(std::cin,userinput); //Get line if user presses enter and fill the buffer
		int bufferlength = userinput.size(); //Find buffer length
		send(Connection, (char*)&bufferlength, sizeof(int), NULL); //Send length of buffer
		send(Connection, userinput.c_str(), bufferlength, NULL); //Send buffer
		Sleep(10);
	}
	return 0;
}

