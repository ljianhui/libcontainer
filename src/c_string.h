#ifndef _C_STRING_H
#define _C_STRING_H

#include "c_libdef.h"

#define C_STRING_NPOS -1

typedef struct c_string c_string;

c_string* c_string_create();
c_string* c_string_create_char(char c, int n);
c_string* c_string_create_cstr(const char *cstr);
c_string* c_string_create_bytes(const char *bytes, int n);
c_string* c_string_create_sub(const c_string *str, int begin, int end);
c_string* c_string_clone(const c_string *src);
void c_string_destroy(c_string *str);

int c_string_assign(c_string *dst, const c_string *src);
int c_string_assign_char(c_string *dst, char c);
int c_string_assign_cstr(c_string *dst, const char *src);
int c_string_assign_bytes(c_string *dst, const char *bytes, int n);
int c_string_assign_format(c_string *dst, const char *format, ...);

int c_string_append(c_string *dst, const c_string *str);
int c_string_append_char(c_string *dst, char c);
int c_string_append_cstr(c_string *dst, const char *cstr);
int c_string_append_bytes(c_string *dst, const char *bytes, int n);
int c_string_append_format(c_string *dst, const char *format, ...);

int c_string_add(c_string *dst, int pos, const c_string *str);
int c_string_add_cstr(c_string *dst, int pos, const char *cstr);
int c_string_add_char(c_string *dst, int pos, char c);
int c_string_add_bytes(c_string *dst, int pos, const char *bytes, int n);

void c_string_remove(c_string *dst, const c_string *str);
void c_string_remove_cstr(c_string *dst, const char *cstr);
void c_string_remove_char(c_string *dst, char c);
void c_string_remove_range(c_string *dst, int begin, int end);

void c_string_replace(c_string *dst, const c_string *old_str, const c_string *new_str);
void c_string_replace_cstr(c_string *dst, const char *old_cstr, const char *new_cstr);
void c_string_replace_char(c_string *dst, char old_char, char new_char);
void c_string_replace_range(c_string *dst, int begin, int end, const c_string *new_str);
void c_string_replace_range_cstr(c_string *dst, int begin, int end, const char *new_cstr);
void c_string_replace_range_char(c_string *dst, int begin, int end, char c);
void c_string_replace_range_bytes(c_string *dst, int begin, int end, const char *bytes, int n);

void c_string_trim_start(c_string *str);
void c_string_trim_end(c_string *str);
void c_string_trim(c_string *str);
void c_string_clear(c_string *str);

void c_string_to_lower(c_string *str);
void c_string_to_upper(c_string *str);

int c_string_find(const c_string *str, int begin, int end, const c_string *sub_str);
int c_string_find_cstr(const c_string *str, int begin, int end, const char *sub_cstr);
int c_string_find_bytes(const c_string *str, int begin, int end, const char *bytes, int n);
int c_string_find_char(const c_string *str, int begin, int end, char c);
int c_string_rfind(const c_string *str, int begin, int end, const c_string *sub_str);
int c_string_rfind_cstr(const c_string *str, int begin, int end, const char *sub_cstr);
int c_string_rfind_bytes(const c_string *str, int begin, int end, const char *bytes, int n);
int c_string_rfind_char(const c_string *str, int begin, int end, char c);

int c_string_compare(const c_string *str1, const c_string *str2);
int c_string_compare_cstr(const c_string *str, const char *cstr);
int c_string_ncompare(const c_string *str1, const c_string *str2, int n);
int c_string_ncompare_cstr(const c_string *str, const char *cstr, int n);

char c_string_get(const c_string *str, int i);
void c_string_set(c_string *str, int i, char c);

const char* c_string_cstr(const c_string *str);
int c_string_is_empty(const c_string *str);
int c_string_len(const c_string *str);
void c_string_print(const c_string *str);

#endif
