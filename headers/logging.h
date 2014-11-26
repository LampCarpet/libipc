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
*/
#pragma once
#include <libipc\headers\common.h>
#include <functional>

namespace libipc
{
	namespace logging
	{
		enum class MessageSeverity
		{
			informational, warning, error_continue, error_abort
		};

		enum class LoggingMode
		{
			verbose, silent, debug
		};
		
		class SystemMessage
		{
		public:

		};

		template<MessageSeverity severity, LoggingMode mode>
		class Log
		{
		public:
			typedef handler std::function<void(const std::string)>;

			Log()
			{
				static_assert(false,'');
			}

			static void SetOutput(handler output_f)
			{
				
			}


		private:
			
		};

		template<MessageSeverity ms>
		void LogMessage(const std::string, const SystemMessage&);

		template<MessageSeverity ms>
		void LogMessage(const std::string, const std::string);


	}
}