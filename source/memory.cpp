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
========================================================================



*/
#include <libipc\headers\memory.h>

namespace libipc
{
	namespace memory
	{
		LargePageBlock::LargePageBlock() 
		{
			block_ = nullptr;
			bytes_allocated_ = 0;
		}

		//allocates a monolithic section of memory from the OS
		//takes a byte count as input, which will be rounded up to
		//the default page size for the OS if available or 4096
		LargePageBlock::LargePageBlock(unsigned bytes_to_allocate) : LargePageBlock()
		{
			SystemMessage e;
			block_ = system::CommitFromSystemHeap<byte, HeapAccessControl::read_write>(bytes_to_allocate);
			if (SystemError(e))
			{
				LogMessage<MessageSeverity::error_abort>(std::string("LargePagBlock(unsigned)"),e);
			}

			bytes_allocated_ = bytes_to_allocate;
		}	

		LargePageBlock::~LargePageBlock()
		{
			if (bytes_allocated_ > 0)
			{
				if (block_ != nullptr)
				{
					SystemMessage e;
					DecommitFromSystemHeap<byte>(bytes_allocated_, block_);
					if (SystemError(e))
					{
						LogMessage<MessageSeverity::error_continue>
						(std::string("~LargePageBlock()"), e);
					}
				}
				else
				{ 
					LogMessage<MessageSeverity::warning>
					(std::string("~LargePageBlock()"), std::string("LargePageBlock destruction with nullptr")); 
				}
			}
			else
			{
				LogMessage<MessageSeverity::warning>
				(std::string("~LargePageBlock()"), std::string("LargePageBlock destruction without allocation"));
			}
		}


	}
}



