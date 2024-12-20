#include "carevent.h"
unsigned int CarEvent::NUMBER_OF_EVENTS = 0;

CarEvent::CarEvent()
    : _timestamp(QDateTime::currentDateTime()) {
    _name = "Generic event";
    _description = "Some of generic maintenance.";
    _mileage = 10200;
    _cost = 100;
    CarEvent::NUMBER_OF_EVENTS++;

    qDebug() << Q_FUNC_INFO <<"Created CarEvent(" << CarEvent::NUMBER_OF_EVENTS << ") with default parameters:"
             << "\n\tName: " << _name
             << "\n\tDescription: " << _description
             << "\n\tMileage [km]: " << _mileage
             << "\n\tDate: " << _timestamp
             << "\n\tCost: " << _cost;
}

CarEvent::CarEvent(QString name, QString description, EventType type, qint64 mileage, float cost)
    : _timestamp(QDateTime::currentDateTime()) {
    _name = name;
    _description = description;
    _mileage = (mileage > 0) ? mileage : 1;
    _cost = (cost > 0) ? cost : (float)0;
    CarEvent::NUMBER_OF_EVENTS++;

    qDebug() << Q_FUNC_INFO <<"Created CarEvent(" << CarEvent::NUMBER_OF_EVENTS << ") with default parameters:"
             << "\n\tName: " << _name
             << "\n\tDescription: " << _description
             << "\n\tMileage [km]: " << _mileage
             << "\n\tDate: " << _timestamp
             << "\n\tCost: " << _cost;

}

CarEvent::~CarEvent(){
    CarEvent::NUMBER_OF_EVENTS--;
    qDebug() << Q_FUNC_INFO << "Deleted CarEvent(" << CarEvent::NUMBER_OF_EVENTS << ")";
}

QSharedPointer<CarEvent> CarEvent::get(){
    return (QSharedPointer<CarEvent>)this;
}
