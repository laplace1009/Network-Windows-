#pragma once
#include "Types.h"
#include "TcpStream.h"
#include "TcpListener.h"
#include "mutex"


class Select
{

public:
	auto Init() -> void;
	auto Run(TcpListener& server, const timeval* time) -> int32;
	auto ReadSet(TcpStream& stream) -> int32;
	auto WriteSet(TcpStream& stream, BYTE* message, uint32 msgLength) -> int32;
	auto SubScribe(TcpStream&& stream) -> bool;

public:
	auto GetSocketSize() -> uint64;

private:
	std::vector<TcpStream> mStreams;
	fd_set mReads;
	fd_set mWrites;
};
