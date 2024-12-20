#include <iostream>
#include <string>
#include <vector>

class House {
public:
    std::string walls;
    std::string floor;
    std::string roof;
    std::vector<std::string> additionalElements;

    void showHouseDetails() const {
        std::cout << "Дом:\n";
        std::cout << "Стены: " << walls << "\n";
        std::cout << "Пол: " << floor << "\n";
        std::cout << "Крыша: " << roof << "\n";
        std::cout << "Дополнительные элементы:\n";
        for (const auto& element : additionalElements) {
            std::cout << "- " << element << "\n";
        }
        std::cout << std::endl;
    }
};


class HouseDocumentation {
public:
    std::string houseDescription;
    std::vector<std::string> elementDescriptions;

    void addElementDescription(const std::string& description) {
        elementDescriptions.push_back(description);
    }

    void showDocumentation() const {
        std::cout << "Документация:\n";
        std::cout << houseDescription << "\n";
        std::cout << "Описание элементов:\n";
        for (const auto& description : elementDescriptions) {
            std::cout << description << "\n";
        }
        std::cout << std::endl;
    }
};


class HouseBuilder {
public:
    virtual ~HouseBuilder() = default;
    virtual void buildWalls() = 0;
    virtual void buildFloor() = 0;
    virtual void buildRoof() = 0;
    virtual House* getHouse() = 0;
    virtual HouseDocumentation* getDocumentation() = 0;
};

class WoodenHouseBuilder : public HouseBuilder {
private:
    House* house;
    HouseDocumentation* documentation;
public:
    WoodenHouseBuilder() : house(new House()), documentation(new HouseDocumentation()) {
        documentation->houseDescription = "Документация для деревянного дома";
    }

    ~WoodenHouseBuilder() override { delete house; delete documentation; }

    void buildWalls() override {
        house->walls = "Деревянные стены";
        documentation->addElementDescription("Описание деревянных стен");
    }
    void buildFloor() override {
        house->floor = "Деревянный пол";
        documentation->addElementDescription("Описание деревянного пола");
    }
    void buildRoof() override {
        house->roof = "Деревянная крыша";
        documentation->addElementDescription("Описание деревянной крыши");
    }
    House* getHouse() override { return house; }
    HouseDocumentation* getDocumentation() override { return documentation; }
};

class BrickHouseBuilder : public HouseBuilder {
private:
    House* house;
    HouseDocumentation* documentation;
public:
    BrickHouseBuilder() : house(new House()), documentation(new HouseDocumentation()) {
        documentation->houseDescription = "Документация для кирпичного дома";
    }
    ~BrickHouseBuilder() override {
        delete house;
        delete documentation;
    }

    void buildWalls() override {
        house->walls = "Кирпичные стены";
        documentation->addElementDescription("Описание кирпичных стен");
    }
    void buildFloor() override {
        house->floor = "Бетонный пол";
        documentation->addElementDescription("Описание бетонного пола");
    }
    void buildRoof() override {
        house->roof = "Металлическая крыша";
        documentation->addElementDescription("Описание металлической крыши");
    }
    House* getHouse() override { return house; }
    HouseDocumentation* getDocumentation() override { return documentation; }
};


int main() {
    WoodenHouseBuilder woodenBuilder;
    woodenBuilder.buildWalls();
    woodenBuilder.buildFloor();
    woodenBuilder.buildRoof();
    woodenBuilder.getHouse()->additionalElements.push_back("Дровяная печь");

    woodenBuilder.getHouse()->showHouseDetails();
    woodenBuilder.getDocumentation()->showDocumentation();

    BrickHouseBuilder brickBuilder;
    brickBuilder.buildWalls();
    brickBuilder.buildFloor();
    brickBuilder.buildRoof();
    brickBuilder.getHouse()->additionalElements.push_back("Камин");
    brickBuilder.getHouse()->additionalElements.push_back("Система кондиционирования");

    brickBuilder.getHouse()->showHouseDetails();
    brickBuilder.getDocumentation()->showDocumentation();

    return 0;
}

