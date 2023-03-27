#include "../inc/libmx.h"

char *mx_replace_substr(const char *str, const char *sub, const char *replace) {
    if (!str || !sub || !replace) {
        return NULL;
    }

	int len = mx_strlen(str) + mx_count_substr(str, sub) * (mx_strlen(replace) - mx_strlen(sub));
	char *res = mx_strnew(len);
    int a = 0;

    for (int i = 0; i < len; i++) {
        if (mx_get_substr_index((char*)&str[a], sub) == 0) {
            for (int j = 0; j < mx_strlen(replace); j++) {
                res[i] = replace[j];
                i++;
            }
            a += mx_strlen(sub);
            i--;
        }
        else {
            res[i] = str[a];
            a++;
        }
    }
    return res;
}
