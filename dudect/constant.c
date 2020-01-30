#include "constant.h"
#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../console.h"
#include "../qtest.h"
#include "../queue.h"
#include "../report.h"
#include "random.h"

const size_t chunk_size = 16;
const size_t number_measurements = 150;  // per test
int test_mode;
static queue_t *q = NULL;
static void queue_init();

void dut_new() {
    q = q_new();
}

void dut_size(int n)
{
    for (int i=0; i<n; ++i) 
        q_size(q);
}

void dut_insert_head(char *s, int n) {
    for (int i=0; i<n; ++i)
        q_insert_head(q, s);
}

void dut_insert_tail(char *s, int n) {
    for (int i=0; i<n; ++i)
        q_insert_tail(q, s);
}

void dut_free() {
    q_free(q);
}

void init_dut(void)
{
    test_mode = 0;
    // initialize queue
    queue_init();
}
void prepare_inputs(uint8_t *input_data, uint8_t *classes)
{
    randombytes(input_data, number_measurements * chunk_size);
    for (size_t i = 0; i < number_measurements; i++) {
        classes[i] = randombit();
        if (classes[i] == 0) {
            *(uint16_t *) (input_data + i * chunk_size) = 0x00;
        } else {
            // leave random
        }
    }
}

static void dut_sigalrmhandler()
{
    printf("Time exceeds 1 sec!!\n");  // We don't use the original alarm
                                       // handler, since it will break the
                                       // computation
    exit(0);
}

static void queue_init()
{
    q = NULL;
    signal(SIGSEGV, sigsegvhandler);
    signal(SIGALRM, dut_sigalrmhandler);
}
