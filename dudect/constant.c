#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include "dut.h"
#include "random.h"
#include "../queue.h"

static queue_t *q = NULL;

const size_t chunk_size = 8;
const size_t number_measurements = 1000;  // per test
typedef bool (*cmd_function)(int argc, char *argv[]);

// copy from qtest.c
extern bool interpret_cmd(char *cmdline);
extern void sigsegvhandler(int sig);
extern void set_verblevel(int level);
extern bool do_insert_tail(int argc, char *argv[]);
extern bool do_insert_head(int argc, char *argv[]);
extern bool do_size(int argc, char *argv[]);
extern bool do_free(int argc, char *argv[]);
extern bool do_new(int argc, char *argv[]);
extern void add_cmd(char *name, cmd_function operation, char *documentation);
extern void init_cmd();
extern void exception_cancel();
static void queue_init();
int test_mode;

void do_one_computation(char *data)
{
    // insert tail or get size
    interpret_cmd(data);
}

void init_dut(void)
{
    test_mode = 0;
    // initialize queue
    queue_init();
    init_cmd();
    add_cmd("new", do_new, "");
    add_cmd("it", do_insert_tail, "");
    add_cmd("ih", do_insert_head, "");
    add_cmd("free", do_free, "");
    add_cmd("size", do_size, "");
    set_verblevel(0);
}

void real_init_dut(void)
{
    interpret_cmd("new\n");
}

void leave_dut(void)
{
    interpret_cmd("free\n");
}

void prepare_inputs(uint8_t *input_data, uint8_t *classes)
{
    randombytes(input_data, number_measurements * chunk_size);
    for (size_t i = 0; i < number_measurements; i++) {
        classes[i] = randombit();
        if (classes[i] == 0) {
            memset(input_data + (size_t) i * chunk_size, 0x01,
                   chunk_size);  // The value cannot be 0x00, since 0x00 will
                                 // not trigger q_insert_tail
        } else {
            // leave random
        }
    }
}

void siginthandler()
{
    if (test_mode)
        exit(0);
    printf("\nTesting q_size...... press Ctrl-C to leave.\n\n");
    test_mode = 1;
}

void test_sigalrmhandler()
{
    printf("Time exceeds 1 sec!!\n");  // We don't use the original alarm
                                       // handler, since it will break the
                                       // computation
    exit(0);
}

static void queue_init()
{
    q = NULL;
    signal(SIGINT, siginthandler);  // use to switch to another mode
    signal(SIGSEGV, sigsegvhandler);
    signal(SIGALRM, test_sigalrmhandler);
}
