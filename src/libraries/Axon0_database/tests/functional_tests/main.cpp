#include <Axon_common/logger.h>
#include <sql_table_test.h>

#include <iostream>

int
main()
{
    Axon::initConsoleLogger(true);
    Axon::SqlTable_Test();
    return 0;
}
