#ifndef VEHICLE_H
#define VEHICLE_H

#include <QObject>
#include "carbook.h"
#include <QSharedPointer>

#define QT_NO_DEBUG_OUTPUT

class CarBook;

typedef QList<QSharedPointer<CarEvent>> EventsList;
typedef std::tuple<QString, QString, QString, qint32> VehicleTuple;

class Vehicle : public QObject
{
    Q_OBJECT
public:
    Vehicle();
    Vehicle(QString mark, QString model, qint32 year);
    ~Vehicle();

    QSharedPointer<CarBook> carBook() const {return _carBook; }

    void addEventToCarBook(QString name, QString description, EventType type, qint64 mileage, float cost);
    float getVehicleMaintenanceCost();      // It includes all service costs.
    float getVehicleTotalCost();            // It includes purchase cost and all services costs.

    VehicleTuple getVehicleData();

    EventsList* getEventsFromCarBook();

private:
    QString _mark;
    QString _model;
    QString _VIN;
    qint32 _year;

    //CarBook* _carBook;
    QSharedPointer<CarBook> _carBook;




};

#endif // VEHICLE_H
