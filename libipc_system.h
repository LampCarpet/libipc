#pragma once
#include "dependencies.h"



namespace libipc_system
{
	enum class HeapAccessControl
	{
		read_only, write_only,read_write, read_write_execute
	};

	template<typename T>
	T* CommitFromSystemHeap(unsigned);
}