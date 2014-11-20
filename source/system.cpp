/*
Copyright 2015 cyclical.state@gmail.com

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.





*/
#include <libipc\headers\common.h>
#include <libipc\headers\system.h>
#ifdef WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#else
static_assert(false, "Unsupported operating system type");
#endif

namespace libipc
{
	namespace system
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
			tmp_ptr = VirtualAlloc(NULL, size_in_bytes*sizeof(T), MEM_COMMIT, details::OS_Flag<os_flag>());
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
			tmp_ptr = VirtualAlloc(NULL, size_in_bytes*sizeof(T), MEM_COMMIT, details::OS_Flag<os_flag>());
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

}