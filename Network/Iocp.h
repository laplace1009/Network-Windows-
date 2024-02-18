#pragma once
#include "Types.h"
#include "TcpStream.h"
#include "TcpListener.h"

class Iocp
{
public:
	Iocp();
	~Iocp();

public:
	auto GetHandlePtr() -> HANDLE*;
	auto Register(TcpStream* stream) -> bool;
	auto Dispatch() -> bool;

private:
	HANDLE mHandle;
};

