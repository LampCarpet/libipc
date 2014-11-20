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
=============================================================================
Interprocess communication library, (libipc)

Filename:
 		libipc.h

Version:
 		0.0.1-dev (unstable)

Referred to as:
		"libipc-header", "libipc-api", "api"

Description:
		

File debug refs:

*/
#pragma once
#include <libipc\headers\common.h>
#include <libipc\headers\core.h>
/*
	domain
	 -subscribers[]
	 -ports[]
	 -domain links[]
*/

namespace libipc
{
	using namespace libipc::core;

	extern "C"
	{
		static int Initialize
		/*
			Initializes the global symbol table object b
		*/
		( 
		 unsigned,
		 unsigned, 
		 unsigned,
		 unsigned
		 );

		Handle CreatePort(const char*, IpcPortInterfaceDescriptor);
	
		void WritePort(Handle port, const char* buffer, void* sync_obj);
		void SubscribeToPort();

		void ReadNextPacket();
	}
}







