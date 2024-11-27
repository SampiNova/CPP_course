#include <iostream>
#include <vector>

class House {
protected:
  static unsigned house_id;
public:
  virtual ~House() {}
  virtual void build() = 0;
};

unsigned House::house_id = 1;

class WoodHouse : public House {
public:
  void build() override {
    std::cout << "Building wooden house numbered { " << house_id++ << " }...\n";
  }
};

class BrickHouse : public House {
public:
  void build() override {
    std::cout << "Building brick house numbered { " << house_id++ << " }...\n";
  }
};

class ConcreteHouse : public House {
public:
  void build() override {
    std::cout << "Building concrete house numbered { " << house_id++ << " }...\n";
  }
};

class Developer {
public:
  virtual House* BuildHouse() = 0;
  virtual ~Developer() {}
};

class WoodDeveloper : public Developer {
public:
  House* BuildHouse() override {
    return new WoodHouse();
  }
};

class BrickDeveloper : public Developer {
public:
  House* BuildHouse() override {
    return new BrickHouse();
  }
};

class ConcreteDeveloper : public Developer {
public:
  House* BuildHouse() override {
    return new ConcreteHouse();
  }
};

class Quarter {
private:
  std::vector<House*> my_houses;
public:
  Quarter(std::vector<House*> houses) {
    this->my_houses = houses;
  }
  ~Quarter() {
    for (House* house: this->my_houses) {
      delete house;
    }
    this->my_houses.clear();
  }

  House* operator[](int i) {
    return this->my_houses[i];
  }
  std::vector<House*> get_vector() {
    return this->my_houses;
  }
};

Quarter buildQuarter(Developer* developer, int numHouses) {
  if (4 > numHouses || numHouses > 16) throw "Wrong houses count!\n";
  std::cout << "Building quarter with " << numHouses << " houses:\n";
  std::vector<House*> houses;
  for (int i = 0; i < numHouses; i++) {
    House* house = developer->BuildHouse();
    house->build();
    houses.push_back(house);
  }
  std::cout << "Quarter was builded.\n\n";
  return Quarter(houses);
}


int main() {

  WoodDeveloper woodDev;
  BrickDeveloper brickDev;
  ConcreteDeveloper concreteDev;

  buildQuarter(&woodDev, 5);
  buildQuarter(&brickDev, 7);
  buildQuarter(&concreteDev, 10);

  return 0;
}

