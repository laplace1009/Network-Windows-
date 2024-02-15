#include "pch.h"
#include "Select.h"

Select::Select()
	:mStreams(FD_SETSIZE)
{
	FD_ZERO(&mReads);
	FD_ZERO(&mWrites);
}

auto Select::GetSocketSize() -> uint64
{
	return mStreams.size();
}

auto Select::Start(timeval time) -> void
{
	for (TcpStream& stream : mStreams)
	{
		FD_SET(stream.GetSocketInfoPtr()->socket, &mReads);
		FD_SET(stream.GetSocketInfoPtr()->socket, &mWrites);
	}
}
