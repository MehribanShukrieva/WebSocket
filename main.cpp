#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <tchar.h>

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
	sockaddr_in serveraddr;
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(12345);

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
	WSACleanup();
	return 0;
}