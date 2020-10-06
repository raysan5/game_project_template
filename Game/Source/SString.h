#ifndef __SSTRING_H__
#define __SSTRING_H__

#include "Defs.h"

#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <assert.h>

#define TMP_STRING_SIZE	4096

class SString
{
private:

	char* str;
	unsigned int size;

public:

	// Constructors
	SString()
	{
		Alloc(1);
		Clear();
	}

	SString(unsigned int size)
	{
		if(size > 0)
			Alloc(size);
		else
			Alloc(1);

		Clear();
	}

	SString(const SString& string)
	{
		Alloc(string.size);
		strcpy_s(str, size, string.str);
	}

	SString(const char *format, ...)
	{
		size = 0;

		if(format != NULL)
		{
			static char tmp[TMP_STRING_SIZE];
			static va_list  ap;

			// Construct the string from variable arguments
			va_start(ap, format);
			int res = vsprintf_s(tmp, TMP_STRING_SIZE, format, ap);
			va_end(ap);

			if(res > 0)
			{
				Alloc(res + 1);
				strcpy_s(str, size, tmp);
			}
		}

		if(size == 0)
		{
			Alloc(1);
			Clear();
		}
	}

	// Destructor
	virtual ~SString()
	{
		if(str != NULL)
			delete[] str;
	}

	const SString& Create(const char *format, ...)
	{
		size = 0;

		if(format != NULL)
		{
			static char tmp[TMP_STRING_SIZE];
			static va_list  ap;

			// Construct the string from variable arguments
			va_start(ap, format);
			int res = vsprintf_s(tmp, TMP_STRING_SIZE, format, ap);
			va_end(ap);

			if(res > 0)
			{
				Alloc(res + 1);
				strcpy_s(str, size, tmp);
			}
		}

		if(size == 0)
		{
			Alloc(1);
			Clear();
		}

		return *this;
	}

	// Operators
	bool operator== (const SString& string) const
	{
		return strcmp(string.str, str) == 0;
	}

	bool operator== (const char* string) const
	{
		if(string != NULL)
			return strcmp(string, str) == 0;
		return false;
	}

	bool operator!= (const SString& string) const
	{
		return strcmp(string.str, str) != 0;
	}

	bool operator!= (const char* string) const
	{
		if(string != NULL)
			return strcmp(string, str) != 0;
		return true;
	}

	const SString& operator= (const SString& string)
	{
		if(string.Length() + 1 > size)
		{
			delete[] str;
			Alloc(string.Length() + 1);
		}
		else
			Clear();

		strcpy_s(str, size, string.str);

		return(*this);
	}

	const SString& operator= (const char* string)
	{
		SString t(string);
		(*this) = t;
		return *this;

		if(string != NULL)
		{
			if(strlen(string) + 1 > size)
			{
				delete[] str;
				Alloc(strlen(string)+1);
			}
			else
				Clear();

			strcpy_s(str, size, string);
		}
		else
		{
			Clear();
		}

		return(*this);
	}

	const SString& operator+= (const SString& string)
	{
		unsigned int need_size = string.Length() + Length() + 1;

		if(need_size > size)
		{
			char* tmp = str;
			Alloc(need_size);
			strcpy_s(str, size, tmp);
			delete[] tmp;
		}

		strcat_s(str, size, string.str);

		return(*this);
	}

	const SString& operator+= (const char* string)
	{
		if(string != NULL)
		{
			unsigned int need_size = strlen(string) + Length() + 1;

			if(need_size > size)
			{
				char* tmp = str;
				Alloc(need_size);
				strcpy_s(str, size, tmp);
				delete[] tmp;
			}

			strcat_s(str, size, string);
		}

		return(*this);
	}

	// Utils
	unsigned int Length() const
	{
		return strlen(str);
	}

	void Clear()
	{
		str[0] = '\0';
	}

	const char* GetString() const
	{
		return str;
	}

	unsigned int GetCapacity() const
	{
		return size;
	}

	bool Cut(unsigned int begin, unsigned int end = 0)
	{
		uint len = Length();

		if(end >= len || end == 0)
			end = len - 1;

		if(begin > len || end <= begin)
			return false;

		char* p1 = str + begin;
		char* p2 = str + end + 1;

		while(*p1++ = *p2++);

		return true;
	}

	void Trim()
	{
		// cut right --
		char* end = str + size;
		while(*--end == ' ') *end = '\0';

		// cut left --
		char* start = str;
		while(*++start == ' ');

		uint s = strlen(start);

		for(uint i = 0; i < s + 1; ++i)
			str[i] = start[i];
	}

	uint Substitute(const char* src, const char *dst)
	{
		assert(src);
		assert(dst);

		uint instances = Find(src);

		if(instances > 0)
		{
			uint src_len = strlen(src);
			uint dst_len = strlen(dst);
			uint diff = dst_len - src_len;
			uint needed_size = 1 + strlen(str) + (diff * instances);

			if(size < needed_size)
			{
				char* tmp = str;
				Alloc(needed_size);
				strcpy_s(str, size, tmp);
				delete tmp;
			}

			for(uint i = 0; i < size - src_len; ++i)
			{
				if(strncmp(src, &str[i], src_len) == 0)
				{
					// Make room
					for(uint j = strlen(str) + diff; j > i + diff; --j)
					{
						str[j] = str[j - diff];
					}

					// Copy
					for(uint j = 0; j < dst_len; ++j)
					{
						str[i++] = dst[j];
					}
				}
			}

		}

		return instances;
	}

	uint Find(const char* string) const
	{
		uint ret = 0;

		if(string != NULL)
		{
			uint len = strlen(string);

			for(uint i = 0; i < size - len; ++i)
			{
				if(strncmp(string, &str[i], len) == 0)
				{
					i += len;
					++ret;
				}
			}
		}

		return ret;
	}

private:

	void Alloc(unsigned int requiered_memory)
	{
		size = requiered_memory;
		str = new char[size];
	}

};

#endif // __SString_H__