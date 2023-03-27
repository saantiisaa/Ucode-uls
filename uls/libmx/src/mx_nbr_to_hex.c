#include "../inc/libmx.h"

char *mx_nbr_to_hex(unsigned long nbr) {
    if (!nbr) return NULL;
    long tmp;
    int j = 0;
    int counter = 0;

    tmp = nbr;
    for ( ; tmp > 0; tmp /= 10) counter++;
    char *hex = mx_strnew(counter);
    tmp = nbr;
    counter = 0;
    while (tmp != 0) {
        if (tmp % 16 < 10) hex[j++] = 48 + tmp % 16;
        else hex[j++] = 87 + tmp % 16;
        counter++;
        tmp = tmp / 16;
    }
    char *hex_reverted = mx_strnew(counter);

    for (int i = 0, n = counter - 1; i < counter; i++, n--)
        hex_reverted[i] = hex[n];
    return hex_reverted;
}
