#pragma once
#include <libipc_common.h>





namespace libipc
{
	namespace calc
	{
		typedef unsigned char u8;
		typedef signed char s8;
		typedef unsigned short u16;
		typedef signed short s16;
		typedef unsigned int u32;
		typedef signed int s32;

		enum class ObjectMapLims
		{
			u8_max_links_per_domain,
			u16_max_links_per_domain,
			u32_max_links_per_domain,
			u8_max_ports_per_domain,
			u16_max_ports_per_domain,
			u32_max_ports_per_domain
		};

		enum class type_limits
		{

		};

		enum class handle_type
		{
			domain,
			port,
			symbol
		};

		template<ObjectMapLims, ObjectMapLims>
		class ObjectMap
		{
		public:
			ObjectMap()
			{
				static_assert(false, "ObjectMapLims enum not supported")
			}

		private:
		};

		/*

		*/
		class ObjectMap
			<ObjectMapLims::u8_max_links_per_domain,
			ObjectMapLims::u8_max_ports_per_domain>
		{
		public:
			ObjectMap(u8, u8);

			const handle_type ResolveHandleType(u32) const;

			auto ResolveHandle(u32) -> decltype();

			const u8 links_per_domain;
			const u8 ports_per_domain;
		};
	}
}