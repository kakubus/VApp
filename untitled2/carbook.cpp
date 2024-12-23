#include "carbook.h"
#include "vehicle.h"
unsigned int CarBook::NUMBER_OF_BOOKS = 0;

CarBook::CarBook(Vehicle & vehicle)
    : _vehicle(vehicle), _totalCosts(0) {
    CarBook::NUMBER_OF_BOOKS++;
    qDebug() << Q_FUNC_INFO << "CarBook("<< CarBook::NUMBER_OF_BOOKS <<") created for vehicle";
}

CarBook::~CarBook(){
    CarBook::NUMBER_OF_BOOKS--;
    qDebug() << Q_FUNC_INFO << "CarBook("<< CarBook::NUMBER_OF_BOOKS <<") is deleting. Clear all service list.";
    _serviceList.clear();
}

void CarBook::addEvent(QString name, QString description, EventType type, qint64 mileage, float cost){
    qDebug() << Q_FUNC_INFO << "Creating new Car Event";
    _serviceList.push_back(QSharedPointer<CarEvent>::create(name,
                                                      description,
                                                      type,
                                                      mileage,
                                                      cost));
}

void CarBook::deleteEvent(QSharedPointer<CarEvent> carEventToDelete){
    qDebug() << Q_FUNC_INFO << "Delete Car Event"  ;
    _serviceList.removeOne(carEventToDelete);
}

QSharedPointer<CarEvent> CarBook::getLastEvent(){
    return (QSharedPointer<CarEvent>)this->_serviceList.last();
}

float CarBook::recalculateCosts(){
    float total_cost = 0;
    for(auto event: this->_serviceList){
        total_cost += event.get()->_cost;
    }
    return total_cost;
}
