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

namespace libipc
{
	namespace types
	{

		typedef unsigned char u8;
		typedef signed char s8;
		typedef unsigned short u16;
		typedef signed short s16;
		typedef unsigned int u32;
		typedef signed int s32;
		
		typedef u32 handle;
		
		typedef u8 byte;

		enum class type_limits
		{

		};

		enum class handle_type
		{
			domain,
			port,
			symbol
		};
	}
}