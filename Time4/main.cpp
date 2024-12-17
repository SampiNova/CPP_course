#include "time/time.hpp"
#include <iostream>

int main() {
  Time t1;
  Time t2(10, 20, 30);
  Time t3(t2);

  std::cout << "t1: " << t1 << std::endl;
  std::cout << "t2: " << t2 << std::endl;
  std::cout << "t3: " << t3 << std::endl;

  Time t4(60,60,24);
  std::cout << "t4 initial: " << t4 << std::endl;
  t4.normalize();
  std::cout << "t4 after normalize: " << t4 << std::endl;
  t4.set_seconds(50);
  t4.set_minutes(100);
  t4.set_hours(30);
  std::cout << "t4 after setting: " << t4 << std::endl;
  t4.normalize();
  std::cout << "t4 after setting and normalize: " << t4 << std::endl;
  std::cout << "Seconds in t4: " << t4.to_seconds() << std::endl;

  Time t5(1,2,3);
  Time t6(4,5,6);
  t5 += t6;
  std::cout << "t5 += t6: " << t5 << std::endl;
  t5 -= t6;
  std::cout << "t5 -= t6: " << t5 << std::endl;
  Time t7 = t5 + t6;
  std::cout << "t5 + t6: " << t7 << std::endl;
  Time t8 = t5 - t6;
  std::cout << "t5 - t6: " << t8 << std::endl;

  t5 += 1000;
  std::cout << "t5 += 1000: " << t5 << std::endl;

  t5 -= 1000;
  std::cout << "t5 -= 1000: " << t5 << std::endl;

  Time t9 = t5 + 1000;
  std::cout << "t5 + 1000: " << t9 << std::endl;

  Time t10 = t5 - 1000;
  std::cout << "t5 - 1000: " << t10 << std::endl;


  std::cout << "t5 == t6: " << (t5 == t6) << std::endl;
  std::cout << "t5 != t6: " << (t5 != t6) << std::endl;

  return 0;
}


