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

		class File<OperatingSystem::Windows>
		{
		public:
			File(HANDLE, std::string); //Transfer ownership of open file to object
			File(std::string, AccessControl);
			File(std::string, AccessControl, FileState);
			File(std::string, bool);

			bool is_open();
			bool try_open();

			File<OperatingSystem::Windows>& load();

			File<OperatingSystem::Windows>& DesiredAccessMode();
			File<OperatingSystem::Windows>& ShareMode();
			File<OperatingSystem::Windows>& CreationMode();

			template<typename T>
			T& open_as();

			template<typename T>
			T& open_as(unsigned);

			template<typename F, typename R>
			T open_as(std::function<R(F&)>);

			bool close();

			utillity::Array<u8> copy(unsigned,unsigned);
			bool write(unsigned, const utillity::Array<u8>&);

		private:
			inline bool can_load_()
			{
				auto state = state_.load();
				return file_addr_.length() != 0 && ac_.load() != AccessControl::no_init && 
					   (state != FileState::file_not_init || state != FileState::file_not_found);
			}

			std::string file_addr_;
			std::atomic<HANDLE> sys_file_ = nullptr;
			std::atomic<size_t> file_size_ = 0;
			std::atomic<FileState> state_ = FileState::file_not_init;
			std::atomic<AccessControl> ac_ = AccessControl::no_init;

			struct 
			{
				DWORD ShareMode;
				DWORD AccessMode;
				DWORD CreationMode;
				DWORD Flags;
			} default_attributes_;
		};
		
		bool
		File<OperatingSystem::Windows>::is_open()
		{
			if (can_load_()){ return state_.load() == FileState::file_exists_open_handle; }
			else{ return false; }
		}

		File<OperatingSystem::Windows>& 
		File<OperatingSystem::Windows>::load()
		{
			if (can_load_())
			{
				SystemMessage e(std::string("load()"));
				auto handle = CreateFile(file_addr_.c_str(),
										 default_attributes_.AccessMode,
										 default_attributes_.ShareMode,
										 NULL,
										 default_attributes_.CreationMode,
										 default_attributes_.Flags,
										 NULL
										 );
				if (SystemError(e))
				{
					
				}

				sys_file_.store(handle);
			}

			return (*this);
		}


		template<typename R>
		R File<OperatingSystem::Windows>::open(std::function<R(u8*, unsigned)> process)
		{

		}
	}

}



