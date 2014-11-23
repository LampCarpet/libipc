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
#include <libipc\headers\utillity.h>


namespace libipc
{
	namespace system
	{
		enum class HeapAccessControl
		{
			read_only, write_only, read_write, read_write_execute
		};

		enum class MessageSeverity
		{
			informational, warning, error_continue, error_abort
		};

		class SystemMessage
		{
		public:

		};

		template<MessageSeverity ms>
		void LogMessage(const std::string, const SystemMessage&);

		template<MessageSeverity ms>
		void LogMessage(const std::string, const std::string);

		//If SystemError(...) returns true then a fault has occured and is stored in the supplied class
		//otherwise the return will reflect the os's success code.
		bool SystemError(SystemMessage&);

		template<typename T, HeapAccessControl OS_flag = HeapAccessControl::read_write>
		byte* CommitFromSystemHeap(unsigned count = 1);

		template<typename T>
		void DecommitFromSystemHeap(unsigned, T*);
	}
}