#include "pch.h"
#include "AsyncListener.h"

AsyncListener::AsyncListener()
{
	ASSERT_CRASH(AsyncStream::Init() == Error::OK);
}

Error AsyncListener::BindAny(uint16 port)
{
	if (mListener.BindAny(port) == Error::NET_BIND_ERROR)
		return Error::NET_BIND_ERROR;

	return ::listen(mListener.GetEndpointRef().ConstGetSocket(), SOMAXCONN) != SOCKET_ERROR ? Error::OK : Error::NET_LISTEN_ERROR;
}

Error AsyncListener::Bind(std::string addr, uint16 port)
{
	if (mListener.Bind(addr, port) == Error::NET_BIND_ERROR)
		return Error::NET_BIND_ERROR;

	return ::listen(mListener.GetEndpointRef().ConstGetSocket(), SOMAXCONN) != SOCKET_ERROR ? Error::OK : Error::NET_LISTEN_ERROR;
}

Error AsyncListener::Accept()
{
	DWORD addrLen = sizeof(SOCKADDR_IN) + 16;
	DWORD recvBytes{ 0 };
	AsyncEndpoint* client = new AsyncEndpoint();
	if (false == AsyncStream::AcceptEx(mListener.GetEndpointRef().ConstGetSocket(), client->GetEndpointRef().ConstGetSocket(), client->GetBufRef().buf, 0, addrLen, addrLen, OUT & recvBytes, OUT static_cast<LPOVERLAPPED>(client->GetEndpointRef().GetOverlappedRef())))
	{
		int error = WSAGetLastError();
		if (error != WSA_IO_PENDING)
		{
			return Error::NET_ACCEPT_ERROR;
		}
	}

	return Error::OK;
}

Error AsyncListener::Connect(DWORD* bytes)
{
	return Error::OK;
}

Error AsyncListener::Recv(WSABUF* buf, DWORD* bytes)
{
	return mListener.Recv();
}

Error AsyncListener::Send(WSABUF* buf, DWORD* bytes, CHAR* msg, size_t size)
{
	if (false == WSASend(mListener.GetEndpointRef().ConstGetSocket(), buf, 1, bytes, 0, mListener.GetEndpointRef().GetOverlappedRef(), NULL))
	{
		return Error::NET_SEND_ERROR;
	}

	return Error::OK;
}

auto AsyncListener::Accept(AsyncEndpoint* client) -> Error
{
	DWORD addrLen = sizeof(SOCKADDR_IN) + 16;
	DWORD recvBytes{ 0 };
	AsyncEndpoint* newClient = static_cast<AsyncEndpoint*>(client);
	if (false == AsyncStream::AcceptEx(mListener.GetEndpointRef().ConstGetSocket(), newClient->GetEndpointRef().ConstGetSocket(), newClient->GetBufRef().buf, 0, addrLen, addrLen, OUT & recvBytes, OUT static_cast<LPOVERLAPPED>(newClient->GetEndpointRef().GetOverlappedRef())))
	{
		int error = WSAGetLastError();
		if (error != WSA_IO_PENDING)
		{
			return Error::NET_ACCEPT_ERROR;
		}
	}

	return Error::OK;
}

auto AsyncListener::Send(AsyncEndpoint* dest, CHAR* msg, size_t size)-> Error
{
	return SOCKET_ERROR != WSASend(dest->GetEndpointRef().ConstGetSocket(), &mListener.GetBufRef(), 1, &mListener.GetTransferredBytesRef(), 0, mListener.GetEndpointRef().GetOverlappedRef(), NULL) ? Error::OK : Error::NET_SEND_ERROR;
}

const SOCKET AsyncListener::ConstGetSocket() const
{
	return mListener.ConstGetSocket();
}

SOCKET& AsyncListener::GetSocketRef()
{
	return mListener.GetEndpointRef().GetSocketRef();
}

SOCKADDR_IN& AsyncListener::GetAddrRef()
{
	return mListener.GetEndpointRef().GetAddrRef();
}

auto AsyncListener::SetSocket(SOCKET socket) -> void
{
	mListener.GetEndpointRef().GetSocketRef() = socket;
}

auto AsyncListener::SetTransferredBytes(DWORD bytes) -> void
{
	mListener.SetTransferredBytes(bytes);
}

auto AsyncListener::GetAsyncStreamRef() -> AsyncEndpoint&
{
	return mListener;
}

auto AsyncListener::SocketAcceptUpdate(AsyncEndpoint* client) -> Error
{
	return SetSocketOpt<SOCKET>(&client->GetEndpointRef(), SO_UPDATE_ACCEPT_CONTEXT, &mListener.GetEndpointRef().GetSocketRef(), sizeof(mListener.GetEndpointRef().ConstGetSocket()));
}

auto AsyncListener::GetTransferredBytesRef() -> DWORD&
{
	return mListener.GetTransferredBytesRef();
}
