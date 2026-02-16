/**
	* Copyright (C) 2026 Indonesia Chip Design Collaborative Center (ICDEC)
	*
	* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
	* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
	* OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
	* NONINFRINGEMENT.
	*/

#ifndef __CXXSTRING_HPP__
#define __CXXSTRING_HPP__

/**
	* configuration
	*/
#include "config_cxxstring.h"

/* standard header c */
#include <string.h> /* strlen, etc. */
#include <stdlib.h> /* alloc related functions */

/* standard header c++ */
#include <exception> /* for std::terminate */

/* local header */
#include "assert_helper.h"



class cxxstring;


#if 0

cxxstring operator+(cxxstring    lhs, const cxxstring   &rhs);

#if ((__cplusplus) >= 201103L) /* C++11 */
cxxstring operator+(cxxstring    lhs, cxxstring        &&rhs);

cxxstring operator+(cxxstring  &&lhs, cxxstring          rhs);

cxxstring operator+(cxxstring  &&lhs, cxxstring        &&rhs);
#endif /* ((__cplusplus) >= 201103L) */


cxxstring operator+(const char *lhs, const cxxstring     &rhs);
#endif

cxxstring operator+(const char *lhs, cxxstring            rhs);

#if ((__cplusplus) >= 201103L) /* C++11 */
cxxstring operator+(const char *lhs, cxxstring          &&rhs);
#endif


class cxxstring
{
private:
	static constexpr const char  *empty_string = "";
	static char                   dummy_char_storage;

	char                         *c_str_buf;
	size_t                        c_str_buf_len;
	size_t                        c_str_buf_strlen;

public:
	/* constructors */
	cxxstring(void);
	cxxstring(const char *str);
	cxxstring(const cxxstring   &rvalue);
	cxxstring(cxxstring        &&rvalue);

	/* destructor */
	~cxxstring(void);

	/**
		* public method
		*/

	/**
		* return c_str pointer
		*/
	inline const char * c_str(void) const
	{
		/* just alias of __non_standard__c_str_non_const */
		return this->__non_standard__c_str_non_const();
	}

	/**
		* same as c_str but without const qualifier
		* this method don't modify instance, therefore
		* can be called by constant instance
		*/
	inline       char * __non_standard__c_str_non_const(void) const
	{
		/**
			* check if current pointer refer to empty_string
			* if so, return NULL
			*/

		return (this->c_str_buf);
	}


	/**
		* overload operator
		*/


	/**
		* operator =
		*/

	/**
		* operator [] (element access)
		* indexing with square bracket
		*
		* "https://docs.arduino.cc/language-reference/en/variables/data-types/stringObject/Operators/elementAccess"
		*/
	/* r-value operator */
	char   operator[](size_t index) const
	{
		/* get current instance string pointer */
		const char *s = this->c_str();

		/* check if buffer is empty */
		if ((s == NULL) || (s == (this->empty_string)))
		{
			return '\0';
		}
		else
		{
			/* check if we attempt to access out of bound memory */
			size_t s_len = strlen(s);

			/* in attempt of accessing out of bound memory, return '\0' */
			if (index >= s_len)
			{
				return '\0';
			}
			else
			{
				/* in bound memory */
				return s[index];
			}
		}
	}

	/**
		* l-value operator, although this method don't modify object
		* the nature of l-value operator is to be modified by r-value
		* therefore don't put const here
		*/
	char  &operator[](size_t index)
	{
		char *s = this->__non_standard__c_str_non_const();

		/* check if we try to write invalid buffer or read-only buffer */
		if ((s == NULL) || (((const char *) s) == (this->empty_string)))
		{
			/* return dummy storage */
			return (cxxstring::dummy_char_storage);
		}
		else
		{
			/* check if we attempt to access memory outside of buffer
			* (not outside of string) */
			if (index >= this->__non_standard__get_buffer_length())
			{
				return (cxxstring::dummy_char_storage);
			}
			else
			{
				return s[index];
			}
		}
	}



	/**
		* copy assignment operator (big three)
		* as part of initialization
		* e.g. cxxstring a = b;
		*
		* should return *this
		*/
	cxxstring &operator=(const cxxstring   &rvalue);
#if (__cplusplus >= 201103L) /* C++11 */
	/* move assignment operator */
	cxxstring &operator=(cxxstring        &&rvalue);
#endif
	cxxstring &operator=(const char        *rvalue);


	/**
		* operator +=
		*/
	/**
		* without move semantic (copy semantic)
		*/
	cxxstring &operator+=(const cxxstring &rvalue);

	/**
		* with move semantic
		*/
#if ((__cplusplus) >= 201103L) /* C++11 */
	cxxstring &operator+=(cxxstring &&rvalue);
#endif /* ((__cplusplus) >= 201103L) */

	/**
		* with c string
		*/
	cxxstring &operator+=(const char *rvalue);

	/**
		* operator +
		*/
	/* with copy semantic */
	inline cxxstring operator+(const cxxstring &rhs) const
	{
		cxxstring lhs(*this);

		/* reuse += operator for string */
		return (lhs += rhs);
	}

	/* with move semantic */
	inline cxxstring operator+(cxxstring &&rhs) const
	{
		/*cxxstring cxxstring_rhs(rhs);*/
		cxxstring lhs(*this);

		/* reuse + operator for string */
		return (lhs += rhs);
	}

	/* with string */
	inline cxxstring operator+(const char *rhs) const
	{
		/* create new instance, since + operator shouldn't modify lhs operand */
		cxxstring lhs(*this);

		/* reuse += operator (const char *) */
		return (lhs += rhs);
	}





	/**
		* set new string to this instance, new argument should be dynamically
		* allocated buffer (created with malloc, realloc, etc.)
		*
		* you can chain this function
		*/
	inline cxxstring & __non_standard__set_new_buffer(char *new_buffer, size_t buffer_length)
	{
		/* if new_buffer is NULL or buffer_length is 0,
		* then automatically set new_buffer to NULL */
		if ((new_buffer == NULL) || (new_buffer == ((char *) (this->empty_string))) ||
			(buffer_length == 0))
		{
			return this->__non_standard__set_new_buffer(NULL, 0, 0);
		}
		else
		{
			/**
				* if not, then calculate string length
				* to guarantee that strlen not accesing out-of-bound memory,
				* set end of buffer to '\0'
				*/
			new_buffer[buffer_length - 1] = '\0';

			/* we can safely use strlen here */
			return this->__non_standard__set_new_buffer(new_buffer, buffer_length, strlen(new_buffer));
		}
	}

	inline cxxstring & __non_standard__set_new_buffer(char *new_buffer, size_t buffer_length, size_t string_length)
	{
		/* string_length should less than buffer_length */
		if (string_length >= buffer_length)
		{
			string_length = (buffer_length <= 1) ? (0) : (buffer_length - 1);
		}

		this->c_str_buf = new_buffer;
		this->c_str_buf_len = buffer_length;
		this->c_str_buf_strlen = string_length;

		return (*this);
	}

	inline size_t      __non_standard__get_buffer_length(void) const
	{
		return (this->c_str_buf_len);
	}

	inline size_t      __non_standard__get_string_length(void) const
	{
		return (this->c_str_buf_strlen);
	}

	/**
		* you can chain this function
		*/
	inline cxxstring & __non_standard__invalidate_string(void)
	{
		this->__non_standard__set_new_buffer(NULL, 0);

		return (*this);
	}

	/**
		* you can chain this function
		*/
	inline cxxstring & __non_standard__free_string_non_invalidate(void)
	{
		/* remove const qualifier */
		void *s = this->__non_standard__c_str_non_const();

		/* check if current instance had allocate string */
		if ((s == NULL) || (s == ((void *) (this->empty_string))))
		{
			/* do nothing if this instance have empty string */
		}
		else
		{
			/* current instance had allocated buffer, free it */
			free(s);

			/**
				* this function intentionally don't invalidate!
				* call to c_str() still return free'd buffer
				* usage of this buffer after free is a memory leak
				*
				* to invalidate, call __non_standard__invalidate_string()
				*/
		}

		return (*this);
	}


	static inline constexpr const char *__non_standard__shared_empty_string(void)
	{
		return cxxstring::empty_string;
	}
};

#endif /* ! defined(__CXXSTRING_HPP__) */
