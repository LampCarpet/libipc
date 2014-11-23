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
#include <libipc\libipc.h>
#include <libipc\headers\memory.h>

namespace libipc
{
	namespace core
	{
		memory::LargePageBlock table(23);

		

		template<typename T>
		class symbol_table
		{
		public:
			symbol_table(unsigned number_of_ts)
			: n_str_pos_(0),symbol_table_(number_of_ts)
			{
				str_load_.store(false);
			}

			~symbol_table()
			{
			
			}

			int register_symbol(const T value)
			{
				std::atomic<int> spin = 0;

				while (sym_load_) { ++spin; }
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
	}

}