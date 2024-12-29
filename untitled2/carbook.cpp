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
    _totalCosts += cost;
}

void CarBook::deleteEvent(QSharedPointer<CarEvent> carEventToDelete){
    qDebug() << Q_FUNC_INFO << "Delete Car Event"  ;
    _totalCosts -= carEventToDelete->_cost;
  // _totalCosts = std::roundf(_totalCosts);
    _serviceList.removeOne(carEventToDelete);
}

QSharedPointer<CarEvent> CarBook::findEvent(QSharedPointer<CarEvent> elementToFind){
    auto founded = std::find(_serviceList.begin(), _serviceList.end(), elementToFind);

    if(founded != _serviceList.end()){
        qDebug() << Q_FUNC_INFO << "Found element ("<< elementToFind <<") at list.";
        return *founded;
    }
    else{
        qDebug() << Q_FUNC_INFO << "Element ("<< elementToFind <<") not found at list.";
        return nullptr;
    }
}

QSharedPointer<CarEvent> CarBook::getEventFromCarBook(int element_number){
    if(element_number < _serviceList.length()){ // Test it!
        return _serviceList.at(element_number);
    }
    else{
        return nullptr;
    }
}

void CarBook::modifyEvent(QSharedPointer<CarEvent> carEventToModify,
                          QString name,
                          QString description,
                          EventType service,
                          qint64 mileage,
                          float cost){
    qDebug() << Q_FUNC_INFO << "Modifying Car Event";

    auto elementToModify = CarBook::findEvent(carEventToModify);

    if(!elementToModify.isNull()){
        if(name.length() != 0)
            elementToModify->_name = name;
        if(description.length() != 0)
            elementToModify-> _description = description;
       // if(type != NULL)
            elementToModify-> _service = service;
        if(mileage != NULL)
            elementToModify-> _mileage = mileage;
        if(cost != NULL)
            elementToModify-> _cost = cost;
        this->recalculateCosts();
    }
    else{
        qDebug() << Q_FUNC_INFO << "Element ("<< carEventToModify <<") not found at list.";
    }
}

QSharedPointer<CarEvent> CarBook::getLastEvent(){
    if(this->_serviceList.isEmpty())
        return nullptr;
    return (QSharedPointer<CarEvent>)this->_serviceList.last();
}

float CarBook::getTotalCosts(){
    return _totalCosts;
}

float CarBook::recalculateCosts(){
    float total_cost = 0;
    for(auto event: this->_serviceList){
        total_cost += event.get()->_cost;
    }
    return total_cost;
}
