#include "../../../code/core/impl/process/export.h"

#include <stdio.h>

int
main(int argc, char** argv)
{
    printf("Core amount  = %lli\n", pax_process_core_amount());
    printf("Thread ident = %lli\n", pax_current_thread_ident());
}
