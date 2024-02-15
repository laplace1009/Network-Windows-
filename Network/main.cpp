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
			cout << "立加 肯丰" << endl;
		}
		else {
			cout << "立加 角菩" << endl;
		}

	}

	WSACleanup();

	int* ptr = new int(3);
	int& a = *ptr;
	return 0;
}