#include "../inc/uls.h"

void mx_alloc_clean_up(t_main *main) {
    free(main->dirs);
}
