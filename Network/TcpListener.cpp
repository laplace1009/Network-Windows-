#include "pch.h"
#include "TcpListener.h"

auto TcpListener::Bind(std::string_view addr, uint16 port) -> void
{
	mServer.GetAddrPtr()->sin_family = AF_INET;
	mServer.GetAddrPtr()->sin_addr.s_addr = htonl(INADDR_ANY);
	mServer.GetAddrPtr()->sin_port = htons(port);
	if (SOCKET_ERROR == bind(*mServer.GetSocketPtr(), reinterpret_cast<SOCKADDR*>(mServer.GetAddrPtr()), sizeof(*mServer.GetAddrPtr())))
		return;

	if (SOCKET_ERROR == listen(*mServer.GetSocketPtr(), SOMAXCONN))
		return;
}

auto TcpListener::Accept() -> std::optional<TcpStream>
{
	TcpStream client;
	int addrLen = sizeof(*client.GetAddrPtr());
	*client.GetSocketPtr() = accept(*mServer.GetSocketPtr(), reinterpret_cast<SOCKADDR*>(client.GetAddrPtr()), &addrLen);
	if (*client.GetSocketPtr() == INVALID_SOCKET)
		return {};

	return client;
}

auto TcpListener::Recv(OUT TcpStream* client) -> int
{
	return recv(*client->GetSocketPtr(), client->GetBufPtr(), sizeof(*client->GetAddrPtr()), 0);
}

auto TcpListener::Send(TcpStream* client, int retVal) -> int
{
	return send(*client->GetSocketPtr(), client->GetBufPtr(), retVal, 0);
}
