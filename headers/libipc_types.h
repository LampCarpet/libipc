#pragma once
#include <libipc_common.h>

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