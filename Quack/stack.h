#pragma once

#include "pch.h"

namespace qck::Runtime
{
	// ========================================================================================================================================
	// Stack
	// ========================================================================================================================================

	class Stack
	{
		private:

		typedef unsigned char* byte;

		const size_t STACK_SIZE = 512;

		byte* buffer;
		size_t offset;

		public:

		Stack();
		~Stack();

		size_t getOffset();

		template <typename T>
		T* push()
		{
			if (offset + sizeof(T) > STACK_SIZE)
				throw "Stack overflow";

			new (buffer) T();
			offset += sizeof(T);

			return reinterpret_cast<T*>(buffer - offset);
		}

		template <typename T>
		void push(const T& value)
		{
			if (offset + sizeof(T) > STACK_SIZE)
				throw "Stack overflow";

			new (buffer) T(value);
			offset += sizeof(T);
		}

		template <typename T>
		void pop()
		{
			if (offset - sizeof(T) < 0)
				throw "Stack error";
			
			offset -= sizeof(T);
			reinterpret_cast<T*>(buffer + offset)->~T();
		}

		template <typename T>
		void pop(T& result)
		{
			if (offset - sizeof(T) < 0)
				throw "Stack error";
			
			auto ptr = reinterpret_cast<T*>(buffer + offset);

			offset -= sizeof(T);
			result = *ptr;
			ptr->~T();
		}

		template <typename T>
		T* peek()
		{
			if (offset - sizeof(T) < 0)
				throw "Stack error";

			return reinterpret_cast<T*>(buffer + offset);
		}

		template <typename T>
		T* peek(int count)
		{
			int index = offset - sizeof(T) * count;

			if (index < 0)
				throw "Stack error";

			return reinterpret_cast<T*>(buffer + index);
		}

		template <typename T>
		T* get(size_t index)
		{
			if (offset - sizeof(T) < 0)
				throw "Stack error";

			return reinterpret_cast<T*>(buffer + index);
		}
	};
}