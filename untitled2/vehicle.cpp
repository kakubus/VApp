#include "vehicle.h"
#include "carbook.h"

Vehicle::Vehicle() {
    _mark = "VehicleMark";
    _model = "Fantastic Mk2";
    _VIN = "ABCDEFGHIJK1234";
    _year= 1998;
    _carBook = QSharedPointer<CarBook>::create(*this);

    qDebug() << Q_FUNC_INFO << "Created vehicle with Car Book";
}

Vehicle::Vehicle(QString mark, QString model, qint32 year){
    _mark = mark;
    _model = model;
    _VIN = "ABCDEFGHIJK1234";
    _year= (year > 1900) ? year : 1900;
    _carBook = QSharedPointer<CarBook>::create(*this);

    qDebug() << Q_FUNC_INFO << "Created vehicle with Car Book with parameters:"
             << "\n\tMark: " << _mark
             << "\n\tModel: " << _model
             << "\n\tVIN: " << _VIN
             << "\n\tYear: " << _year;
}

Vehicle::~Vehicle(){
    qDebug() << Q_FUNC_INFO << "Vehicle deleted. CarBook delete() called.";
}

void Vehicle::addEventToCarBook(QString name, QString description, EventType type, qint64 mileage, float cost){
    carBook()->addEvent(name, description, type, mileage, cost);
    float actual_totalCost = carBook()->recalculateCosts();

    qDebug() << Q_FUNC_INFO << " -> Actual total costs of vehicle: " << actual_totalCost;
}
