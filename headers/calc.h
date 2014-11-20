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
	namespace calc
	{
		using namespace types;

		enum class ObjectMapLims
		{
			u8_max_links_per_domain,
			u16_max_links_per_domain,
			u32_max_links_per_domain,
			u8_max_ports_per_domain,
			u16_max_ports_per_domain,
			u32_max_ports_per_domain
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