#include "pch.h"
#include "Select.h"

Select::Select()
	:mStreams(FD_SETSIZE)
{
	
}

auto Select::GetSocketSize() -> uint64
{
	return mStreams.size();
}
