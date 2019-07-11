#include <gtest/gtest.h>
#include "route.h"

int main(int argc, char**argv) {
    testing::InitGoogleTest(&argc, argv);
    int my_argc = argc;
    char** my_argv = argv;
    return RUN_ALL_TESTS();
}
