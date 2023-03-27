#include "../inc/libmx.h"

bool mx_islower(int c) {
    if(c >= 'a' && c <= 'z') {
        return true;
    }
    return false;
}
