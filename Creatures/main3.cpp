#include <iostream>
#include <vector>

class GenericCreature {
public:
    virtual ~GenericCreature() {}
    virtual void eat() = 0; // Pure virtual function
};

class OceanCreature : public virtual GenericCreature {
public:
    void swim() { std::cout << "Swimming...\n"; }
    void eat() override { std::cout << "I eat plankton!\n"; }
};

class TerrestrialCreature : public virtual GenericCreature {
public:
    void walk() { std::cout << "Walking...\n"; }
    void eat() override { std::cout << "I eat plants!\n"; }
};

class Amphibious : public OceanCreature, public TerrestrialCreature {
public:
    void eat() override { std::cout << "I eat insects and small fish!\n"; }
};

class Bird : public TerrestrialCreature {
public:
    void fly() { std::cout << "Flying...\n"; }
    void eat() override { std::cout << "I eat worms and seeds!\n"; }
};

class Waterfowl : public Bird, public OceanCreature {
public:
    void eat() override { std::cout << "I eat fish and aquatic plants!\n"; }
};


int main() {
    // Non-polymorphic behavior
    GenericCreature* creatures_array[] = {new OceanCreature, new TerrestrialCreature, new Amphibious, new Bird, new Waterfowl};
    for (int i = 0; i < 5; ++i) {
        creatures_array[i]->eat();
    }
    for (int i = 0; i < 5; ++i) {
        delete creatures_array[i];
    }

    std::vector<GenericCreature*> creatures;
    creatures.push_back(new OceanCreature);
    creatures.push_back(new TerrestrialCreature);
    creatures.push_back(new Amphibious);
    creatures.push_back(new Bird);
    creatures.push_back(new Waterfowl);

    for (GenericCreature* creature : creatures) {
        creature->eat();
    }

    for (GenericCreature* creature : creatures) {
        delete creature;
    }

    OceanCreature ocean1;
    TerrestrialCreature terr1;
    GenericCreature* gen_ptr;
    gen_ptr = &ocean1;
    gen_ptr->eat();

    return 0;
}

