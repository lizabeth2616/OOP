#include <Eleven.h>
#include <gtest\gtest.h>

TEST(equal_test_suite, equal_to_itself) {
    Eleven lhs{ 50u };
    ASSERT_TRUE(Eleven::equal(lhs, lhs));
}

TEST(equal_test_suite, different_equal_objects) {
    Eleven lhs{ 100u };
    Eleven rhs{ 100u };
    ASSERT_TRUE(Eleven::equal(lhs, rhs));
    ASSERT_TRUE(Eleven::equal(rhs, lhs));
}

TEST(equal_test_suite, no_equal) {
    Eleven lhs{ 100u };
    Eleven rhs{ 200u };

    ASSERT_FALSE(Eleven::equal(lhs, rhs));
    ASSERT_FALSE(Eleven::equal(rhs, lhs));
}

TEST(comparison_test_suite, larger) {
    Eleven small{ 100u };
    Eleven large{ 200u };

    ASSERT_FALSE(Eleven::greater_than(small, large));
    ASSERT_TRUE(Eleven::greater_than(large, small));
}

TEST(comparison_test_suite, smaller) {
    Eleven small{ 100u };
    Eleven large{ 200u };

    ASSERT_TRUE(Eleven::less_than(small, large));
    ASSERT_FALSE(Eleven::less_than(large, small));
}

TEST(comparison_test_suite, equal_is_not_larger) {
    Eleven value{ 100u };
    ASSERT_FALSE(Eleven::greater_than(value, value));
}

TEST(comparison_test_suite, equal_is_not_smaller) {
    Eleven value{ 100u };
    ASSERT_FALSE(Eleven::less_than(value, value));
}

TEST(addition_test_suite, normal_test) {
    Eleven left{ 10u }, right{ 21u }, answer{ 31u };
    Eleven result = Eleven::add(left, right);
    ASSERT_TRUE(Eleven::equal(result, answer));
}

TEST(subtraction_test_suite, normal_test) {
    Eleven left{ 31u }, right{ 20u }, answer{ 11u };
    Eleven result = Eleven::subtract(left, right);
    ASSERT_TRUE(Eleven::equal(result, answer));
}

TEST(copy_test_suite, regular_test) {
    Eleven value{ 10u };
    Eleven copy{ 0u };

    copy = value;

    ASSERT_TRUE(Eleven::equal(copy, value));
}

TEST(MyTestSuite, MyTest) {
    EXPECT_EQ(1 + 1, 2);
}
