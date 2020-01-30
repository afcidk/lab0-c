/* qtest interface for dudect */
#include <stdbool.h>

bool do_new(int argc, char *argv[]);
bool do_free(int argc, char *argv[]);
bool do_insert_head(int argc, char *argv[]);
bool do_insert_tail(int argc, char *argv[]);
bool do_remove_head(int argc, char *argv[]);
bool do_remove_head_quiet(int argc, char *argv[]);
bool do_reverse(int argc, char *argv[]);
bool do_size(int argc, char *argv[]);
bool do_show(int argc, char *argv[]);

void sigalrmhandler(int sig);
void sigsegvhandler(int sig);
