#include <iostream>
#include <vector>
#include <memory>

class House {
public:
  virtual ~House() {}
  virtual void build() = 0;
  virtual std::string getType() const = 0;
};

class Fence {
public:
  virtual ~Fence() {}
  virtual void build() = 0;
  virtual std::string getType() const = 0;
};

class Barn {
public:
  virtual ~Barn() {}
  virtual void build() = 0;
  virtual std::string getType() const = 0;
};


class WoodHouse : public House {
public:
  void build() override { std::cout << "Building wooden house...\n"; }
  std::string getType() const override { return "Wooden House\n"; }
};

class BrickHouse : public House {
public:
  void build() override { std::cout << "Building brick house...\n"; }
  std::string getType() const override { return "Brick House\n"; }
};

class ConcreteHouse : public House {
public:
  void build() override { std::cout << "Building concrete house...\n"; }
  std::string getType() const override { return "Concrete House\n"; }
};


class WoodFence : public Fence {
public:
  void build() override { std::cout << "Building wooden fence...\n"; }
  std::string getType() const override { return "Wooden Fence\n"; }
};

class BrickFence : public Fence {
public:
  void build() override { std::cout << "Building brick fence...\n"; }
  std::string getType() const override { return "Brick Fence"; }
};

class ConcreteFence : public Fence {
public:
  void build() override { std::cout << "Building concrete fence...\n"; }
  std::string getType() const override { return "Concrete Fence\n"; }
};


class WoodBarn : public Barn {
public:
  void build() override { std::cout << "Building wooden barn...\n"; }
  std::string getType() const override { return "Wooden Barn\n"; }
};

class BrickBarn : public Barn {
public:
  void build() override { std::cout << "Building brick barn...\n"; }
  std::string getType() const override { return "Brick Barn\n"; }
};

class ConcreteBarn : public Barn {
public:
  void build() override { std::cout << "Building concrete barn...\n"; }
  std::string getType() const override { return "Concrete Barn\n"; }
};

class Developer {
public:
  virtual ~Developer() {}
  virtual std::unique_ptr<House> BuildHouse() = 0;
  virtual std::unique_ptr<Fence> BuildFence() = 0;
  virtual std::unique_ptr<Barn> BuildBarn() = 0;
};

class WoodDeveloper : public Developer {
public:
  std::unique_ptr<House> BuildHouse() override { return std::make_unique<WoodHouse>(); }
  std::unique_ptr<Fence> BuildFence() override { return std::make_unique<WoodFence>(); }
  std::unique_ptr<Barn> BuildBarn() override { return std::make_unique<WoodBarn>(); }
};

class BrickDeveloper : public Developer {
public:
  std::unique_ptr<House> BuildHouse() override { return std::make_unique<BrickHouse>(); }
  std::unique_ptr<Fence> BuildFence() override { return std::make_unique<BrickFence>(); }
  std::unique_ptr<Barn> BuildBarn() override { return std::make_unique<BrickBarn>(); }
};

class ConcreteDeveloper : public Developer {
public:
  std::unique_ptr<House> BuildHouse() override { return std::make_unique<ConcreteHouse>(); }
  std::unique_ptr<Fence> BuildFence() override { return std::make_unique<ConcreteFence>(); }
  std::unique_ptr<Barn> BuildBarn() override { return std::make_unique<ConcreteBarn>(); }
};


int main() {
  std::unique_ptr<Developer> developer = std::make_unique<BrickDeveloper>();

  std::cout << "Building a plot with Brick style\n";

  auto house = developer->BuildHouse();
  auto fence = developer->BuildFence();
  auto barn = developer->BuildBarn();

  house->build();
  fence->build();
  barn->build();

  std::cout << "Plot built successfully!\n";

  return 0;
}
