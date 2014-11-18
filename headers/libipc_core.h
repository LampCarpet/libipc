#pragma once
#include "dependencies.h"
#include "libipc_system.h"




namespace libipc
{
	static const unsigned max_domain_depth = 8;
	static const unsigned max_domain_links = 8;
	static const unsigned max_port_per_domain = 16;
	static const unsigned max_unique_interfaces = 32;
	static const unsigned max_subscr_length = 64;
	static const unsigned max_string_length = 64;

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

	template<typename T, unsigned number_of_ts>
	class symbol_table
	{
	public:
		symbol_table() : n_str_pos_(0), allocated_(0)
		{
			str_load_.store(false);
			symbol_table_ = libipc_system::CommitFromSystemHeap<T>(number_of_ts);
			allocated_ = number_of_ts*sizeof(T);
		}

		~symbol_table()
		{
			if (allocated_ != 0) 
			{
				libipc_system::DecommitFromSystemHeap<T>(number_of_ts);
			}
		}

		int register_symbol(const T value)
		{

			while (sym_load_) { sym_load_.store(false); }
			sym_load_.store(true);
			if (n_str_pos_ < symbol_table_.max_size())
			{
				memset(&symbol_table_[n_sym_pos_], 0, number_of_ts*sizeof(T));
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
		T* symbol_table_;
	};


	

	class IpcSymbolLookupTable
	{
	protected:
		static const unsigned max_domains_ = max_domain_links*max_domain_depth;
		static const unsigned max_ports_ = max_domain_links*max_domain_depth*max_port_per_domain;
	public:


	private:
		symbol_table<void*, max_subscr_length> producers_;
		symbol_table<void*, max_subscr_length> consumers_;
		symbol_table<IpcDomain, max_domains_> domain_table_;
		symbol_table<char[max_string_length],max_domains_> string_table_;
		symbol_table<IpcPortInterfaceDescriptor, max_unique_interfaces> port_interfaces_;
	};

	struct IpcPort
	{
		void* subscribers[max_subscr_length];
		unsigned sym_name_handle_, sym_interface_handle_;
	};

	class IpcDomain
	{
	public:
		IpcDomain() : str_ref_(-1)
		{

		}

		IpcDomain(const int domain_path_name) : str_ref_(domain_path_name)
		{

		}


	private:
		
		std::array<IpcDomain*, max_domain_links> links;
		int str_ref_;
	};
}













