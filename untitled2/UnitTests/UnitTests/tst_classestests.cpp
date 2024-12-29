#include <gmock/gmock-matchers.h>
#include <gtest/gtest.h>

#include "../../../../VApp/untitled2/vehicle.h"
#include "../../../../VApp/untitled2/carbook.h"
#include "../../../../VApp/untitled2/carevent.h"

using namespace testing;

struct VehicleClassTest : public Test{
    Vehicle *v1;
    Vehicle *v2;
    void SetUp(){
        v1 = new Vehicle("VW", "T4", 2003);
        v2 = new Vehicle();
        qDebug() << "Test fixture vehicle has been created.\n";

    }
    void TearDown() {
        delete v1;
        delete v2;
        qDebug() << "Test fixture vehicle has been removed.\n";
    }
};

TEST(Base_Tst, Base)
{
    EXPECT_EQ(1, 1);
    ASSERT_THAT(0, Eq(0));
}

TEST_F(VehicleClassTest, VehicleCreation){
    VehicleTuple vehicle1_data = v1->getVehicleData();
    VehicleTuple vehicle2_data = v2->getVehicleData();

    EXPECT_EQ(std::get<0>(vehicle1_data), "VW");
    EXPECT_EQ(std::get<1>(vehicle1_data), "T4");
    EXPECT_EQ(std::get<2>(vehicle1_data), "ABCDEFGHIJK1234");
    EXPECT_EQ(std::get<3>(vehicle1_data), 2003);

    EXPECT_EQ(std::get<0>(vehicle2_data), "VehicleMark");
    EXPECT_EQ(std::get<1>(vehicle2_data), "Fantastic Mk2");
    EXPECT_EQ(std::get<2>(vehicle2_data), "ABCDEFGHIJK1234");
    EXPECT_EQ(std::get<3>(vehicle2_data), 1998);
}

TEST_F(VehicleClassTest, CarBookCreation){

}

//TEST(Base_Tst, CarBookCreation){

    // Arrange
    //Vehicle *v1 = new Vehicle();
//  Vehicle *v2 = new Vehicle();
// Act

// Assert
//   ASSERT_FALSE(EXPECT_EQ(v2->carBook(), v1->carBook()));
//}
