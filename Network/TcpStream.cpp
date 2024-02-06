#include "pch.h"
#include "TcpStream.h"

TcpStream::TcpStream()
{
	mSocket = socket(AF_INET, SOCK_STREAM, 0);

	if (mSocket == INVALID_SOCKET)
		CRASH("Socket()");

	memset(&mAddr, 0, sizeof(mAddr));
}

TcpStream::~TcpStream() noexcept
{
	delete[] mBuf;
	closesocket(mSocket);
}

auto TcpStream::GetSocketPtr() -> SOCKET*
{
	return &mSocket;
}

auto TcpStream::GetAddrPtr() -> SOCKADDR_IN*
{
	return &mAddr;
}

auto TcpStream::SetSocketOpt(int option) -> int
{
	int bOptVal = true;
	int iOptLen = sizeof(int);
	return setsockopt(mSocket, SOL_SOCKET, option, reinterpret_cast<char*>(&bOptVal), iOptLen);
}

auto TcpStream::GetBufPtr() -> char*
{
	return mBuf;
}
