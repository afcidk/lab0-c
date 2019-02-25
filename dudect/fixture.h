extern const size_t chunk_size;
extern const size_t number_measurements;
extern void do_one_computation(u_int8_t *data);
extern void real_init_dut(void);
extern void init_dut(void);
extern void leave_dut(void);
extern void prepare_inputs(u_int8_t *input_data, u_int8_t *classes);
void test_constant(void);
