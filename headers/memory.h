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
#include<libipc\headers\common.h>
#include <libipc\headers\system.h>
#include <libipc\headers\math.h>
#include <libipc\headers\types.h>

namespace libipc
{
	namespace memory
	{
		using namespace calc;
		using namespace system;
		using namespace types;

		class LargePageBlock 
		{
		public:
			LargePageBlock();
			LargePageBlock(unsigned);

			LargePageBlock(LargePageBlock&) = delete;
			LargePageBlock(LargePageBlock&&) = delete;

			~LargePageBlock();

			template<typename T, unsigned index>
			void Set(T&);

			template<typename T>
			T& operator[](size_t byte_offset)
			{
				if (byte_offset > bytes_allocated_)
				{
					LogMessage<MessageSeverity::error_continue>(std::string(""), std::string(""));
				}
				return block_ +
			}

		private:
			byte* block_;
			size_t bytes_allocated_;
		};
	}
}











