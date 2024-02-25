#include "pch.h"
#include "Select.h"

auto Select::Init() -> void
{
	mStreams.reserve(FD_SETSIZE);
}

auto Select::Run(TcpListener& server, const timeval* time = nullptr) -> int32
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

	return retVal;
}

// 무조건 한번에 다 받아야 함
auto Select::ReadSet(TcpStream& stream) -> int32
{
	if (FD_ISSET(stream.GetSocketInfoPtr()->socket, &mReads))
	{
		int32 recvLen = 0;
		do {
			int32 bytesRecved = stream.Recv(recvLen);

			if (bytesRecved == SOCKET_ERROR)
			{
				return SOCKET_ERROR;
			}
			
			recvLen += bytesRecved;

		} while (static_cast<uint32>(recvLen) < stream.GetSocketInfoPtr()->recvBytes);

		stream.GetSocketInfoPtr()->recvBytes = 0;
		return recvLen;
	}

	return -1;
}


auto Select::WriteSet(TcpStream& stream, CHAR* message, uint32 msgLength) -> int32
{
	if (msgLength == 0) return 0;
	
	if (FD_ISSET(stream.GetSocketInfoPtr()->socket, &mWrites))
	{
		int32 sendLen = 0;
		do {
			int32 bytesSent = stream.Send(message, msgLength, sendLen, 1);
			if (bytesSent == SOCKET_ERROR)
			{
				return SOCKET_ERROR;
			}

			sendLen += bytesSent;

		} while (static_cast<uint32>(sendLen) < stream.GetSocketInfoPtr()->sendBytes);

		stream.GetSocketInfoPtr()->sendBytes = 0;
		return sendLen;
	}
	
	return -1;
}



auto Select::SubScribe(TcpStream&& stream) -> bool
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