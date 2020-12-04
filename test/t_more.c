#include "xp_getentropy.h"
#include <unity.h>
#include <errno.h>
#include <stdint.h>
#include <string.h>

void setUp(void) {}
void tearDown(void) {}

void test_should_be_different(void) {
    uint8_t buf1[20] = {0};
    uint8_t buf2[sizeof buf1] = {0};

    const int ret1 = xp_getentropy(buf1, sizeof buf1);
    TEST_ASSERT_EQUAL_INT(0, ret1);

    const int ret2 = xp_getentropy(buf2, sizeof buf1);
    TEST_ASSERT_EQUAL_INT(0, ret2);

    TEST_ASSERT(memcmp(buf1, buf2, sizeof buf1) != 0);
}

void test_zero_len(void) {
    uint8_t zero[20] = {0};
    uint8_t buf2[sizeof zero] = {0};

    const int ret = xp_getentropy(buf2, 0);
    TEST_ASSERT_EQUAL_INT(0, ret);

    TEST_ASSERT_EQUAL_MEMORY(zero, buf2, sizeof zero);
}

void test_len_too_large(void) {
    uint8_t buf[257];

    const int ret = xp_getentropy(buf, sizeof buf);
    TEST_ASSERT_EQUAL_INT(-1, ret);

    TEST_ASSERT_EQUAL_INT(EIO, errno);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_should_be_different);
    RUN_TEST(test_zero_len);
    RUN_TEST(test_len_too_large);
    return UNITY_END();
}
