#pragma once
#include "dependencies.h"
#include "lib_ipc_core.h"
/*
	domain
	 -subscribers[]
	 -ports[]
	 -domain links[]
*/

namespace libipc
{
	extern "C"
	{

		static void InitializeIpcInterface(const std::vector<IpcPortInterfaceDescriptor>);


		void CreatePort(const char*);
	
		void SubscribeToPort();

		void ReadNextPacket();
	}
}







