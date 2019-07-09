#define concat_string(X, Y) _Generic((Y),\
    char*: concat_type_chars,\
    String*: concat_type_string\
)(X, Y)

#define copy_string(X, Y) _Generic((Y),\
    char*: copy_type_chars,\
    String*: copy_type_string\
)(X, Y)

#define replace_string(X, Y, Z) _Generic((Y),\
    char*: replace_type_chars,\
    String*: replace_type_string\
)(X, Y, Z)

#define split_string(X, Y, Z) _Generic((Y),\
    char*: split_type_chars,\
    String*: split_type_string\
)(X, Y, Z)

#define slice_string(X, Y, MIN, MAX) _Generic((Y),\
    char*: slice_type_chars,\
    String*: slice_type_string\
)(X, Y, MIN, MAX)

#define has_prefix_string(X, Y) _Generic((Y),\
    char*: has_prefix_type_chars,\
    String*: has_prefix_type_string\
)(X, Y)

#define has_suffix_string(X, Y) _Generic((Y),\
    char*: has_suffix_type_chars,\
    String*: has_suffix_type_string\
)(X, Y)

#define has_contain_string(X, Y) _Generic((Y),\
    char*: has_contain_type_chars,\
    String*: has_contain_type_string\
)(X, Y)

#define count_string(X, Y) _Generic((Y),\
    char*: count_type_chars,\
    String*: count_type_string\
)(X, Y)

#define length_string(X) _Generic((X),\
    char*: length_type_chars,\
    String*: length_type_string\
)(X)

#define delete_string(X, Y) _Generic((Y),\
    char*: delete_type_chars,\
    String*: delete_type_string\
)(X, Y)

#define compare_string(X, Y) _Generic((Y),\
    char*: compare_type_chars,\
    String*: compare_type_string\
)(X, Y)
