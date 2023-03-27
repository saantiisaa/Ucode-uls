#include "../inc/uls.h"

void mx_parse_file_paths(t_main *main, int argc, char **argv) {
    int i = 0;
    main->dirs = (char **)malloc((argc + 1) * sizeof(char *));
    for (int j = 0; j <= argc; j++) {
        main->dirs[j] = NULL;
    }        
    if ((argc <= 1) || (argc == 2 && argv[1][0] == '-')) {
        main->dirs[0] = ".";
        return;
    }
    if (!argv[1] || argv[1][0] == '-') {
        i = 2;
    }
    else { 
        i = 1; 
    }
    for (int j = 0; argv[i]; j++) {
        main->dirs[j] = argv[i];
        i++;
    }
}
