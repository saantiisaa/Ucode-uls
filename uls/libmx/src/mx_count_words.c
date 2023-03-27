#include "../inc/libmx.h"

int mx_count_words(const char *str, char delimiter) {
    int words = 0;
    bool sequence = true;
    
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == delimiter) {
            sequence = true;
        }
        else if (sequence) {
            words++;
            sequence = false;
        }
    }
    return words;
}
