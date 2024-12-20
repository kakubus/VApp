#include <QGuiApplication>
#include <QQmlApplicationEngine>

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

    std::unique_ptr<Vehicle> v1(new Vehicle("VW", "Golf II", 1985));
    Vehicle* someShit = new Vehicle("VW", "Golf", 2000);
    someShit->carBook()->addEvent("Oil change", "5w30 Dexos2", EventType::SERVICE, 126500, 204.55);
    someShit->carBook()->addEvent("Oil change 2", "5w30 Dexos2", EventType::SERVICE, 136500, 244.55);

    Vehicle* someShit2 = new Vehicle("Fiat", "Panda", 2004);
    someShit2->carBook()->addEvent("Oil change", "10w30 Mobil", EventType::SERVICE, 26500, 104.55);

    someShit->carBook()->addEvent("Oil change 3", "5w30 Dexos2", EventType::SERVICE, 146500, 284.55);
    someShit->carBook()->deleteEvent(someShit->carBook()->getLastEvent());
    delete someShit;
    return app.exec();
}
