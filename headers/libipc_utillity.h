#pragma once
#include <libipc_common.h>
#include <libipc_system.h>



namespace libipc_utillity
{
	namespace utillity
	{
		using namespace libipc_system;

		template<typename T>
		class Array
		{
		public:
			Array() : data_(nullptr), allocs_(0)
			{

			}
			Array(unsigned allocations) : Array()
			{
				if (allocations != 0)
				{
					allocs_ = allocations;
					data_ = CommitFromSystemHeap<T, HeapAccessControl::read_write>(allocs_);
				}
			}
			Array(unsigned allocations, T value) : Array(allocations)
			{
				for (auto &i : data_)
				{
					i = value;
				}
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
			unsigned allocs_;
		};

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
	}

}