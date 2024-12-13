#include <iostream>
#include <WinSock2.h>

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

	WSACleanup();
	return 0;
}