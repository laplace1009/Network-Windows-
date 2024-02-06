#include "pch.h"
#include "TcpStream.h"
#include "TcpListener.h"
#include <iostream>

using namespace std;

int main()
{
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 3), &wsaData) != 0)
		return 1;

	TcpListener server;
	server.Bind("127.0.0.1", 9000);

	while (1)
	{
		TcpStream client;
		auto resClient = server.Accept();
		if (resClient.has_value())
		{
			cout << "접속 완료" << endl;
		}
		else {
			cout << "접속 실패" << endl;
		}

	}

	WSACleanup();
	return 0;
}