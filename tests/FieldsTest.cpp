#include <gtest/gtest.h>
#include "../src/components/Fields.h"
#include "../src/texture/Manager.h"
#include <memory>

class VehicleTest : public ::testing::Test {
protected:
    void SetUp() override {
        vehicle = std::make_unique<Vehicle>(Texture::ID::Car, 1, 1, 0);
    }

    std::unique_ptr<Vehicle> vehicle;
};

TEST_F(VehicleTest, MoveUp) {
    vehicle->moveUp();
    EXPECT_EQ(vehicle->getX(), 0);
}

TEST_F(VehicleTest, MoveDown) {
    vehicle->moveDown();
    EXPECT_EQ(vehicle->getX(), 2);
}

TEST_F(VehicleTest, MoveLeft) {
    vehicle->moveLeft();
    EXPECT_EQ(vehicle->getY(), 0);
}

TEST_F(VehicleTest, MoveRight) {
    vehicle->moveRight();
    EXPECT_EQ(vehicle->getY(), 2);
}

// TEST_F(VehicleTest, SetPosition) {
//     Point newPos(2, 2);
//     vehicle->setPosition(newPos);
//     EXPECT_EQ(vehicle->getX(), 2);
//     EXPECT_EQ(vehicle->getY(), 2);
// }

TEST_F(VehicleTest, SetID) {
    vehicle->setID(Texture::ID::Bike);
    EXPECT_EQ(vehicle->getID(), Texture::ID::Bike);
}

class FieldTest : public ::testing::Test {
protected:
    void SetUp() override {
        field = std::make_unique<Field>();
    }

    std::unique_ptr<Field> field;
};

TEST_F(FieldTest, SetVehicle) {
    auto vehicle = std::make_shared<Car>(1, 1, 0);
    field->setVehicle(true, vehicle);
    EXPECT_TRUE(field->isOccupied());
}

TEST_F(FieldTest, IsOccupied) {
    EXPECT_FALSE(field->isOccupied());
    auto vehicle = std::make_shared<Car>(1, 1, 0);
    field->setVehicle(true, vehicle);
    EXPECT_TRUE(field->isOccupied());
}

TEST_F(FieldTest, GetID) {
    EXPECT_EQ(field->getID(), Texture::ID::Default);
    field->textureID = Texture::ID::Road;
    EXPECT_EQ(field->getID(), Texture::ID::Road);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}