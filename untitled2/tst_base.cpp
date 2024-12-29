#include <gmock/gmock-matchers.h>
#include <gtest/gtest.h>

#include <QLoggingCategory>

#include "vehicle.h"
#include "carbook.h"
#include "carevent.h"

#define QT_NO_DEBUG_OUTPUT

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

    ASSERT_NE(v1, v2);
}

TEST_F(VehicleClassTest, carBookCreation){
    auto carBook1 = v1->carBook();
    auto carBook2 = v2->carBook();

    ASSERT_NE(carBook1, carBook2);
    ASSERT_EQ(carBook1->getLastEvent(), nullptr);
}

TEST_F(VehicleClassTest, carBookGetEventFromCarBookWhenEventsAreEmpty){
    auto carBook1 = v1->carBook();
    auto carBook2 = v2->carBook();

    // List after creation Vehicle is empty, so it should be true.
    EXPECT_EQ(carBook1->getEventFromCarBook(0), nullptr);
    EXPECT_EQ(carBook2->getEventFromCarBook(1), nullptr);

}


TEST_F(VehicleClassTest, carBookAddEventAndCheckTotalCosts){
    auto carBook1 = v1->carBook();

    // After creation Vehicle, totalCosts should be (at this moment
    ASSERT_EQ(carBook1->getTotalCosts(), 0.00);

    // Add new event
    carBook1->addEvent("TestEvent",
                       "This is event for test",
                       EventType::YEARLY_INSPECTION,
                       1234567890,
                       999.99
                       );

    // After add new event, it should be possible to return non-nullptr object.
    auto lastEvent = carBook1->getLastEvent();
    EXPECT_NE(lastEvent, nullptr);

    // Check data
    EXPECT_EQ(lastEvent->_name, "TestEvent");
    EXPECT_EQ(lastEvent->_description, "This is event for test");
    EXPECT_EQ(lastEvent->_service, EventType::YEARLY_INSPECTION);
    EXPECT_EQ(lastEvent->_mileage, 1234567890);
    EXPECT_EQ(lastEvent->_cost, (float)999.99);

    ASSERT_EQ(carBook1->getTotalCosts(), (float)999.99);

}

TEST_F(VehicleClassTest, carBookRecalculateCostsWithAddSecondEvent){
    auto carBook1 = v1->carBook();
    ASSERT_EQ(carBook1->recalculateCosts(), (float)0.00);

    // Add new event
    carBook1->addEvent("TestEvent",
                       "This is event for test",
                       EventType::YEARLY_INSPECTION,
                       1234567890,
                       999.99
                       );
    carBook1->addEvent("TestEventSecond",
                       "This is second event for test",
                       EventType::YEARLY_INSPECTION,
                       1234567895,
                       0.01
                       );
    EXPECT_EQ(carBook1->getLastEvent()->_mileage, 1234567895);
    // Now after add second event, total cost should be updated automatically.
    EXPECT_EQ(carBook1->getTotalCosts(), (float)1000.00);
    // Check again if direct method recalculateCosts() will return proper value.
    ASSERT_EQ(carBook1->recalculateCosts(), (float)1000.00);

}

TEST_F(VehicleClassTest, carBookModifyEvent){
    auto carBook1 = v1->carBook();
    ASSERT_EQ(carBook1->recalculateCosts(), (float)0.00);

    // Add new event
    carBook1->addEvent("TestEvent",
                       "This is event for test",
                       EventType::YEARLY_INSPECTION,
                       1234567890,
                       999.99
                       );
    carBook1->addEvent("TestEventSecond",
                       "This is event for test",
                       EventType::YEARLY_INSPECTION,
                       1234567895,
                       0.01
                       );
    auto eventToModify = carBook1->getEventFromCarBook(0);

    carBook1->modifyEvent(eventToModify, NULL, "Modified description", EventType::BODY_REPAIR, 1000, 26.00);

    // Check after modifications
    EXPECT_EQ(eventToModify->_name, "TestEvent");
    EXPECT_EQ(eventToModify->_description, "Modified description");
    EXPECT_NE(eventToModify->_service, EventType::YEARLY_INSPECTION);
    EXPECT_EQ(eventToModify->_mileage, 1000);
    EXPECT_NE(eventToModify->_cost, (float)999.99);

    ASSERT_EQ(carBook1->recalculateCosts(), float(26.01));
}

TEST_F(VehicleClassTest, carBookDeleteEvent){
    auto carBook1 = v1->carBook();
    ASSERT_EQ(carBook1->recalculateCosts(), (float)0.00);

    // Add new event
    carBook1->addEvent("TestEvent",
                       "This is event for test",
                       EventType::YEARLY_INSPECTION,
                       1234567890,
                       999.99
                       );
    carBook1->addEvent("TestEventSecond",
                       "This is event for test",
                       EventType::YEARLY_INSPECTION,
                       1234567895,
                       0.01
                       );
    auto eventToDelete = carBook1->getEventFromCarBook(0);

    // Delete first (by history) event
    carBook1->deleteEvent(eventToDelete);

    auto lastEvent = carBook1->getLastEvent();

    // Check if second event is second event.
    EXPECT_EQ(lastEvent->_name, "TestEventSecond");
    EXPECT_EQ(carBook1->getTotalCosts(), (float)0.01);

    // Delete last (second) event
    carBook1->deleteEvent(lastEvent);

    // Last event has been delete, so _serviceList should be empty.
    // If empty, then method getLastEvent should return 'nullptr'.
    ASSERT_EQ(carBook1->getLastEvent(), nullptr);
}

