#pragma once
#include "Types.h"
#include "TcpStream.h"


class Select
{
public:
	Select();

public:
	auto GetSocketSize() -> uint64;

private:
	std::vector<TcpStream*> mStreams;
};
