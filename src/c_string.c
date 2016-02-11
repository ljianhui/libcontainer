#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include "c_string.h"

#define GET_NEW_CAPACITY(len) ((len<1024*1024)?(len)+((len)>>1)+1:len+1024*1024)
#define IS_SPACE_CHAR(c) ((c) == ' ' || (c) == '\r' || (c) == '\n' || (c) == '\t')

struct c_string
{
	char *buf;
	int len;
	int capacity;
};

static c_string* c_string_create_capacity(int capacity)
{
	c_string *str = (c_string*)malloc(sizeof(c_string));
	if (str == NULL)
	{
		return NULL;
	}

	str->buf = (char*)malloc(sizeof(char) * (capacity + 1));
	if (str->buf == NULL)
	{
		free(str);
		return NULL;
	}
	str->buf[0] = '\0';
	str->len = 0;
	str->capacity = capacity;
	return str;
}

static int c_string_resize(c_string *str, int capacity, int cpy)
{
	if (capacity <= str->capacity)
	{
		return 1;
	}

	char *cstr = (char*)malloc(sizeof(char) * (capacity+1));
	if (cstr == NULL)
	{
		return 0;
	}

	if (cpy)
	{
		memcpy(cstr, str->buf, str->len + 1);
	}
	if (str->buf != NULL)
	{
		free(str->buf);
	}
	str->buf = cstr;
	str->capacity = capacity;
	return 1;
}

static void c_string_remove_bytes(c_string *dst, const char *bytes, int n)
{
	int pos = 0;
	while ((pos = c_string_find_bytes(dst, pos, dst->len, bytes, n)) != C_STRING_NPOS)
	{
		c_string_remove_range(dst, pos, pos+n);
	}
}

static void c_string_replace_bytes(c_string *dst, const char *old_bytes, int old_len,
                                    const char *new_bytes, int new_len)
{
	if (old_len == new_len && memcmp(old_bytes, new_bytes, old_len) == 0)
	{
		return;
	}
	
	int pos = 0;
	while ((pos = c_string_find_bytes(dst, pos, dst->len, old_bytes, old_len)) != C_STRING_NPOS)
	{
		c_string_replace_range_bytes(dst, pos, pos + old_len, new_bytes, new_len);
		pos += new_len;
	}
}

c_string* c_string_create()
{
	return c_string_create_capacity(0);
}

c_string* c_string_create_char(char c, int n)
{
	c_string *str = c_string_create_capacity(n);
	if (str == NULL)
	{
		return NULL;
	}

	memset(str->buf, (int)c, n);
	str->buf[n] = '\0';
	if (c != '\0')
	{
		str->len = n;
	}
	else
	{
		str->len = 0;
	}
	return str;
}

c_string* c_string_create_cstr(const char *cstr)
{
	if (cstr == NULL)
	{
		return NULL;
	}

	size_t len = strlen(cstr);
	c_string *str = c_string_create_capacity(len);
	if (str == NULL)
	{
		return NULL;
	}

	strncpy(str->buf, cstr, len);
	str->buf[len] = '\0';
	str->len = len;
	return str;
}

c_string* c_string_create_bytes(const char *bytes, int n)
{
	if (bytes == NULL || n < 1)
	{
		return NULL;
	}

	c_string *str = c_string_create_capacity(n);
	if (str == NULL)
	{
		return NULL;
	}

	memcpy(str->buf, bytes, n);
	str->buf[n] = '\0';
	str->len = n;
	return str;
}

c_string* c_string_create_sub(const c_string *src, int begin, int end)
{
	if (src == NULL || end < 0 || end < begin || end > src->len)
	{
		return NULL;
	}

	c_string *str = c_string_create_capacity(end - begin);
	if (str == NULL)
	{
		return NULL;
	}

	memcpy(str->buf, src->buf + begin, end - begin);
	str->buf[end - begin] = '\0';
	str->len = end - begin;
	return str;
}

c_string* c_string_clone(const c_string *src)
{
	if (src == NULL)
	{
		return NULL;
	}

	c_string *str = c_string_create_capacity(src->capacity);
	if (str == NULL)
	{
		return NULL;
	}

	memcpy(str->buf, src->buf, src->len);
	str->buf[src->len] = '\0';
	str->len = src->len;
	return str;
}

void c_string_destroy(c_string *str)
{
	if (str == NULL)
	{
		return;
	}

	if (str->buf != NULL)
	{
		free(str->buf);
	}
	free(str);
}

int c_string_assign(c_string *dst, const c_string *src)
{
	if (src == NULL)
	{
		return 0;
	}
	return c_string_assign_bytes(dst, src->buf, src->len);
}

int c_string_assign_char(c_string *dst, char c)
{
	if (dst == NULL)
	{
		return 0;
	}
	return c_string_assign_bytes(dst, &c, 1);
}

int c_string_assign_cstr(c_string *dst, const char *src)
{
	if (src == NULL)
	{
		return 0;
	}
	return c_string_assign_bytes(dst, src, (int)strlen(src));
}

int c_string_assign_bytes(c_string *str, const char *bytes, int n)
{
	if (str == NULL || bytes == NULL || n < 0)
	{
		return 0;
	}

	if (n > str->capacity)
	{
		int ret = c_string_resize(str, GET_NEW_CAPACITY(n), 0);
		if (ret == 0)
		{
			return 0;
		}
	}
	memcpy(str->buf, bytes, n);
	str->buf[n] = '\0';
	str->len = n;
	return 1;
}

int c_string_assign_format(c_string *dst, const char *format, ...)
{
	if (dst == NULL || format == NULL)
	{
		return 0;
	}

	int len = (int)strlen(format);
	va_list arg_ptr;
	int bytes = 0;
	while (1)
	{
		va_start(arg_ptr, format);
		bytes = vsnprintf(dst->buf, dst->capacity, format, arg_ptr);
		if (bytes < dst->capacity)
		{
			va_end(arg_ptr);
			break;
		}
		len = len > dst->capacity ? len : dst->capacity;
		if (!c_string_resize(dst, GET_NEW_CAPACITY(len), 0))
		{
			va_end(arg_ptr);
			return 0;
		}
		va_end(arg_ptr);
	}
	
	dst->len = bytes;
	return 1;
}

int c_string_append(c_string *dst, const c_string *str)
{
	if (str == NULL)
	{
		return 0;
	}
	return c_string_append_bytes(dst, str->buf, str->len);
}

int c_string_append_char(c_string *dst, char c)
{
	if (dst == NULL)
	{
		return 0;
	}
	return c_string_append_bytes(dst, &c, 1);
}

int c_string_append_cstr(c_string *dst, const char *cstr)
{
	if (cstr == NULL)
	{
		return 0;
	}
	return c_string_append_bytes(dst, cstr, (int)strlen(cstr));
}

int c_string_append_bytes(c_string *dst, const char *bytes, int n)
{
	if (dst == NULL || bytes == NULL || n <= 0)
	{
		return 0;
	}

	if (n > dst->capacity - dst->len)
	{
		int ret = c_string_resize(dst, GET_NEW_CAPACITY(dst->len + n), 1);
		if (ret == 0)
		{
			return 0;
		}
	}
	memcpy(dst->buf + dst->len, bytes, n);
	dst->len += n;
	dst->buf[dst->len] = '\0';
	return 1;
}

int c_string_append_format(c_string *dst, const char *format, ...)
{
	if (dst == NULL || format == NULL)
	{
		return 0;
	}

	int len = (int)strlen(format);
	va_list arg_ptr;
	int bytes = 0;
	while (1)
	{
		va_start(arg_ptr, format);
		bytes = vsnprintf(dst->buf + dst->len, dst->capacity - dst->len, format, arg_ptr);
		if (bytes < dst->capacity - dst->len)
		{
			va_end(arg_ptr);
			break;
		}
		len = len > dst->capacity ? len : dst->capacity;
		if (!c_string_resize(dst, GET_NEW_CAPACITY(len), 1))
		{
			va_end(arg_ptr);
			return 0;
		}
		va_end(arg_ptr);
	}
	dst->len += bytes;
	return 1;
}

int c_string_add(c_string *dst, int pos, const c_string *str)
{
	if (str == NULL)
	{
		return 0;
	}
	return c_string_add_bytes(dst, pos, str->buf, str->len);
}

int c_string_add_cstr(c_string *dst, int pos, const char *cstr)
{
	if (cstr == NULL)
	{
		return 0;
	}
	return c_string_add_bytes(dst, pos, cstr, (int)strlen(cstr));
}

int c_string_add_char(c_string *dst, int pos, char c)
{
	if (dst == NULL || pos < 0)
	{
		return 0;
	}
	return c_string_add_bytes(dst, pos, &c, 1);
}

int c_string_add_bytes(c_string *dst, int pos, const char *bytes, int n)
{
	if (dst == NULL || pos < 0 || bytes == NULL || n <=0)
	{
		return 0;
	}

	if (dst->len + n > dst->capacity)
	{
		int ret = c_string_resize(dst, GET_NEW_CAPACITY(dst->len + n), 1);
		if (ret == 0)
		{
			return 0;
		}
	}

	// right move
	char *cp1 = dst->buf + dst->len;
	char *cp2 = cp1 + n;
	char *end = dst->buf + pos;
	while (cp1 >= end)
	{
		*cp2 = *cp1;
		--cp1;
		--cp2;
	}
	
	memcpy(end, bytes, n);
	dst->len += n;
	return 1;
}

void c_string_remove(c_string *dst, const c_string *str)
{
	if (dst == NULL || str == NULL)
	{
		return;
	}
	c_string_remove_bytes(dst, str->buf, str->len);
}

void c_string_remove_cstr(c_string *dst, const char *cstr)
{
	if (dst == NULL || cstr == NULL)
	{
		return;
	}
	c_string_remove_bytes(dst, cstr, (int)strlen(cstr));
}

void c_string_remove_char(c_string *dst, char c)
{
	if (dst == NULL || c == '\0')
	{
		return;
	}
	c_string_remove_bytes(dst, &c, 1);
}

void c_string_remove_range(c_string *dst, int begin, int end)
{
	if (dst == NULL || end <= begin || end < 0 || end > dst->len)
	{
		return;
	}
	
	int n = end - begin;
	char *pc1 = dst->buf + begin;
	char *pc2 = pc1 + n;
	char *pc3 = dst->buf + dst->len + 1;
	while (pc2 < pc3)
	{
		*pc1 = *pc2;
		++pc1;
		++pc2;
	}
	dst->len -= n;
}

void c_string_replace(c_string *dst, const c_string *old_str, const c_string *new_str)
{
	if (old_str == NULL || new_str == NULL)
	{
		return;
	}

	c_string_replace_bytes(dst, old_str->buf, old_str->len, new_str->buf, new_str->len);
}

void c_string_replace_cstr(c_string *dst, const char *old_cstr, const char *new_cstr)
{
	if (old_cstr == NULL || new_cstr == NULL)
	{
		return;
	}

	c_string_replace_bytes(dst, old_cstr, (int)strlen(old_cstr), new_cstr, (int)strlen(new_cstr));
}

void c_string_replace_char(c_string *dst, char old_char, char new_char)
{
	c_string_replace_bytes(dst, &old_char, 1, &new_char, 1);
}

void c_string_replace_range(c_string *dst, int begin, int end, const c_string *new_str)
{
	if (new_str == NULL)
	{
		return;
	}

	c_string_replace_range_bytes(dst, begin, end, new_str->buf, new_str->len);
}

void c_string_replace_range_cstr(c_string *dst, int begin, int end, const char *new_cstr)
{
	if (new_cstr == NULL)
	{
		return;
	}

	c_string_replace_range_bytes(dst, begin, end, new_cstr, (int)strlen(new_cstr));
}

void c_string_replace_range_char(c_string *dst, int begin, int end, char c)
{
	if (dst == NULL || end <= begin || begin < 0 || end > dst->len)
	{
		return;
	}

	char *pc1 = dst->buf + begin;
	char *pc2 = dst->buf + end;
	while (pc1 < pc2)
	{
		*pc1 = c;
		++pc1;
	}
}

void c_string_replace_range_bytes(c_string *dst, int begin, int end, const char *bytes, int n)
{
	if (dst == NULL || bytes == NULL || n <=0 || end <= begin || end < 0)
	{
		return;
	}

	int diff = n - (end - begin);
	if (n <= end - begin)
	{
		memcpy(dst->buf + begin, bytes, n);
		c_string_remove_range(dst, begin + n, end);
	}
	else // n > end - begin
	{
		if (dst->len + diff > dst->capacity)
		{
			if (!c_string_resize(dst, GET_NEW_CAPACITY(dst->len + diff), 1))
			{
				return;
			}
		}
		// right move
		char *write = dst->buf + dst->len + diff;
		char *read = dst->buf + dst->len;
		while (read >= dst->buf + end)
		{
			*write = *read;
			--write;
			--read;
		}

		memcpy(dst->buf + begin, bytes, n);
	}
	dst->len += diff;
	dst->buf[dst->len] = '\0';
}

void c_string_trim_start(c_string *str)
{
	if (str == NULL)
	{
		return;
	}

	char *pc = NULL;
	for (pc =str->buf; IS_SPACE_CHAR(*pc); ++pc);
	if (pc != str->buf)
	{
		char *tmp = str->buf;
		while (*pc)
		{
			*tmp = *pc;
			++tmp;
			++pc;
		}
		*tmp = '\0';
	}
}

void c_string_trim_end(c_string *str)
{
	if (str == NULL)
	{
		return;
	}

	char *pc = str->buf + str->len -1;
	while (IS_SPACE_CHAR(*pc))
	{
		*pc = '\0';
		--pc;
		--str->len;
	}
}

void c_string_trim(c_string *str)
{
	c_string_trim_end(str);
	c_string_trim_start(str);
}

void c_string_clear(c_string *str)
{
	if (str == NULL)
	{
		return;
	}
	str->buf[0] = '\0';
	str->len = 0;
}

void c_string_to_lower(c_string *str)
{
	if (str == NULL)
	{
		return;
	}

	char *pc = str->buf;
	int i = 0;
	for (; i < str->len; ++i, ++pc)
	{
		if (*pc >= 'A' && *pc <= 'Z')
		{
			*pc += ('a' - 'A');
		}
	}
}

void c_string_to_upper(c_string *str)
{
	if (str == NULL)
	{
		return;
	}

	char *pc = str->buf;
	int i = 0;
	for (; i < str->len; ++i, ++pc)
	{
		if (*pc >= 'a' && *pc <= 'z')
		{
			*pc -= ('a' - 'A');
		}
	}
}

int c_string_find(const c_string *str, int begin, int end, const c_string *sub_str)
{
	if (sub_str == NULL)
	{
		return C_STRING_NPOS;
	}
	return c_string_find_bytes(str, begin, end, sub_str->buf, sub_str->len);
}

int c_string_find_cstr(const c_string *str, int begin, int end, const char *sub_cstr)
{
	if (sub_cstr == NULL)
	{
		return C_STRING_NPOS;
	}
	return c_string_find_bytes(str, begin, end, sub_cstr, (int)strlen(sub_cstr));
}

int c_string_find_char(const c_string *str, int begin, int end, char c)
{
	return c_string_find_bytes(str, begin, end, &c, 1);
}

int c_string_find_bytes(const c_string *str, int begin, int end, const char *bytes, int n)
{
	if (str == NULL || bytes == NULL || n < 0 || end < begin || end > str->len)
	{
		return C_STRING_NPOS;
	}

	int i = begin;
	for (; i <= end - n; ++i)
	{
		if (memcmp(str->buf + i, bytes, n) == 0)
		{
			return i;
		}
	}
	return C_STRING_NPOS;
}

int c_string_rfind(const c_string *str, int begin, int end, const c_string *sub_str)
{
	if (sub_str == NULL)
	{
		return C_STRING_NPOS;
	}
	return c_string_rfind_bytes(str, begin, end, sub_str->buf, sub_str->len);
}

int c_string_rfind_cstr(const c_string *str, int begin, int end, const char *sub_cstr)
{
	if (sub_cstr == NULL)
	{
		return C_STRING_NPOS;
	}
	return c_string_rfind_bytes(str, begin, end, sub_cstr, (int)strlen(sub_cstr));
}

int c_string_rfind_char(const c_string *str, int begin, int end, char c)
{	
	return c_string_rfind_bytes(str, begin, end, &c, 1);
}

int c_string_rfind_bytes(const c_string *str, int begin, int end, const char *bytes, int n)
{
	if (str == NULL || bytes == NULL || n < 0 || end < begin || end > str->len)
	{
		return C_STRING_NPOS;
	}

	int i = end - n;
	for (; i >= begin; --i)
	{
		if (memcmp(str->buf + i, bytes, n) == 0)
		{
			return i;
		}
	}
	return C_STRING_NPOS;
}

int c_string_compare(const c_string *str1, const c_string *str2)
{
	if (str1 == NULL && str2 != NULL)
	{
		return -1;
	}
	if (str1 != NULL && str2 == NULL)
	{
		return 1;
	}
	if (str1 == NULL && str2 == NULL)
	{
		return 0;
	}

	int n = str1->len <= str2->len ? str1->len : str2->len;
	int ret = memcmp(str1->buf, str2->buf, n);
	if (ret != 0)
	{
		return ret;
	}
	if (str1->len > str2->len)
	{
		return 1;
	}
	return -1;
}

int c_string_compare_cstr(const c_string *str, const char *cstr)
{
	if (str == NULL && cstr != NULL)
	{
		return -1;
	}
	if (str != NULL && cstr == NULL)
	{
		return 1;
	}
	if (str == NULL && cstr == NULL)
	{
		return 0;
	}
	return strcmp(str->buf, cstr);
}

int c_string_ncompare(const c_string *str1, const c_string *str2, int n)
{
	if (str1 == NULL && str2 != NULL)
	{
		return -1;
	}
	if (str1 != NULL && str2 == NULL)
	{
		return 1;
	}
	if (str1 == NULL && str2 == NULL)
	{
		return 0;
	}
	return memcmp(str1->buf, str2->buf, n);
}

int c_string_ncompare_cstr(const c_string *str, const char *cstr, int n)
{
	if (str == NULL && cstr != NULL)
	{
		return -1;
	}
	if (str != NULL && cstr == NULL)
	{
		return 1;
	}
	if (str == NULL && cstr == NULL)
	{
		return 0;
	}
	return strncmp(str->buf, cstr, n);
}

char c_string_get(const c_string *str, int i)
{
	if (str == NULL || i < 0 || i > str->len)
	{
		return '\0';
	}
	return str->buf[i];
}

void c_string_set(c_string *str, int i, char c)
{
	if (str == NULL || i < 0 || i >= str->len)
	{
		return;
	}
	str->buf[i] = c;
}

const char* c_string_cstr(const c_string *str)
{
	return str->buf;
}

int c_string_is_empty(const c_string *str)
{
	return !str->len;
}

int c_string_len(const c_string *str)
{
	return str->len;
}

void c_string_print(const c_string *str)
{
	if (str == NULL)
	{
		return;
	}

	int i = 0;
	for (; i < str->len; ++i)
	{
		printf("%c", str->buf[i]);
	}
}
