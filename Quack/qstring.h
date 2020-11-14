#pragma once

#include "pch.h"

namespace qck::Runtime
{
	class QString
	{
		private:

		char* buffer;
		size_t capacity, size;

		static std::stringstream ss;

		void resize(size_t);

		public:

		int getLength() const;

		QString();
		~QString();

		int indexOf(char) const;
		int indexOf(QString*) const;

		void append(char);
		void append(QString*);
		void append(int*, int);
		void append(int);

		template <typename T>
		bool parse(T& result)
		{
			ss.clear();
			ss.write(buffer, size);
			ss >> result;

			return ss.good();
		}

		void clear();

		static void concatenate(const QString*, const QString*, QString*);
		static void swap(QString*, QString*);
	};
}