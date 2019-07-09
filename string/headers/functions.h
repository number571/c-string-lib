extern String * init_string(char * chars);
extern void free_string(String * string);

extern void concat_type_chars(String * string, char * chars);
extern void concat_type_string(String * string1, String * string2);

extern void copy_type_chars(String * string, char * chars);
extern void copy_type_string(String * string1, String * string2);

extern void replace_type_chars(String * string, char * repl, char * torepl);
extern void replace_type_string(String * string, String * repl, String * torepl);

extern char * split_type_string(String * string, String * sep, ssize_t * position);
extern char * split_type_chars(String * string, char * sep, ssize_t * position);

extern void delete_type_string(String * string, String * pattern);
extern void delete_type_chars(String * string, char * pattern);

extern int slice_type_string(String * string, String * slice, size_t min, size_t max);
extern int slice_type_chars(String * string, char * slice, size_t min, size_t max);

extern bool has_prefix_type_string(String * string, String * pattern);
extern bool has_prefix_type_chars(String * string, char * pattern);

extern bool has_suffix_type_string(String * string, String * pattern);
extern bool has_suffix_type_chars(String * string, char * pattern);

extern bool has_contain_type_string(String * string, String * pattern);
extern bool has_contain_type_chars(String * string, char * pattern);

extern size_t count_type_string(String * string, String * pattern);
extern size_t count_type_chars(String * string, char * pattern);

extern int compare_type_chars(String * string, char * chars);
extern int compare_type_string(String * string1, String * string2);
