#include "pch.h"
#include "IocpObj.h"


auto IocpObj::Init() -> void
{
	memset(&mOverlapped, 0, sizeof(mOverlapped));
	mBuf.buf = reinterpret_cast<CHAR*>(mClient.GetSocketInfoPtr()->buf);
	mBuf.len = mClient.GetMaxBuffSize();
}

auto IocpObj::SetClient(TcpStream client) -> void
{
	mClient = std::move(client);
}

auto IocpObj::Recv() -> int
{
	LPDWORD flags = 0;
	return 0;
}

auto IocpObj::Send() -> int
{
	return 0;
}

