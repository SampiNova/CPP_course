#include "../time/time.hpp"
#include <gtest/gtest.h>

TEST(TimeConstructor, DefaultConstructor) {
    Time t;
    EXPECT_EQ(t.get_hours(), 0);
    EXPECT_EQ(t.get_minutes(), 0);
    EXPECT_EQ(t.get_seconds(), 0);
}

TEST(TimeConstructor, FullConstructor) {
    Time t(10, 20, 30);
    EXPECT_EQ(t.get_hours(), 6);
    EXPECT_EQ(t.get_minutes(), 20);
    EXPECT_EQ(t.get_seconds(), 10);
}

TEST(TimeConstructor, FullConstructor_Normalization) {
    Time t(70, 70, 25);
    std::cout << t << "\n";
    EXPECT_EQ(t.get_hours(), 2);
    EXPECT_EQ(t.get_minutes(), 11);
    EXPECT_EQ(t.get_seconds(), 10);
}

TEST(TimeConstructor, FullConstructor_NegativeInput) {
    ASSERT_THROW(Time t(-1, 0, 0), const char *);
    ASSERT_THROW(Time t(0, -1, 0), const char *);
    ASSERT_THROW(Time t(0, 0, -1), const char *);
}

TEST(TimeConstructor, CopyConstructor) {
    Time t1(10, 20, 30);
    Time t2(t1);
    EXPECT_EQ(t2.get_hours(), 6);
    EXPECT_EQ(t2.get_minutes(), 20);
    EXPECT_EQ(t2.get_seconds(), 10);
}

TEST(Time, ToSeconds) {
    Time t(10, 20, 30);
    EXPECT_EQ(t.to_seconds(), 10 + 20 * 60 + 6 * 3600);
}

TEST(TimeSetters, Setters) {
    Time t;
    t.set_seconds(10);
    t.set_minutes(20);
    t.set_hours(30);
    EXPECT_EQ(t.get_hours(), 6);
    EXPECT_EQ(t.get_minutes(), 20);
    EXPECT_EQ(t.get_seconds(), 10);
}

TEST(TimeSetters, Setters_NegativeInput) {
    Time t;
    ASSERT_THROW(t.set_seconds(-1), const char *);
    ASSERT_THROW(t.set_minutes(-1), const char *);
    ASSERT_THROW(t.set_hours(-1), const char *);
}

TEST(TimeOperators, AddOperatorTime) {
    Time t1(10, 20, 30);
    Time t2(5, 10, 15);
    t1 += t2;
    EXPECT_EQ(t1.get_hours(), 21);
    EXPECT_EQ(t1.get_minutes(), 30);
    EXPECT_EQ(t1.get_seconds(), 15);
}

TEST(TimeOperators, AddOperatorInt) {
    Time t1(10, 20, 30);
    t1 += 100;
    EXPECT_EQ(t1.get_hours(), 6);
    EXPECT_EQ(t1.get_minutes(), 21);
    EXPECT_EQ(t1.get_seconds(), 50);
}

TEST(TimeOperators, SubtractOperatorTime) {
    Time t1(10, 20, 30);
    Time t2(5, 10, 15);
    t1 -= t2;
    EXPECT_EQ(t1.get_hours(), 0);
    EXPECT_EQ(t1.get_minutes(), 0);
    EXPECT_EQ(t1.get_seconds(), 0);
}

TEST(TimeOperators, SubtractOperatorInt) {
    Time t1(10, 20, 30);
    t1 -= 100;
    EXPECT_EQ(t1.get_hours(), 6);
    EXPECT_EQ(t1.get_minutes(), 18);
    EXPECT_EQ(t1.get_seconds(), 30);
}

TEST(Watch, SetFormat) {
    Time t;
    Watch w(t);
    w.set_format(true);
    EXPECT_EQ(w.format(), 1);
    w.set_format(false);
    EXPECT_EQ(w.format(), 0);
}

TEST(Watch, GetTimeObject) {
    Time t_;
    Watch w(t_);
    Time &t = w.get_time_object();
    t.set_hours(10);
    EXPECT_EQ(w.get_time_object().get_hours(), 10);
}

TEST(WatchSettersGetters, SettersGetters) {
    Time t_;
    Watch w(t_);
    Time t;
    w.set_seconds(t, 10);
    w.set_minutes(t, 20);
    w.set_hours(t, 30);
    EXPECT_EQ(w.get_seconds(t), 10);
    EXPECT_EQ(w.get_minutes(t), 20);
    EXPECT_EQ(w.get_hours(t), 6);
}

TEST(WatchSettersGetters, SettersGetters_NegativeInput) {
    Time t_;
    Watch w(t_);
    Time t;
    ASSERT_THROW(w.set_seconds(t, -1), const char *);
    ASSERT_THROW(w.set_minutes(t, -1), const char *);
    ASSERT_THROW(w.set_hours(t, -1), const char *);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
