#include <gmock/gmock-matchers.h>
#include <gtest/gtest.h>
#include "sqlworker.h"

using namespace testing;

TEST(ExamplesTests, Base)
{
    EXPECT_EQ(1, 1);
    ASSERT_THAT(0, Eq(0));
}
