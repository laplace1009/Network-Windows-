#pragma once
#include "Types.h"
#include <string_view>
#include <optional>
#include <WinSock2.h>


class TcpStream
{
public:
	TcpStream();
	~TcpStream() noexcept;

public:
	auto GetSocketPtr() -> SOCKET*;
	auto GetAddrPtr() -> SOCKADDR_IN*;
	auto SetSocketOpt(int option) -> int;
	auto GetBufPtr() -> char*;

private:
	SOCKET mSocket;
	SOCKADDR_IN mAddr;
	char* mBuf = new char[1024];
};

