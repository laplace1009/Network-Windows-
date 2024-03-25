#pragma once
#include "Types.h"

// ������ �����ͷ� �Ű������� ����� �ٿ��ִ� �±�
#define OUT
// �԰ݸ� ���߰� ������� �ʴ� �Ű����� �տ� �ٿ� �ִ� �±�
#define NOT_USED

// �⺻���� [[nodiscard]] ��ũ��
#define NODISCARD [[nodiscard]]

// �޽����� �����ϴ� [[nodiscard]] ��ũ��
#if __cplusplus >= 202002L  // C++20 �̻��� ��쿡�� �޽��� ���� ���� ��� ����
#define NODISCARD_MSG(msg) [[nodiscard(msg)]]
#else
#define NODISCARD_MSG(msg) [[nodiscard]]
#endif

#define UN_USED [[maybe_unused]]


#define XALLOCATE(size)	PoolAllocator::Allocate(size)
#define XRELEASE(ptr)	PoolAllocator::Release(ptr)

// �ǵ������� ũ������ ���� ���� ��ũ��1
#define CRASH(cause)						\
{											\
	uint32* crash = nullptr;				\
	__analysis_assume(crash != nullptr);	\
	*crash = 0xDEADBEEF;					\
}											

// �ǵ������� ũ������ ���� ���� ��ũ��2
#define ASSERT_CRASH(expr)					\
{											\
	if ((expr == false))					\
	{										\
		CRASH("ASSERT_CRASH");				\
		__analysis_assume(expr);			\
	}										\
}