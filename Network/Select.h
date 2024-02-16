#pragma once
#include "Types.h"
#include "TcpStream.h"
#include "TcpListener.h"
#include "mutex"


class Select
{
public:
	Select();

public:
	auto GetSocketSize() -> uint64;
	auto Start(TcpListener& server, timeval time) -> int;
	auto SubScribes(TcpStream stream) -> void;
	auto SubScribes(std::initializer_list<TcpStream> list) -> void;

private:
	std::vector<TcpStream> mStreams;
	fd_set mReads;
	fd_set mWrites;
};
