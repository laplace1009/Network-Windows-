#include "pch.h"
#include "Select.h"

Select::Select()
{
	mStreams.reserve(FD_SETSIZE);
}

auto Select::GetSocketSize() -> uint64
{
	return mStreams.size();
}

auto Select::Start(TcpListener& server, timeval time) -> int
{
	FD_ZERO(&mReads);
	FD_ZERO(&mWrites);
	FD_SET(server.GetServerSocketPtr()->GetSocketInfoPtr()->socket, &mReads);
	for (TcpStream& stream : mStreams)
	{
		FD_SET(stream.GetSocketInfoPtr()->socket, &mReads);
		FD_SET(stream.GetSocketInfoPtr()->socket, &mWrites);
	}
	return select(0, &mReads, &mWrites, NULL, NULL);
}

auto Select::SubScribes(TcpStream stream) -> void
{
	mStreams.emplace_back(std::move(stream));
}

auto Select::SubScribes(std::initializer_list<TcpStream> list) -> void
{
	mStreams.insert(mStreams.end(), std::make_move_iterator(list.begin()), std::make_move_iterator(list.end()));
}
