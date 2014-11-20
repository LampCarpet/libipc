#pragma once
#include <libipc_common.h>
#include <libipc_system.h>



namespace libipc_system
{
	namespace system
	{
		enum class HeapAccessControl
		{
			read_only, write_only, read_write, read_write_execute
		};

		template<typename T, HeapAccessControl OS_flag = HeapAccessControl::read_write>
		T* CommitFromSystemHeap(unsigned count = 1);

		template<typename T>
		void DecommitFromSystemHeap(unsigned, T*);
	}
}