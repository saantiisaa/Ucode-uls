#include "../inc/uls.h"

int window_get_columns(void) {
  struct winsize sizes;
  int cols = -1;
  if (isatty(1)) { 
    /* Only try this if stdout is a terminal */
    int status = ioctl(1, TIOCGWINSZ, &sizes);
    if (status == 0) {
      cols = sizes.ws_col;
    }
  }
  return cols;
}

void mx_print_format(t_list *filelist) {
    for (t_list *cur = filelist; cur != NULL; cur = cur->next) {
        if (cur->data != NULL) mx_printstr((cur->data));
        if (cur->next != NULL) mx_printstr("  ");
    }
    if (filelist != NULL) mx_printstr("\n");
}

void mx_print_format_column(t_list *filelist) {
    for (t_list *cur = filelist; cur != NULL; cur = cur->next) {
        if (cur->data != NULL) mx_printstr((cur->data));
        if (cur->next != NULL) mx_printstr("\n");
    }
    if (filelist != NULL) mx_printstr("\n");
}
