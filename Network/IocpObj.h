#pragma once
#include "Types.h"
#include "TcpStream.h"
#include "TcpListener.h"

class IocpObj
{
public:
	auto Init() -> void;
	auto SetClient(TcpStream client) -> void;
	auto Recv() -> int;
	auto Send() -> int;

private:
	OVERLAPPED mOverlapped;
	TcpStream mClient;
	WSABUF mBuf;
};

