#include "init.h"

static void concat_template(String * string, char * chars, size_t length);
static void copy_template(String * string, char * chars, size_t length);
static void replace_template(String * str, char * repl, char * torepl);
static char * split_template(String * string, char * sep, ssize_t * position, size_t seplen);
static void delete_template(String * string, char * pattern, size_t patternlen);
static bool has_contain_template(String * string, char * pattern, size_t patternlen);
static int slice_template(String * string, char * slice, size_t slicelen, size_t min, size_t max);
static size_t count_template(String * string, char * pattern, size_t patternlen);

extern String * init_string(char * chars) {
    String * new_string = (String *)malloc(sizeof(String));
    size_t len = strlen(chars);
    size_t cap = (len >= DEFLEN) ? (len + DEFLEN) : DEFLEN;
    new_string->chars = (char *)malloc(cap * sizeof(char));
    memcpy(new_string->chars, chars, len+1);
    new_string->len = len;
    new_string->cap = cap;
    return new_string;
}

extern void free_string(String * string) {
    free(string->chars);
    free(string);
}

extern void concat_type_chars(String * string, char * chars) {
    concat_template(string, chars, strlen(chars));
}

extern void concat_type_string(String * string1, String * string2) {
    concat_template(string1, string2->chars, string2->len);
}

static void concat_template(String * string, char * chars, size_t length) {
    const size_t reslen = string->len + length;
    if (reslen >= string->cap) {
        while (reslen >= string->cap) {
            string->cap *= 2;
        }
        string->chars = (char *)realloc(string->chars, string->cap * sizeof(char));
    }
    strcat(string->chars, chars);
    string->len += length;
}

extern void replace_type_chars(String * string, char * repl, char * torepl) {
    replace_template(string, repl, torepl);
}

extern void replace_type_string(String * string, String * repl, String * torepl) {
    replace_template(string, repl->chars, torepl->chars);
}

static void expension_string(String * str, char * buffer) {
    str->cap *= 2;
    str->chars = (char *)realloc(str->chars, str->cap * sizeof(char));
    buffer = (char *)realloc(buffer, str->cap * sizeof(char));
}

static void replace_template(String * str, char * repl, char * torepl) {
    char * buffer = (char*)malloc(str->cap * sizeof(char));
    char * p_buff = buffer;
    for (size_t i = 0, x = 0; i < str->len + 1; ++i) {
        if ((p_buff - buffer) == (str->cap - 1)) {
            expension_string(str, buffer);
        }
        if (repl[x] == END_OF_STRING) {
            for (char *p = torepl; *p != END_OF_STRING; ++p) {
                *p_buff++ = *p;
                if ((p_buff - buffer) == (str->cap - 1)) {
                    expension_string(str, buffer);
                }
            }
            x = 0;
        }
        if (str->chars[i] == repl[x]) {
            ++x;
        } else {
            while (x) {
                *p_buff++ = str->chars[i-x--];
                if ((p_buff - buffer) == (str->cap - 1)) {
                    expension_string(str, buffer);
                }
            }
            if (str->chars[i] == repl[0]) {
                ++x;
            } else {
                *p_buff++ = str->chars[i];
            }
        }
    }
    *p_buff = END_OF_STRING;
    str->len = p_buff - buffer;
    strcpy(str->chars, buffer);
    free(buffer);
} 

extern void copy_type_chars(String * string, char * chars) {
    copy_template(string, chars, strlen(chars));
}

extern void copy_type_string(String * string1, String * string2) {
    copy_template(string1, string2->chars, string2->len);
}

static void copy_template(String * string, char * chars, size_t length) {
    if (length >= string->cap) {
        while (length >= string->cap) {
            string->cap *= 2;
        }
        string->chars = (char *)realloc(string->chars, string->cap * sizeof(char));
    }
    memcpy(string->chars, chars, length+1);
    string->len = length;
}

extern char * split_type_string(String * string, String * sep, ssize_t * position) {
    return split_template(string, sep->chars, position, sep->len);
}

extern char * split_type_chars(String * string, char * sep, ssize_t * position) {
    return split_template(string, sep, position, strlen(sep));
}

static char * split_template(String * string, char * sep, ssize_t * position, size_t seplen) {
    char * ptr = string->chars;
    switch(*position) {
        case -1: return NULL;
        case  0: break;
        default: 
            ptr[*position-seplen] = sep[0];
            ptr += *position;
    }
    for (size_t j, i = 0; i < (string->len - *position); ++i) {
        j = 0;
        for (j = 0; j < seplen; ++j) {
            if (ptr[i+j] != sep[j]) {
                break;
            }
        }
        if (j == seplen) {
            ptr[i] = '\0';
            *position += i + seplen;
            return ptr;
        }
    }
    *position = -1;
    return ptr;
}

extern void delete_type_string(String * string, String * pattern) {
    delete_template(string, pattern->chars, pattern->len);
}

extern void delete_type_chars(String * string, char * pattern) {
    delete_template(string, pattern, strlen(pattern));
}

static void delete_template(String * string, char * pattern, size_t patternlen) {
    if (string->len < patternlen) return;
    for (size_t j, i = 0; i < string->len; ++i) {
        j = 0;
        for (j = 0; j < patternlen; ++j) {
            if (string->chars[i+j] != pattern[j]) {
                break;
            }
        }
        if (j == patternlen) {
            memmove(string->chars + i, string->chars + i + patternlen, string->len - i);
            string->len -= patternlen;
        }
    }
}

extern int slice_type_string(String * string, String * slice, size_t min, size_t max) {
    return slice_template(string, slice->chars, slice->len, min, max);
}

extern int slice_type_chars(String * string, char * slice, size_t min, size_t max) {
    return slice_template(string, slice, strlen(slice), min, max);
}

static int slice_template(String * string, char * slice, size_t slicelen, size_t min, size_t max) {
    if (min > max) return 1;
    if (min > slicelen || max > slicelen) return 2;
    size_t count = max - min;
    char ptr[count+1];
    memcpy(ptr, slice + min, count);
    ptr[count] = '\0';
    copy_template(string, ptr, count);
    return 0;
}

extern bool has_prefix_type_string(String * string, String * pattern) {
    return memcmp(string->chars, pattern->chars, pattern->len) == 0;
}

extern bool has_prefix_type_chars(String * string, char * pattern) {
    return memcmp(string->chars, pattern, strlen(pattern)) == 0;
}

extern bool has_suffix_type_string(String * string, String * pattern) {
    return memcmp(string->chars + (string->len - pattern->len), pattern->chars, pattern->len) == 0;
}

extern bool has_suffix_type_chars(String * string, char * pattern) {
    const size_t patternlen = strlen(pattern);
    return memcmp(string->chars + (string->len - patternlen), pattern, patternlen) == 0;
}

extern bool has_contain_type_string(String * string, String * pattern) {
    return has_contain_template(string, pattern->chars, pattern->len);
}

extern bool has_contain_type_chars(String * string, char * pattern) {
    return has_contain_template(string, pattern, strlen(pattern));
}

static bool has_contain_template(String * string, char * pattern, size_t patternlen) {
    if (string->len < patternlen) return false;
    for (size_t j, i = 0; i < string->len; ++i) {
        j = 0;
        for (j = 0; j < patternlen; ++j) {
            if (string->chars[i+j] != pattern[j]) {
                break;
            }
        }
        if (j == patternlen) {
            return true;
        }
    }
    return false;
}

extern size_t count_type_string(String * string, String * pattern) {
    return count_template(string, pattern->chars, pattern->len);
}

extern size_t count_type_chars(String * string, char * pattern) {
    return count_template(string, pattern, strlen(pattern));
}

static size_t count_template(String * string, char * pattern, size_t patternlen) {
    size_t sum = 0;
    for (size_t i = 0; i < string->len - patternlen; ++i) {
        if (string->chars[i] != pattern[0]) continue;
        if (memcmp(string->chars + i, pattern, patternlen) == 0) {
            ++sum;
        }
    }
    return sum;
}

extern size_t length_type_string(String * string) {
    return string->len;
}

extern size_t length_type_chars(char * chars) {
    return strlen(chars);
}

extern int compare_type_chars(String * string, char * chars) {
    return strcmp(string->chars, chars);
}

extern int compare_type_string(String * string1, String * string2) {
    return strcmp(string1->chars, string2->chars);
}
