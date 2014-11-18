#pragma once
#include <dependencies.h>



namespace libipc_utillities
{
	template<typename T>
	class Array
	{
	public:
		Array() : data_(nullptr), allocs_(0)
		{

		}

		Array(unsigned allocations) : Array()
		{
			if (size != 0) { allocs_ = { size }, data_ = new[allocs_]; }
		}
		
		~Array()
		{
			delete[] data_;
		}

		T& operator[](unsigned index)
		{
			if (index < allocs_) { return data_[index]; }
			else { return T(0);}
		}

		
	private:
		T* data_;
		unsigned allocs_;
	};

}