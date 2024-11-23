#include <iostream>

class GenericCreature {
public:
  GenericCreature() {}
  virtual ~GenericCreature() {}
};

class WalkingCreature : public GenericCreature {
public:
  void walk() { std::cout << "Walking...\n"; }
};

class OceanCreature : public GenericCreature {
public:
  void swim() { std::cout << "Swimming...\n"; }
};

class Amphibious : public OceanCreature, public WalkingCreature {
public:

};

class TerrestrialCreature : public WalkingCreature {
public:

};

class Bird : public TerrestrialCreature {
public:
  void fly() { std::cout << "Flying...\n"; }
};

class Waterfowl : public Bird, public OceanCreature {
public:
};

int main() {
  OceanCreature fish;
  fish.swim();

  Amphibious frog;
  frog.swim();
  frog.walk();

  TerrestrialCreature cat;
  cat.walk();

  Bird bird;
  bird.walk();
  bird.fly();

  Waterfowl duck;
  duck.walk();
  duck.fly();
  duck.swim();

  return 0;
}

