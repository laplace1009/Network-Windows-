#pragma once
#include <string_view>
#include "Socket.h"
#include "TcpStream.h"

class TcpListener
{
public:
	auto Bind(std::string_view addr, uint16 port) -> void;
	auto Accept() -> void;

private:
	TcpStream mServer;
	TcpStream mClient;
};

