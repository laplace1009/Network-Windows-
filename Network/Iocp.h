#pragma once
#include "Types.h"
#include "TcpStream.h"
#include "TcpListener.h"
#include "IocpObj.h"

class Iocp
{
public:
	Iocp();
	~Iocp();

public:
	auto GetHandlePtr() -> HANDLE*;
	auto Register(TcpStream& stream) -> bool;
	auto Dispatch(uint32 timeout = INFINITE) -> bool;

private:
	HANDLE mHandle;
};

