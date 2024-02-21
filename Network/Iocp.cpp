#include "pch.h"
#include "Iocp.h"

Iocp::Iocp()
{
	mHandle = ::CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
	ASSERT_CRASH(mHandle != INVALID_HANDLE_VALUE);
}

Iocp::~Iocp()
{
	CloseHandle(mHandle);
}

auto Iocp::GetHandlePtr() -> HANDLE*
{
	return &mHandle;
}

auto Iocp::Register(TcpStream& stream) -> bool
{
	return CreateIoCompletionPort(reinterpret_cast<HANDLE>(stream.GetSocketInfoPtr()->socket), mHandle, stream.GetSocketInfoPtr()->socket, 0);
}

auto Iocp::Dispatch(uint32 timeout) -> bool
{
	DWORD bytes = 0;
	ULONG_PTR key = 0;
	IocpObj* obj = nullptr;
	GetQueuedCompletionStatus(mHandle, &bytes, &key, reinterpret_cast<LPOVERLAPPED*>(&obj), timeout);
	return false;
}
