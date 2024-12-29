#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <gtest/gtest.h>

#include "vehicle.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("untitled2", "Main");
/*
    std::unique_ptr<Vehicle> v1(new Vehicle("VW", "Golf II", 1985));
    Vehicle* someShit = new Vehicle("VW", "Golf", 2000);
    someShit->carBook()->addEvent("Oil change", "5w30 Dexos2", EventType::SERVICE, 126500, 100);
    someShit->carBook()->addEvent("Oil change 2", "5w30 Dexos2", EventType::SERVICE, 136500, 200);

    Vehicle* someShit2 = new Vehicle("Fiat", "Panda", 2004);
    someShit2->carBook()->addEvent("Oil change", "10w30 Mobil", EventType::SERVICE, 26500, 104.55);

    someShit2->carBook()->addEvent("Oil change 3", "5w30 Dexos2", EventType::SERVICE, 146500, 100.00);
    someShit->carBook()->deleteEvent(someShit->carBook()->getLastEvent());
    someShit->addEventToCarBook("Filter change", "Air, cabin", EventType::SERVICE, 15600, 44.00);
    auto tmpEvent = someShit->carBook()->getLastEvent();
    someShit->carBook()->modifyEvent(tmpEvent, "Filter and oil change", "Air, cabin, oil filters", EventType::SERVICE, 15650, 144.00);


    delete someShit;
*/

    ::testing::InitGoogleTest(&argc, argv);
    RUN_ALL_TESTS();
    return app.exec();
}
