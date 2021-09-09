#pragma once
#include "ws_test.h"


int main(void)
{
    test_all();
    std::cin.get();

#if defined(_MSC_VER) && defined(_DEBUG)
    _CrtDumpMemoryLeaks();
#endif // check memory leaks
}
