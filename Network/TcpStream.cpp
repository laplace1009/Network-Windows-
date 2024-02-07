#include "pch.h"
#include "TcpStream.h"

TcpStream::TcpStream()
{
	mSocket.buf = new BYTE[MAX_BUFF_SIZE + 1];
	mSocket.socket = socket(AF_INET, SOCK_STREAM, 0);

	if (mSocket.socket == INVALID_SOCKET)
		CRASH("Socket()");

	memset(&mSocket.addr, 0, sizeof(mSocket.addr));
}

TcpStream::~TcpStream() noexcept
{
	delete[] mSocket.buf;
	closesocket(mSocket.socket);
}

auto TcpStream::Connect(std::string_view addr, uint16 port) -> int
{
	mSocket.addr.sin_family = AF_INET;
	inet_pton(AF_INET, addr.data(), &mSocket.addr.sin_addr);
	mSocket.addr.sin_port = htons(port);
	return connect(mSocket.socket, reinterpret_cast<SOCKADDR*>(&mSocket.addr), sizeof(mSocket.addr));
}

auto TcpStream::Recv() -> int
{
	return recv(mSocket.socket, reinterpret_cast<char*>(mSocket.buf), sizeof(mSocket.addr), 0);
}

auto TcpStream::Send(BYTE* message) -> int
{
	uint64 msgLength = sizeof(*message);
	uint64 sendMsgLength = 0;
	while (sendMsgLength < msgLength)
	{
		uint64 remainMsgLength = msgLength - sendMsgLength;
		uint64 sendLength = remainMsgLength > MAX_BUFF_SIZE ? MAX_BUFF_SIZE : remainMsgLength;
		if (SOCKET_ERROR == send(mSocket.socket, reinterpret_cast<char*>(mSocket.buf) + sendMsgLength, static_cast<int>(sendLength), 0))
			return SOCKET_ERROR;
		sendMsgLength += sendLength;
	}

	return sendMsgLength;
}

auto TcpStream::GetSocketPtr() -> SOCKET*
{
	return &mSocket.socket;
}

auto TcpStream::GetAddrPtr() -> SOCKADDR_IN*
{
	return &mSocket.addr;
}

auto TcpStream::SetSocketOpt(int option) -> int
{
	int bOptVal = true;
	int iOptLen = sizeof(int);
	return setsockopt(mSocket.socket, SOL_SOCKET, option, reinterpret_cast<char*>(&bOptVal), iOptLen);
}

auto TcpStream::GetBufPtr() -> BYTE*
{
	return mSocket.buf;
}
