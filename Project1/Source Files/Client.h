#pragma once

#include <SDL.h>
#include <SDL_timer.h>
#include <SDL_image.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <WS2tcpip.h>
#pragma comment(lib, "ws2_32.lib")


using namespace std;

class Client {

public:
	Client();
	~Client();

	bool run();
	void receive();
	void sendMessage(std::string message);
	void close();
	std::vector<float> m_positionVec;
	bool joined = false;
	bool gameOver = false;
	int m_joinNum;
private:



	char buf[4096];
	SOCKET sock;
	sockaddr_in hint;
	string userInput;
	string ipAddress = "149.153.106.161";			// IP Address of the server
	int port = 54000;						// Listening port # on the server
	string message;
	

};
