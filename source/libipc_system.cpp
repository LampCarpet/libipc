#include "libipc_system.h"

#ifdef WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#else
static_assert(false, "Unsupported operating system type");
#endif

namespace libipc_system
{
#ifdef WIN32
	typedef DWORD OS_Flag_Type;
#endif

	namespace details
	{
		template<HeapAccessControl flag>
		OS_Flag_Type OS_Flag()
		{
			switch (flag)
			{
			case HeapAccessControl::read_write_execute:
				return PAGE_EXECUTE_READWRITE;
			case HeapAccessControl::read_only:
				return PAGE_EXECUTE_READ;
			case HeapAccessControl::read_write:
				return PAGE_READWRITE;
			case HeapAccessControl::write_only:
				return PAGE_EXECUTE_WRITECOPY;
			default:
				static_assert(false, "invalid flag");
			}
		}
	}

	template<typename T, HeapAccessControl os_flag>
	T* CommitFromSystemHeap(unsigned count)
	{
		void* tmp_ptr = nullptr;
#ifdef WIN32
		tmp_ptr = VirtualAlloc(NULL, size_in_bytes*sizeof(T), MEM_COMMIT,details::OS_Flag<os_flag>());
#endif
		return reinterpret_cast<T*>(tmp_ptr);
	}

	template<typename T>
	void DecommitFromSystemHeap(unsigned count, T* addr)
	{
		if (count == 0) { return; }
#ifdef WIN32
		VirtualFree(addr, count*sizeof(T), MEM_DECOMMIT);
#endif
	}
}