#include <gmock/gmock-matchers.h>
#include <gtest/gtest.h>

#include  "sqlworker.h"

using namespace testing;

TEST(SQLTests, Sql_Base_Tests)
{
    EXPECT_EQ(1, 1);
    ASSERT_THAT(0, Eq(0));
}

TEST(SQLTests, Sql_Base_Tests2)
{
    EXPECT_EQ(1, 1);
    ASSERT_THAT(0, Eq(0));
}

