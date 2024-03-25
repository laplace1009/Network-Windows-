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

	int* ptr = new int(3);
	int& a = *ptr;
	return 0;
}