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

#pragma once
#include <libipc\headers\common.h>
#include <libipc\headers\types.h>



namespace libipc
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