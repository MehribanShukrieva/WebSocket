#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <tchar.h>
#include <thread>

using namespace std;

#pragma comment(lib, "ws2_32.lib")

/*
	//initialize winsock library

	//create the socket

	//get ip and port

	//bind the ip/port with the socket

	//listen the socket

	//accept

	//recv and send

	//close the socket

	//cleanup the winsock

*/

bool Initialize() {
	WSADATA data;
	return WSAStartup(MAKEWORD(2,2), &data) == 0;
}

void InteractWithClient(SOCKET clientSocket) {
	//send/recv client
	cout << "client connected" << endl;
	char buffer[4096];

	while (1) {
		int bytesrecvd = recv(clientSocket, buffer, sizeof(buffer), 0);

		if (bytesrecvd <= 0) {
			cout << "client disconnected" << endl;
			break;
		}
		string message(buffer, bytesrecvd);

		cout << "message from client: " << message << endl;
	}

	closesocket(clientSocket);
}

int main() {
	if (!Initialize()) {
		cout << "winsock initialization failed" << endl;
	}
	cout << "server program" << endl;

	SOCKET listenSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (listenSocket == INVALID_SOCKET) {
		cout << "socket creation failed" << endl;
		return 1;
	}

	//create address structure
	int port = 12345;
	sockaddr_in serveraddr;
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(port);

	//convert the ipaddress to binary format 
	//(0.0.0.0) put inside the sin_family in binary form
	if (InetPton(AF_INET, _T("0.0.0.0"), &serveraddr.sin_addr) != 1) {
		cout << "setting address structure failed" << endl;
		closesocket(listenSocket);
		WSACleanup();
		return 1;
	}

	//bind
	if (bind(listenSocket, reinterpret_cast<sockaddr*>(&serveraddr), sizeof(serveraddr)) == SOCKET_ERROR) {
		cout << "bind failed" << endl;
		closesocket(listenSocket);
		WSACleanup();
		return 1;
	}
	
	//listen
	if (listen(listenSocket, SOMAXCONN) == SOCKET_ERROR) {
		cout << "listen failed" << endl;
		closesocket(listenSocket);
		WSACleanup();
		return 1;
	}
	cout << "server has started listening on port: " << port << endl;

	while (1) {
		//accept
		SOCKET clientSocket = accept(listenSocket, nullptr, nullptr);
		if (clientSocket == INVALID_SOCKET) {
			cout << "invalid client socket" << endl;
		}

		thread t1(InteractWithClient, clientSocket);
	}

	closesocket(listenSocket);



	WSACleanup();
	return 0;
}