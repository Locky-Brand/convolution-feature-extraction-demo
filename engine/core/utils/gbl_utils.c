#include "gbl_utils.h"

int cmp_file_ext(const char* fname, const char* ext) {
    for (int i = 0; fname[i] != '\0'; ++i) {
        if (fname[i] == '.') {
            return !strcmp(&fname[i], ext);
        }
    }
    return 0;
}
