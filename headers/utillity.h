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
#include <libipc\headers\utillity.h>
#include <libipc\headers\system.h>


namespace libipc
{
	namespace utillity
	{
		using namespace system;

		template<typename T>
		class Array
		{
		public:
			Array() : data_(nullptr), allocs_(0)
			{

			}

			Array(size_t allocations) : Array()
			{
				if (allocations != 0)
				{
					allocs_ = allocations;
					data_ = CommitFromSystemHeap<T, HeapAccessControl::read_write>(allocs_);
				}
			}
			
			Array(size_t allocations, T value) : Array(allocations)
			{
				for (auto &i : data_)
				{
					i = value;
				}
			}

			Array(size_t allocations, T* block)
			{
				if (allocation == 0)
				{

				}
			}
			const size_t Size() const
			{
				return alloc_;
			}

			~Array()
			{
				DecommitFromSystemHeap<T>(allocs_d, ata_);
			}



			T& operator[](unsigned index)
			{
				if (index < allocs_) { return data_[index]; }
				else { return T(0); }
			}


		private:
			T* data_;
			size_t allocs_;
		};

		class Log
		{
		public:
			template<MessageSeverity ms>
			void operator()();
			
			template<MessageSeverity ms, typename T>
			static void SetHandler(std::functiuo);

		private:

		};

		

		template<typename ...T>
		class CacheableObject
		{
			size_t pos_;
		public:

			inline u32 Range();

			auto operator[](size_t pos)->decltype(vars_[pos])
			{
				return vars_[pos];
			}

			size_t Elements()
			{
				return sizeof(T);
			}

			auto NextElement() -> decltype(vars_[pos])
			{
				if (pos + 1 > sizeof(vars_))
				{
					++pos;
					return vars_[pos];
				}
			}

		private:

			T ... vars_;
		};

		typedef CacheableObject<int,std::string,int> test;	
						

		template<typename T>


		template<typename ...T>
		class StripedArray
		{
		public:
			StripedArray() : count_(0)
			{
				

			}

			StripedArray(unsigned count)
			{
				if (count == 0) { return; }
				count_ = count;
			}

			StripedArray(unsigned count, T... values) : StripedArray(count)
			{
				unsigned v_iter = 0;
				for (auto t_ptr : data_)
				{
					for (auto &i : t_ptr)
					{
						i = values[v_iter];
					}
					++v_iter;
				}
			}

		private:
			T* ... *data_; //multidimensional array of t's
			const unsigned count_;
		};

		template<typename ... T>
		bool Is(T ... vars, T c)
		{
			for (auto i : vars)
			{
				if (i == c) { return true; }
			}
			return false;
		}

		template<typename exit_f>
		class ScopeGuard
		{
		public:
			ScopeGuard();

		};

	}

}