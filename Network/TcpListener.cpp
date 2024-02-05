#include "pch.h"
#include "TcpListener.h"

auto TcpListener::Bind(std::string_view addr, uint16 port) -> void
{
	mServer.Init();
	mServer.GetAddr()->sin_family = AF_INET;
	mServer.GetAddr()->sin_addr.s_addr = htonl(INADDR_ANY);
	mServer.GetAddr()->sin_port = htons(port);
	if (SOCKET_ERROR == bind(*mServer.GetSocket(), reinterpret_cast<SOCKADDR*>(mServer.GetAddr()), sizeof(*mServer.GetAddr())))
		return;

	if (SOCKET_ERROR == listen(*mServer.GetSocket(), SOMAXCONN))
		return;
}

auto TcpListener::Accept() -> void
{
	int addrLen;
	*mClient.GetSocket() =  accept(*mServer.GetSocket(), reinterpret_cast<SOCKADDR*>(mClient.GetAddr()), &addrLen);
	if (*mClient.GetSocket() == INVALID_SOCKET)
		return;
}
