#include "../inc/libmx.h"

double mx_pow(double n, unsigned int pow) {
    double num = 1;

    if (pow < 0) {
        return 0;
    }
    if (pow == 0) {
        return 1;
    }
    if (pow > 0) {
        for (unsigned int i = 0; i < pow; i++)
            num *= n;
    }
    return num;
}
