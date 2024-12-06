#include <iostream>
#include "../CircularBuffer/CircularBuffer.hpp"
#include "gtest/gtest.h"

using namespace std;

TEST(Constructors, DefaultConstructor) {
  CircularBuffer cb;
  EXPECT_EQ(cb.size(), 0);
  EXPECT_EQ(cb.capacity(), 0);
  EXPECT_TRUE(cb.empty());
}

TEST(Constructors, CapacityConstructor) {
  CircularBuffer cb(5);
  EXPECT_EQ(cb.size(), 0);
  EXPECT_EQ(cb.capacity(), 5);
  EXPECT_TRUE(cb.empty());
}

TEST(Constructors, CapacityAndValueConstructor) {
  CircularBuffer cb(5, 10);
  EXPECT_EQ(cb.size(), 5);
  EXPECT_EQ(cb.capacity(), 5);
  EXPECT_FALSE(cb.empty());
  for (int i = 0; i < 5; ++i) {
    EXPECT_EQ(cb[i], 10);
  }
}

TEST(Constructors, CopyConstructor) {
  CircularBuffer cb1(5, 10);
  CircularBuffer cb2(cb1);
  EXPECT_EQ(cb2.size(), 5);
  EXPECT_EQ(cb2.capacity(), 5);
  EXPECT_FALSE(cb2.empty());
  for (int i = 0; i < 5; ++i) {
    EXPECT_EQ(cb2[i], 10);
  }
}

TEST(IndexGetter, IndexedGetters) {
  CircularBuffer cb(5);
  cb.push_back(1);
  cb.push_back(2);
  cb.push_back(3);
  EXPECT_EQ(cb[0], 1);
  EXPECT_EQ(cb[1], 2);
  EXPECT_EQ(cb[2], 3);
  EXPECT_EQ(cb[-1], 3);
  EXPECT_EQ(cb[3], 1);
  EXPECT_EQ(cb[4], 2);
  EXPECT_EQ(cb[5], 3);
  EXPECT_EQ(cb[6], 1);

  EXPECT_EQ(cb.at(0), 1);
  EXPECT_EQ(cb.at(1), 2);
  EXPECT_EQ(cb.at(2), 3);
  //EXPECT_THROW(cb.at(-1), std::invalid_argument);
  //EXPECT_THROW(cb.at(4), std::invalid_argument);
}

TEST(Push, FrontBack) {
  CircularBuffer cb(5);
  cb.push_back(1);
  cb.push_back(2);
  cb.push_back(3);
  EXPECT_EQ(cb.front(), 1);
  EXPECT_EQ(cb.back(), 3);
}

TEST(Linerization, Linearize) {
  CircularBuffer cb(5);
  cb.push_back(1);
  cb.push_back(2);
  cb.push_back(3);
  cb.push_front(4);
  cb.push_front(5);
  int* arr = cb.linearize();
  EXPECT_EQ(arr[0], 5);
  EXPECT_EQ(arr[1], 4);
  EXPECT_EQ(arr[2], 1);
  EXPECT_EQ(arr[3], 2);
  EXPECT_EQ(arr[4], 3);
}

TEST(Linerization, IsLinearized) {
  CircularBuffer cb(5);
  EXPECT_TRUE(cb.is_linearized());
  cb.push_front(1);
  cb.push_front(2);
  cb.push_front(3);
  EXPECT_FALSE(cb.is_linearized());
  cb.linearize();
  EXPECT_TRUE(cb.is_linearized());
}

TEST(Linerization, Rotate) {
  CircularBuffer cb(5);
  cb.push_back(1);
  cb.push_back(2);
  cb.push_back(3);
  cb.push_front(4);
  cb.push_front(5);
  cb.rotate(0);
  cout << endl;
  EXPECT_EQ(cb[0], 5);
  EXPECT_EQ(cb[1], 4);
  EXPECT_EQ(cb[2], 1);
  EXPECT_EQ(cb[3], 2);
  EXPECT_EQ(cb[4], 3);
}

TEST(State, SizeEmptyFull) {
    CircularBuffer cb(5);
    EXPECT_EQ(cb.size(), 0);
    EXPECT_TRUE(cb.empty());
    EXPECT_FALSE(cb.full());
    cb.push_back(1);
    EXPECT_EQ(cb.size(), 1);
    EXPECT_FALSE(cb.empty());
    EXPECT_FALSE(cb.full());
    for (int i = 2; i <= 5; ++i) {
      cb.push_back(i);
    }
    EXPECT_EQ(cb.size(), 5);
    EXPECT_FALSE(cb.empty());
    EXPECT_TRUE(cb.full());
}

TEST(Push, PushFront) {
    CircularBuffer cb(5);
    cb.push_front(1);
    cb.push_front(2);
    cb.push_front(3);
    EXPECT_EQ(cb.size(), 3);
    EXPECT_EQ(cb[0], 3);
    EXPECT_EQ(cb[1], 2);
    EXPECT_EQ(cb[2], 1);
    cb.push_front(4);
    cb.push_front(5);
    EXPECT_EQ(cb.size(), 5);
    EXPECT_EQ(cb[0], 5);
    EXPECT_EQ(cb[1], 4);
    EXPECT_EQ(cb[2], 3);
    EXPECT_EQ(cb[3], 2);
    EXPECT_EQ(cb[4], 1);
}

TEST(Pop, PopBack) {
    CircularBuffer cb(5);
    cb.push_back(1);
    cb.push_back(2);
    cb.push_back(3);
    cb.pop_back();
    EXPECT_EQ(cb.size(), 2);
    EXPECT_EQ(cb[0], 1);
    EXPECT_EQ(cb[1], 2);
    cb.pop_back();
    EXPECT_EQ(cb.size(), 1);
    EXPECT_EQ(cb[0], 1);
    cb.pop_back();
    EXPECT_EQ(cb.size(), 0);
    //EXPECT_THROW(cb.pop_back(), std::exception);
}

TEST(Pop, PopFront) {
    CircularBuffer cb(5);
    cb.push_back(1);
    cb.push_back(2);
    cb.push_back(3);
    cb.pop_front();
    EXPECT_EQ(cb.size(), 2);
    EXPECT_EQ(cb[0], 2);
    EXPECT_EQ(cb[1], 3);
    cb.pop_front();
    EXPECT_EQ(cb.size(), 1);
    EXPECT_EQ(cb[0], 3);
    cb.pop_front();
    EXPECT_EQ(cb.size(), 0);
    //EXPECT_THROW(cb.pop_front(), std::exception);
}

TEST(Push, Insert) {
    CircularBuffer cb(5);
    cb.push_back(1);
    cb.push_back(2);
    cb.push_back(3);
    cb.insert(1, 4);
    EXPECT_EQ(cb.size(), 4);
    EXPECT_EQ(cb[0], 1);
    EXPECT_EQ(cb[1], 4);
    EXPECT_EQ(cb[2], 2);
    EXPECT_EQ(cb[3], 3);
    //EXPECT_THROW(cb.insert(-1, 4), std::invalid_argument);
    //EXPECT_THROW(cb.insert(4, 4), std::invalid_argument);
}

TEST(Cleaning, Erase) {
    CircularBuffer cb(5);
    cb.push_back(1);
    cb.push_back(2);
    cb.push_back(3);
    cb.push_back(4);
    cb.erase(1, 3);
    EXPECT_EQ(cb.size(), 2);
    EXPECT_EQ(cb[0], 1);
    EXPECT_EQ(cb[1], 4);
    //EXPECT_THROW(cb.erase(2, 1), std::invalid_argument);
    //EXPECT_THROW(cb.erase(-1, 1), std::invalid_argument);
    //EXPECT_THROW(cb.erase(0, 5), std::invalid_argument);
}

TEST(Cleaning, Clear) {
    CircularBuffer cb(5);
    cb.push_back(1);
    cb.push_back(2);
    cb.push_back(3);
    cb.clear();
    EXPECT_EQ(cb.size(), 0);
    EXPECT_TRUE(cb.empty());
}

TEST(Output, StreamOutput) {
    CircularBuffer cb(5);
    cb.push_back(1);
    cb.push_back(2);
    cb.push_back(3);
    std::stringstream ss;
    ss << cb;
    EXPECT_EQ(ss.str(), "1 2 3 \n");
}

TEST(Comparators, Equal) {
    CircularBuffer cb1(5, 10);
    CircularBuffer cb2(5, 10);
    EXPECT_TRUE(cb1 == cb2);
    cb2.push_back(20);
    EXPECT_FALSE(cb1 == cb2);
}

TEST(Comparators, NotEqual) {
    CircularBuffer cb1(5, 10);
    CircularBuffer cb2(5, 10);
    EXPECT_FALSE(cb1 != cb2);
    cb2.push_back(20);
    EXPECT_TRUE(cb1 != cb2);
}


int main(int argc, char** argv) {

	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}
