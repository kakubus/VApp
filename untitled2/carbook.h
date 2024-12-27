#ifndef CARBOOK_H
#define CARBOOK_H

#include <QObject>
#include <QList>
#include "carevent.h"
#include "vehicle.h"

typedef QList<QSharedPointer<CarEvent>> EventsList;

class Vehicle;

class CarBook : public QObject
{
    Q_OBJECT
public:
    explicit CarBook(Vehicle & vehicle);
    ~CarBook();

    void addEvent(QString name, QString description, EventType type, qint64 mileage, float cost);
    void deleteEvent(QSharedPointer<CarEvent> carEventToDelete);
    void modifyEvent(QString name, QString description, EventType type, qint64 mileage, float cost);

    QSharedPointer<CarEvent> getLastEvent();
    float recalculateCosts();

private:
    EventsList _serviceList;
    float _totalCosts;
    Vehicle& _vehicle;


    quint16 numberOfEvents;



    static unsigned int NUMBER_OF_BOOKS;

};

#endif // CARBOOK_H

