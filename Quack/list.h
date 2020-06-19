#pragma once

#include "pch.h"

namespace qck
{
	// ========================================================================================================================================
	// List
	// ========================================================================================================================================

	template <typename T>
	class List
	{
		private:

		const int MINIMUM_CAPACITY = 8;

		int capacity, count;
		T* data;

		int nearestPO2(int size)
		{
			return size > MINIMUM_CAPACITY ? (int) std::pow(2.0, std::ceil(std::log2(size))) : MINIMUM_CAPACITY;
		}

		void resize(int size)
		{
			if (size < MINIMUM_CAPACITY)
				size = MINIMUM_CAPACITY;

			T* prev = data;

			capacity	= size;
			data		= new T[capacity];

			if (prev != nullptr)
			{
				int max = count < capacity ? count : capacity;
				for (int i = 0; i < max; ++i)
					data[i] = prev[i];

				delete[] prev;
			}
		}

		public:

		// ====================================================================================================================================
		// Accessors
		// ====================================================================================================================================

		inline int getCount()			{return count;}
		inline T* begin()				{return &data[0];}
		inline T* end()					{return &data[count];}
		inline const T* begin() const	{return &data[0];}
		inline const T* end() const		{return &data[count];}

		// ====================================================================================================================================
		// Constructor / Destructor
		// ====================================================================================================================================

		List()
		{
			capacity	= 0;
			count		= 0;
			data		= nullptr;
		}

		List(size_t reserved)
		{
			capacity	= nearestPO2((int) reserved);
			count		= 0;
			data		= new T[capacity];
		}

		List(std::initializer_list<T> values)
		{
			capacity	= nearestPO2(values.size());
			count		= values.size();
			data		= new T[capacity];

			for (int i = 0; i < count; ++i)
				data[i] = *(values.begin() + i);
		}

		~List()
		{
			if (data != nullptr)
				delete[] data;
		}

		// ====================================================================================================================================
		// At
		// ====================================================================================================================================

		bool at(int index, T& result)
		{
			if (index < 0 || index >= count)
				return false;

			result = data[index];

			return true;
		}

		// ====================================================================================================================================
		// Search
		// ====================================================================================================================================

		int search(const T& value)
		{
			for (int i = 0; i < count; ++i)
				if (data[i] == value)
					return i;

			return -1;
		}

		bool contains(const T& value)
		{
			for (int i = 0; i < count; ++i)
				if (data[i] == value)
					return true;

			return false;
		}

		// ====================================================================================================================================
		// Insert
		// ====================================================================================================================================

		void insert(const T& value)
		{
			if (count >= capacity)
				resize(capacity << 1);

			data[count] = value;

			++count;
		}

		void insert(const T& value, int index)
		{
			qckAssert(index >= 0 && index <= count, "Index out of range");

			if (count >= capacity)
				resize(capacity << 1);

			for (int i = count; i > index; --i)
				data[i] = data[i - 1];

			data[index] = value;

			++count;
		}

		// ====================================================================================================================================
		// Remove
		// ====================================================================================================================================

		void remove()
		{
			if (count > 0)
				--count;
		}

		void remove(int index)
		{
			qckAssert(index >= 0 && index < count, "Index out of range");

			for (int i = index, j = count - 1; i < j; ++i)
				data[i] = data[i + 1];

			--count;
		}

		// ====================================================================================================================================
		// Misc
		// ====================================================================================================================================

		void clear()
		{
			count = 0;
		}

		void trim()
		{
			int po2 = nearestPO2(count);
			if (po2 < capacity)
				resize(po2);
		}

		// ====================================================================================================================================
		// Operators
		// ====================================================================================================================================

		const T& operator [](int index)
		{
			qckAssert(index >= 0 && index < count, "Index out of range");
			return data[index];
		}
	};
}