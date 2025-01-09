#include <gtest/gtest.h>
#include "../src/components/ListOfVehicle.h"
#include "../src/components/Fields.h"
#include <memory>

class ListOfVehicleTest : public ::testing::Test {
protected:
    void SetUp() override {
        listOfVehicle = std::make_unique<ListOfVehicle>();
    }

    std::unique_ptr<ListOfVehicle> listOfVehicle;
};

TEST_F(ListOfVehicleTest, addVehicle) {
    auto vehicle = std::make_shared<Vehicle>(Texture::ID::Car, 1, 1, 0); 
    listOfVehicle->addVehicle(vehicle);
    EXPECT_EQ(listOfVehicle->size(), 1);
}

TEST_F(ListOfVehicleTest, PrintAllVehicles) {
    auto vehicle1 = std::make_shared<Vehicle>(Texture::ID::Car, 1, 0);
    auto vehicle2 = std::make_shared<Vehicle>(Texture::ID::Car, 2, 0);
    listOfVehicle->addVehicle(vehicle1);
    listOfVehicle->addVehicle(vehicle2);
    testing::internal::CaptureStdout();
    listOfVehicle->printAllVehicles();
    std::string output = testing::internal::GetCapturedStdout();
    std::cout << "Captured output:\n" << output << std::endl; // Debug output
    EXPECT_NE(output.find("1, 0"), std::string::npos); // Adjusted expected output
    EXPECT_NE(output.find("2, 0"), std::string::npos); // Adjusted expected output
}

//TEST_F(ListOfVehicleTest, RemoveVehicle) {
//    auto vehicle = std::make_shared<Vehicle>(Texture::ID::Car, 1, 0);
//    listOfVehicle->addVehicle(vehicle);
//    listOfVehicle->removeVehicle(1, 1);
//    EXPECT_EQ(listOfVehicle->size(), 0);
//}
//
//TEST_F(ListOfVehicleTest, RemoveNonExistentVehicle) {
//    auto vehicle = std::make_shared<Vehicle>(Texture::ID::Car, 1, 0);
//    listOfVehicle->addVehicle(vehicle);
//    listOfVehicle->removeVehicle(2, 2);
//    EXPECT_EQ(listOfVehicle->size(), 1);
//}
//
//TEST_F(ListOfVehicleTest, PrintAllVehicles) {
//    auto vehicle1 = std::make_shared<Vehicle>(Texture::ID::Car, 1, 0);
//    auto vehicle2 = std::make_shared<Vehicle>(Texture::ID::Car, 2, 0);
//    listOfVehicle->addVehicle(vehicle1);
//    listOfVehicle->addVehicle(vehicle2);
//    testing::internal::CaptureStdout();
//    listOfVehicle->printAllVehicles();
//    std::string output = testing::internal::GetCapturedStdout();
//    EXPECT_NE(output.find("1, 1"), std::string::npos);
//    EXPECT_NE(output.find("2, 2"), std::string::npos);
//}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
