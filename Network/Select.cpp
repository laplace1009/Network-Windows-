#include "pch.h"
#include "Select.h"

auto Select::Init() -> void
{
	mStreams.reserve(FD_SETSIZE);
}

auto Select::Run(TcpListener& server, const timeval* time = nullptr) -> int
{
	FD_ZERO(&mReads);
	FD_ZERO(&mWrites);
	FD_SET(server.GetServerSocketPtr()->GetSocketInfoPtr()->socket, &mReads);
	for (TcpStream& stream : mStreams)
	{
		FD_SET(stream.GetSocketInfoPtr()->socket, &mReads);
		FD_SET(stream.GetSocketInfoPtr()->socket, &mWrites);
	}

	int32 retVal = select(0, &mReads, &mWrites, nullptr, time);
	
	if (retVal == SOCKET_ERROR)
		return SOCKET_ERROR;

	if (FD_ISSET(server.GetServerSocketPtr()->GetSocketInfoPtr()->socket, &mReads))
	{
		auto client = server.Accept();
		if (client.has_value() == false)
			return INVALID_SOCKET;

		SubScribes(std::move(client.value()));
	}
}

auto Select::SubScribes(TcpStream&& stream) -> bool
{
	if (mStreams.size() + 1 <= FD_SETSIZE)
		return false;

	mStreams.emplace_back(std::move(stream));

	return true;
}


auto Select::GetSocketSize() -> uint64
{
	return mStreams.size();
}