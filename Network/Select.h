#pragma once
#include "Types.h"
#include "TcpStream.h"
#include "TcpListener.h"
#include "mutex"


class Select
{

public:
	auto Init() -> void;
	auto Run(TcpListener& server, const timeval* time) -> int;
	auto SubScribe(TcpStream&& stream) -> bool;

public:
	auto GetSocketSize() -> uint64;

private:
	std::vector<TcpStream> mStreams;
	fd_set mReads;
	fd_set mWrites;
};
