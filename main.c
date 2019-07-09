#include <stdio.h>
#include "string/init.h"

int main(void) {
	String * str = init_string("hello, world!");
	replace_string(str, "world", "string type");
	printf("%s\n", str->chars);
	free_string(str);
	return 0;
}
