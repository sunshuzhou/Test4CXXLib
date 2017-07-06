
add_custom_command(OUTPUT enclave_u.h enclave_u.c enclave_t.h enclave_u.c
                   COMMAND ${SGX_EDGER8R} enclave.edl)
