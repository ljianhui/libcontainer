#include <stdio.h>
#include "c_string.h"

int main()
{
	// AAAAA
	c_string *str = c_string_create_char('A', 5);
	c_string_print(str);
	printf("\n");

	// hello string
	c_string *str1 = c_string_create_cstr("hello string");
	c_string_print(str1);
	printf("\n");

	// string
	c_string *str2 = c_string_create_sub(str1, 6, c_string_len(str1));
	c_string_print(str2);
	printf("\n");

	// hello string
	c_string *str3 = c_string_clone(str1);
	c_string_print(str3);
	printf("\n");

	char buf[] = "string\0buffer";
	c_string *str4 = c_string_create_bytes(buf, 13);
	// stringbuffer
	c_string_print(str4);
	// string
	printf("\n%s\n", c_string_cstr(str4));

	// cstring assign
	c_string_assign_cstr(str1, "cstring assign is so cool!");
	c_string_print(str1);
	printf("\n");

	// cstring assign
	c_string_assign(str, str1);
	c_string_print(str);
	printf("\n");

	// a
	c_string_assign_char(str, 'a');
	c_string_print(str);
	printf("\n");

	// stringbuffer
	c_string_assign_bytes(str, buf, 13);
	c_string_print(str);
	printf("\n");

	// ten is 10
	c_string_assign_format(str, "%s is %d", "ten", 10);
	c_string_print(str);
	printf("\n");

	// string is cool
	c_string_assign_cstr(str, "string ");
	c_string_append_cstr(str, "is cool");
	printf("%s\n", c_string_cstr(str));

	// string is cool!!!
	c_string_assign_cstr(str1, "!!!");
	c_string_append(str, str1);
	printf("%s\n", c_string_cstr(str));

	// string is cool!!! len[18]
	c_string_append_char(str, ' ');
	c_string_append_format(str, "len[%d]", c_string_len(str));
	printf("%s\n", c_string_cstr(str));

	// string is cool!!! len[18]stringbuffer
	c_string_append_bytes(str, buf, 13);
	c_string_print(str);
	printf("\n");

	// string is cool
	c_string_assign_cstr(str, "");
	c_string_add_cstr(str, 0, "string");
	c_string_add_cstr(str, c_string_len(str), "cool");
	c_string_assign_cstr(str1, " is ");
	c_string_add(str, 6, str1);
	c_string_print(str);
	printf("\n");

	// #string is cool
	c_string_add_char(str, 0 , '#');
	printf("%s\n", c_string_cstr(str));

	// #stringstringbuffer is cool
	c_string_add_bytes(str, 7, buf, 13);
	c_string_print(str);
	printf("\n");

	c_string_assign_cstr(str, "+-*/+-*/+-*/()");
	c_string_assign_cstr(str1, "+");
	c_string_remove(str, str1);
	printf("%s\n", c_string_cstr(str)); // -*/-*/-*/()
	c_string_remove_cstr(str, "*/");
	printf("%s\n", c_string_cstr(str)); // ---()
	c_string_remove_char(str, '-');
	printf("%s\n", c_string_cstr(str)); // ()
	c_string_remove_range(str, 1, 2);
	printf("%s\n", c_string_cstr(str)); // (
	
	// string.string.string.string
	c_string_assign_cstr(str, "str.str.str.str");
	c_string_replace_cstr(str, "str", "string");
	printf("%s\n", c_string_cstr(str));

	// sing.sing.sing.sing
	c_string_assign_cstr(str1, "str");
	c_string_assign_cstr(str2, "s");
	c_string_replace(str, str1, str2);
	printf("%s\n", c_string_cstr(str));

	// sing-sing-sing-
	c_string_replace_char(str, '.', '-');
	printf("%s\n", c_string_cstr(str));

	// string-sing-sing-
	c_string_replace_range(str, 0, 1, str1);
	printf("%s\n", c_string_cstr(str));
	// string-ting-sing-
	c_string_replace_range_cstr(str, 7, 8, "t");
	printf("%s\n", c_string_cstr(str));
	// string-ting-AAAAA
	c_string_replace_range_char(str, 12, 17, 'A');
	printf("%s\n", c_string_cstr(str));
	// stringbuffer-ting-AAAAA
	c_string_replace_range_bytes(str, 0, 6, buf, 13);
	c_string_print(str);printf("\n");

	// String Cool
	c_string_assign_cstr(str, "\t String Cool \r\n");
	c_string_trim(str);
	printf("%s\n", c_string_cstr(str));
	// STRING COOL
	c_string_to_upper(str);
	printf("%s\n", c_string_cstr(str));
	// string cool
	c_string_to_lower(str);
	printf("%s\n", c_string_cstr(str));

	c_string_assign_cstr(str, "string-string-string");
	c_string_assign_cstr(str1, "tr");
	// 1
	printf("%d\n", c_string_find(str, 0, c_string_len(str), str1));
	// -1
	printf("%d\n", c_string_find_cstr(str, 16, c_string_len(str), "tr"));
	// 6
	printf("%d\n", c_string_find_char(str, 6, 9, '-'));
	c_string_append_bytes(str, buf, 13);
	// 20
	printf("%d\n", c_string_find_bytes(str, 0, c_string_len(str),buf, 12));

	c_string_assign_cstr(str, "str.str.str");
	// 9
	printf("%d\n", c_string_rfind(str, 0, c_string_len(str), str1));
	// -1
	printf("%d\n", c_string_rfind_cstr(str, 2, 5, "tr"));
	// 7
	printf("%d\n", c_string_rfind_char(str, 0, c_string_len(str), '.'));
	c_string_add_bytes(str, 6, buf, 13);
	// 6
	printf("%d\n", c_string_rfind_bytes(str, 0, c_string_len(str), buf, 12));

	c_string_assign_cstr(str, "string");
	c_string_assign_cstr(str1, "str");
	c_string_assign_cstr(str2, "struct");
	// 1
	printf("%d\n", c_string_compare(str, str1));
	// -1
	printf("%d\n", c_string_compare(str1, str));
	// >0
	printf("%d\n", c_string_compare_cstr(str, "str"));
	// 0
	printf("%d\n", c_string_ncompare(str, str2, 3));
	// <0
	printf("%d\n", c_string_ncompare(str, str2, 4));
	// 0
	printf("%d\n", c_string_ncompare_cstr(str, "str", 3));

	// g
	printf("%c\n", c_string_get(str, 5));
	// strina
	c_string_set(str, 5, 'a');
	printf("%s\n", c_string_cstr(str));

	// 0
	printf("%d\n", c_string_is_empty(str));
	c_string_clear(str);
	// 1
	printf("%d\n", c_string_is_empty(str));

	c_string_destroy(str4);
	c_string_destroy(str3);
	c_string_destroy(str2);
	c_string_destroy(str1);
	c_string_destroy(str);

	return 0;
}