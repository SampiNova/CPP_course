#include <iostream>

class GenericCreature {
public:
    GenericCreature() {}
    virtual ~GenericCreature() {}
};

class OceanCreature : public virtual GenericCreature {
public:
    void swim() { std::cout << "Swimming...\n"; }
};

class Amphibious : public virtual OceanCreature {
public:
    void walk() { std::cout << "Walking...\n"; }
};

class TerrestrialCreature : protected Amphibious {
public:
    using Amphibious::walk;
};

class Bird : public TerrestrialCreature {
public:
    void fly() { std::cout << "Flying...\n"; }
};

class Waterfowl : public Bird, public virtual OceanCreature {
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
