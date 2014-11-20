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
	     core.h

Version: 
		0.0.1-dev (unstable)
		
Referred to as: 
		 "core", "Core", "core.h", "libipc-core"

Description: 
	     Core defines internal structures and classes used to generate, manage and co-ordinate
		 the memory space and functionality exposed by libipc.

File debug refs:
				\core::, 0x01, (type of: debug namespace)

*/
#pragma once
#include <libipc\headers\common.h>
#include <libipc\headers\system.h>
#include <libipc\headers\utillity.h>


namespace libipc
{
	namespace core
	{
		typedef unsigned Handle;

		static unsigned max_domain_depth = 8;
		static unsigned max_domain_links = 8;

		static unsigned max_unique_interfaces = 32;
		static unsigned max_subscr_length = 64;

		static const unsigned max_string_length = 64;
		static const unsigned max_port_per_domain = 16;

		enum PortAccessModifiers
		{
			read_only, read_write, write_only, read_write_execute
		};

		enum PortLockMode
		{
			no_lock, mutex
		};

		struct IpcPortInterfaceDescriptor
		{
			/* */
			const unsigned packet_overhead; //the containing packet size in bytes
			const unsigned read_buffer_length, write_buffer_length; //number of packets in buffer
			const unsigned read_packet_data_size, write_packet_data_size; //size of raw buffer

			PortLockMode lock_mode;
			PortAccessModifiers modifier;
			static char interface_type_name[max_string_length];
		};

		template<typename T>
		class symbol_table
		{
		public:
			symbol_table(unsigned number_of_ts)
				: n_str_pos_(0),
				symbol_table_(number_of_ts)
			{
				str_load_.store(false);
			}

			~symbol_table()
			{

			}

			int register_symbol(const T value)
			{

				while (sym_load_) { sym_load_.store(false); }
				sym_load_.store(true);
				if (n_str_pos_ < symbol_table_.max_size())
				{
					memset(&symbol_table_[n_sym_pos_], 0, sizeof(T));
					memcpy_s(&symbol_table_, sizeof(T), &value, sizeof(T));

					auto r_tmp = n_str_pos_.load();
					++n_sym_pos_;
					sym_load_.store(false);
					return r_tmp;
				}
				else{ sym_load_.store(false); return -1; }
			}

			T get_symbol(unsigned handle) const
			{
				if (handle < n_str_pos_)
				{
					return symbol_table_[handle];
				}
			}

		private:
			std::atomic<int> n_sym_pos_;
			std::atomic_bool sym_load_;
			libipc_utillity::Array<T> symbol_table_;
		};




		class IpcSymbolTable
			: symbol_table<char[max_string_length]>,
			symbol_table<IpcPortInterfaceDescriptor>
		{
		public:
			IpcSymbolTable(unsigned, unsigned);

		private:
			unsigned const max_ports_, max_domains_;
		};

		struct IpcPort
		{
			unsigned unique_handle;
			unsigned sym_name_handle;
			unsigned sym_interface_handle;
		};

		class IpcDomain
		{
		public:
			IpcDomain() : str_ref_(0)
			{

			}
			IpcDomain(const int domain_path_name_id)
				: str_ref_(domain_path_name_id), links(max_domain_links, nullptr)
			{

			}

			bool IsInitialized()
			{
				if (str_ref_ == 0) { return false; }
				return true;
			}

		private:
			symbol_table<IpcPort> ports_;
			libipc_utillity::Array<IpcDomain*> links_;
			unsigned str_ref_;
		};
	}

}













