#pragma once
#include "Types.h"
#include "Socket.h"
#include <string_view>
#include <optional>
#include <WinSock2.h>


class TcpStream
{
public:
	auto Init() -> int;
	auto GetSocket() -> SOCKET*;
	auto GetAddr() -> SOCKADDR_IN*;
	auto SetSocketOpt() -> void;

private:
	SOCKET mSocket;
	SOCKADDR_IN mAddr;
};

