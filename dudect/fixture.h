#include <stddef.h>
#include <stdint.h>
extern const size_t chunk_size;
extern const size_t number_measurements;
extern void do_one_computation(uint8_t *data);
extern void real_init_dut(void);
extern void init_dut(void);
extern void leave_dut(void);
extern void prepare_inputs(uint8_t *input_data, uint8_t *classes);
void test_constant(void);
