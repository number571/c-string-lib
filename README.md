# CStringLIB
> Extended string library for programming language C.

### String type
```c
typedef struct String {
	char * chars;
	size_t len;
	size_t cap;
} String;
```

### Example :
```c
#include <stdio.h>
#include "string/init.h"

int main(void) {
	String * str = init_string("hello, world!");
	replace_string(str, "world", "string type");
	printf("%s\n", str->chars);
	free_string(str);
	return 0;
}
```

### Run
```
$ gcc -o main main.c string/init.c 
$ ./main
```
