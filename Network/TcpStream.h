#pragma once
#include "Types.h"
#include <string_view>
#include <optional>
#include <WinSock2.h>


class TcpStream
{
	enum
	{
		MAX_BUFF_SIZE = 4096,
	};

	struct SocketInfo
	{
		SOCKET socket;
		SOCKADDR_IN addr;
		BYTE* buf;
		int recvBytes;
		int sendBytes;
	};

public:
	TcpStream();
	~TcpStream() noexcept;

public:
	auto Connect(std::string_view addr, uint16 port) -> int;
	auto Recv(uint32 offset) -> int;
	auto Send(BYTE* message, uint32 msgLength, uint32 offset) -> int;

public:
	auto SetSocketOpt(int option) -> int;
	auto GetSocketInfoPtr() -> SocketInfo*;
	auto GetMaxBuffSize() -> uint32;

private:
	SocketInfo mSocket;
};

