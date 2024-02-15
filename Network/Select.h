#pragma once
#include "Types.h"
#include "TcpStream.h"
#include "mutex"


class Select
{
public:
	Select();

public:
	auto GetSocketSize() -> uint64;
	auto Start(timeval time) -> void;

private:
	std::vector<TcpStream> mStreams;
	fd_set mReads;
	fd_set mWrites;
	std::mutex mLock;
};
