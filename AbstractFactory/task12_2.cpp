#include <iostream>
#include <memory>
#include <vector>
#include <string>

class GenericCreature {
public:
    virtual ~GenericCreature() = default;
    virtual std::string getName() const = 0;
    virtual void eat() = 0;
};


class Shark : public GenericCreature {
public:
    std::string getName() const override { return "Акула"; }
    void eat() override { std::cout << "рыбу" << std::endl; }
};

class Dolphin : public GenericCreature {
public:
    std::string getName() const override { return "Дельфин"; }
    void eat() override { std::cout << "мелкую рыбу" << std::endl; }
};

class Lion : public GenericCreature {
public:
    std::string getName() const override { return "Лев"; }
    void eat() override { std::cout << "мясо" << std::endl; }
};

class Elephant : public GenericCreature {
public:
    std::string getName() const override { return "Слон"; }
    void eat() override { std::cout << "траву" << std::endl; }
};

class Crocodile : public GenericCreature {
public:
    std::string getName() const override { return "Крокодил"; }
    void eat() override { std::cout << "рыбу и животных" << std::endl; }
};

class Alligator : public GenericCreature {
public:
    std::string getName() const override { return "Аллигатор"; }
    void eat() override { std::cout << "рыбу и животных" << std::endl; }
};

class Pigeon : public GenericCreature {
public:
    std::string getName() const override { return "Голубь"; }
    void eat() override { std::cout << "семена" << std::endl; }
};

class Parrot : public GenericCreature {
public:
    std::string getName() const override { return "Попугай"; }
    void eat() override { std::cout << "фрукты и орехи" << std::endl; }
};

class Duck : public GenericCreature {
public:
    std::string getName() const override { return "Утка"; }
    void eat() override { std::cout << "насекомых и растения" << std::endl; }
};

class Goose : public GenericCreature {
public:
    std::string getName() const override { return "Гусь"; }
    void eat() override { std::cout << "траву и растения" << std::endl; }
};


class ZooCreator {
public:
    virtual ~ZooCreator() = default;
    virtual std::unique_ptr<GenericCreature> createCreature() = 0;
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
            std::cout << creature->getName() << " ест: ";
            creature->eat();
        }
        std::cout << std::endl;
    }

    return 0;
}

