#include <iostream>
#include <vector>

class OceanCreature;
class Amphibious;
class TerrestrialCreature;
class Bird;
class Waterflow;

class CreatureVisitor {
public:
    virtual void visit(OceanCreature& creature) = 0;
    virtual void visit(Amphibious& creature) = 0;
    virtual void visit(TerrestrialCreature& creature) = 0;
    virtual void visit(Bird& creature) = 0;
    virtual void visit(Waterflow& creature) = 0;
    virtual ~CreatureVisitor() = default;
};


class GenericCreature {
public:
    virtual ~GenericCreature() {}
    virtual void eat() { std::cout << "Просто ем...\n"; }
    virtual void accept(CreatureVisitor& visitor) = 0; 
};

class OceanCreature : public virtual GenericCreature {
public:
    void swim() { std::cout << "Плыву...\n"; }
    void eat() override { std::cout << "Я ем планктон!\n"; }
    void accept(CreatureVisitor& visitor) override { visitor.visit(*this); }
};

class Amphibious : public virtual OceanCreature {
public:
    void walk() { std::cout << "Иду...\n"; }
    void eat() override { std::cout << "Я ем насекомых и мелкую рыбу!\n"; }
    void accept(CreatureVisitor& visitor) override { visitor.visit(*this); }
};

class TerrestrialCreature : protected Amphibious, public virtual GenericCreature {
public:
    using Amphibious::walk;
    void sleep() { std::cout << "Дремлю в тенёчке...\n"; }
    void eat() override { std::cout << "Я ем растения!\n"; }
    void accept(CreatureVisitor& visitor) override { visitor.visit(*this); }
};

class Bird : public TerrestrialCreature {
public:
    void fly() { std::cout << "Лечу...\n"; }
    void clean() { std::cout << "Чищу перья...\n"; }
    void eat() override { std::cout << "Я ем червей и семена!\n"; }
    void accept(CreatureVisitor& visitor) override { visitor.visit(*this); }
};

class Waterflow : public Bird, public virtual OceanCreature {
public:
    void eat() override { std::cout << "Я ем рыбу и водные растения!\n"; }
    void accept(CreatureVisitor& visitor) override { visitor.visit(*this); }
};


class CreatureActions : public CreatureVisitor {
public:
    void visit(OceanCreature& creature) override {
        creature.swim();
        creature.swim();
        creature.eat();
        creature.swim();
        creature.swim();
    }
    void visit(Amphibious& creature) override {
        creature.walk();
        creature.eat();
        creature.swim();
    }
    void visit(TerrestrialCreature& creature) override {
        creature.walk();
        creature.eat();
        creature.sleep();
    }
    void visit(Bird& creature) override {
        creature.clean();
        creature.walk();
        creature.fly();
    }
    void visit(Waterflow& creature) override {
        creature.clean();
        creature.swim();
        creature.fly();
    }
};


int main() {
    std::vector<GenericCreature*> creatures;
    creatures.push_back(new OceanCreature);
    creatures.push_back(new TerrestrialCreature);
    creatures.push_back(new Amphibious);
    creatures.push_back(new Bird);
    creatures.push_back(new Waterflow);

    CreatureActions actions;
    for (GenericCreature* creature : creatures) {
        creature->accept(actions); 
        std::cout << "\n";
    }

    for (GenericCreature* creature : creatures) {
        delete creature;
    }

    return 0;
}

