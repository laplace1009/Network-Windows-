#include "pch.h"
#include "TcpStream.h"

auto TcpStream::Init() -> int
{
	mSocket = socket(AF_INET, SOCK_STREAM, 0);

	if (mSocket == INVALID_SOCKET) return 1;

	memset(&mAddr, 0, sizeof(mAddr));

	return 0;
}

auto TcpStream::GetSocket() -> SOCKET*
{
	return &mSocket;
}

auto TcpStream::GetAddr() -> SOCKADDR_IN*
{
	return &mAddr;
}
