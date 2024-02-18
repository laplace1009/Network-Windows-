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

