#include <iostream>
#include <vector>
#include <memory>

class GenericCreature {
public:
    virtual ~GenericCreature() {}
    virtual void eat() = 0;
    virtual std::string getName() const = 0;
};

// Ocean Creatures
class OceanCreature : public virtual GenericCreature {
public:
    void swim() { std::cout << "Swimming...\n"; }
    virtual void eat() override = 0;
    virtual std::string getName() const = 0;
};

class Shark : public OceanCreature {
public:
    void eat() override { std::cout << "Shark eats fish!\n"; }
    std::string getName() const override { return "Shark"; }
};

class Dolphin : public OceanCreature {
public:
    void eat() override { std::cout << "Dolphin eats krill!\n"; }
    std::string getName() const override { return "Dolphin"; }
};

class TerrestrialCreature : public virtual GenericCreature {
public:
    void walk() { std::cout << "Walking...\n"; }
    virtual void eat() override = 0;
    virtual std::string getName() const = 0;
};

class Lion : public TerrestrialCreature {
public:
    void eat() override { std::cout << "Lion eats meat!\n"; }
    std::string getName() const override { return "Lion"; }
};

class Elephant : public TerrestrialCreature {
public:
    void eat() override { std::cout << "Elephant eats plants!\n"; }
    std::string getName() const override { return "Elephant"; }
};

class Amphibious : public OceanCreature, public TerrestrialCreature {
public:
    virtual void eat() override = 0;
    virtual std::string getName() const = 0;
};

class Crocodile : public Amphibious {
public:
    void eat() override { std::cout << "Crocodile eats fish and reptiles!\n"; }
    std::string getName() const override { return "Crocodile"; }
};

class Alligator : public Amphibious {
public:
    void eat() override { std::cout << "Alligator eats fish and birds!\n"; }
    std::string getName() const override { return "Alligator"; }
};

class Bird : public TerrestrialCreature {
public:
    virtual void fly() { std::cout << "Flying...\n"; }
    virtual void eat() override = 0;
    virtual std::string getName() const = 0;
};

class Pigeon : public Bird {
public:
    void eat() override { std::cout << "Pigeon eats seeds and scraps!\n"; }
    std::string getName() const override { return "Pigeon"; }
};

class Parrot : public Bird {
public:
    void eat() override { std::cout << "Parrot eats fruits and nuts!\n"; }
    std::string getName() const override { return "Parrot"; }
};


// Waterfowl
class Waterfowl : public Bird, public OceanCreature {
public:
    void eat() override { std::cout << "Waterfowl eats fish and aquatic plants!\n"; }
    std::string getName() const override { return "Waterfowl"; }
};

class Duck : public Waterfowl {
public:
    void eat() override { std::cout << "Duck eats aquatic plants and insects!\n"; }
    std::string getName() const override { return "Duck"; }
};

class Goose : public Waterfowl {
public:
    void eat() override { std::cout << "Goose eats grass and grains!\n"; }
    std::string getName() const override { return "Goose"; }
};

class ZooCreator {
public:
    virtual std::unique_ptr<GenericCreature> createCreature() = 0;
    virtual ~ZooCreator() = default;
};

class SharkCreator : public ZooCreator {
public:
    std::unique_ptr<GenericCreature> createCreature() override { return std::make_unique<Shark>(); }
};

class DolphinCreator : public ZooCreator {
public:
    std::unique_ptr<GenericCreature> createCreature() override { return std::make_unique<Dolphin>(); }
};

class LionCreator : public ZooCreator {
public:
    std::unique_ptr<GenericCreature> createCreature() override { return std::make_unique<Lion>(); }
};

class ElephantCreator : public ZooCreator {
public:
    std::unique_ptr<GenericCreature> createCreature() override { return std::make_unique<Elephant>(); }
};

class CrocodileCreator : public ZooCreator {
public:
    std::unique_ptr<GenericCreature> createCreature() override { return std::make_unique<Crocodile>(); }
};

class AlligatorCreator : public ZooCreator {
public:
    std::unique_ptr<GenericCreature> createCreature() override { return std::make_unique<Alligator>(); }
};

class PigeonCreator : public ZooCreator {
public:
    std::unique_ptr<GenericCreature> createCreature() override { return std::make_unique<Pigeon>(); }
};

class ParrotCreator : public ZooCreator {
public:
    std::unique_ptr<GenericCreature> createCreature() override { return std::make_unique<Parrot>(); }
};

class DuckCreator : public ZooCreator {
public:
    std::unique_ptr<GenericCreature> createCreature() override { return std::make_unique<Duck>(); }
};

class GooseCreator : public ZooCreator {
public:
    std::unique_ptr<GenericCreature> createCreature() override { return std::make_unique<Goose>(); }
};


int main() {
    std::vector<std::unique_ptr<ZooCreator>> creators;
    creators.push_back(std::make_unique<SharkCreator>());
    creators.push_back(std::make_unique<DolphinCreator>());
    creators.push_back(std::make_unique<LionCreator>());
    creators.push_back(std::make_unique<ElephantCreator>());
    creators.push_back(std::make_unique<CrocodileCreator>());
    creators.push_back(std::make_unique<AlligatorCreator>());
    creators.push_back(std::make_unique<PigeonCreator>());
    creators.push_back(std::make_unique<ParrotCreator>());
    creators.push_back(std::make_unique<DuckCreator>());
    creators.push_back(std::make_unique<GooseCreator>());

    for (auto& creator : creators) {
        for (int i = 0; i < 3; ++i) {
            auto creature = creator->createCreature();
            std::cout << creature->getName() << " is eating: ";
            creature->eat();
        }
        std::cout << std::endl;
    }

    return 0;
}
