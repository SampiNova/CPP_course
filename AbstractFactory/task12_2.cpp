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

// Terrestrial
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

// Amphibious
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

// Bird
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
    virtual std::vector<std::unique_ptr<GenericCreature>> createCreatures() = 0;
};

class OceanCreator : public ZooCreator {
public:
    std::vector<std::unique_ptr<GenericCreature>> createCreatures() override {
        std::vector<std::unique_ptr<GenericCreature>> res;
        res.push_back(std::make_unique<Dolphin>());
        res.push_back(std::make_unique<Shark>());

        return res;
    }
};

class TerrestrialCreator : public ZooCreator {
public:
    std::vector<std::unique_ptr<GenericCreature>> createCreatures() override {
        std::vector<std::unique_ptr<GenericCreature>> res;
        res.push_back(std::make_unique<Lion>());
        res.push_back(std::make_unique<Elephant>());

        return res;
    }
};

class AmphibiousCreator : public ZooCreator {
public:
    std::vector<std::unique_ptr<GenericCreature>> createCreatures() override {
        std::vector<std::unique_ptr<GenericCreature>> res;
        res.push_back(std::make_unique<Alligator>());
        res.push_back(std::make_unique<Crocodile>());

        return res;
    }
};

class BirdCreator : public ZooCreator {
public:
    std::vector<std::unique_ptr<GenericCreature>> createCreatures() override {
        std::vector<std::unique_ptr<GenericCreature>> res;
        res.push_back(std::make_unique<Pigeon>());
        res.push_back(std::make_unique<Parrot>());

        return res;
    }
};

class WaterfowlCreator : public ZooCreator {
public:
    std::vector<std::unique_ptr<GenericCreature>> createCreatures() override {
        std::vector<std::unique_ptr<GenericCreature>> res;
        res.push_back(std::make_unique<Goose>());
        res.push_back(std::make_unique<Duck>());

        return res;
    }
};



int main() {
    std::vector<std::unique_ptr<ZooCreator>> creators;
    creators.push_back(std::make_unique<OceanCreator>());
    creators.push_back(std::make_unique<TerrestrialCreator>());
    creators.push_back(std::make_unique<AmphibiousCreator>());
    creators.push_back(std::make_unique<BirdCreator>());
    creators.push_back(std::make_unique<WaterfowlCreator>());

    for (auto& creator : creators) {
        auto creatures = creator->createCreatures();
        for (auto& animal : creatures) {
            std::cout << animal->getName() << " is eating: ";
            animal->eat();
            std::cout << std::endl;
        }
    }

    return 0;
}
