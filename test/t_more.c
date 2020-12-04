#include "xp_getentropy.h"
#include <unity.h>
#include <stdint.h>

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

void test_should_be_different(void) {
    uint8_t buf1[20] = {0};
    uint8_t buf2[sizeof buf1] = {0};
    const int ret1 = 0;
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_should_be_different);
    return UNITY_END();
}
