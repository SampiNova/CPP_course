#include <iostream>

class GenericCreature {
public:
  GenericCreature() {}
  virtual ~GenericCreature() {}
};

class OceanCreature : public GenericCreature {
public:
  void swim() { std::cout << "Swimming...\n"; }
};

class Amphibious : public OceanCreature {
public:
  void walk() { std::cout << "Walking...\n"; }
};

class TerrestrialCreature : public Amphibious {
public:
  void swim() = delete;
};

class Bird : public TerrestrialCreature {
public:
  void fly() { std::cout << "Flying...\n"; }
};

class Waterfowl : public Bird {
public:
  using OceanCreature::swim;
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
