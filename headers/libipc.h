#pragma once
#include <libipc_common.h>
#include <libipc_core.h>
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







