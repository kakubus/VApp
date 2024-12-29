#ifndef CAREVENT_H
#define CAREVENT_H

#include <QObject>
#include <QDateTime>
#include <algorithm>

#define QT_NO_DEBUG_OUTPUT

enum class EventType{
    FUEL,
    SERVICE,
    YEARLY_INSPECTION,
    BODY_REPAIR,
    WASH_CARE,
    OTHERS
};

class CarEvent : public QObject
{
    Q_OBJECT
public:
    CarEvent();
    CarEvent(QString name, QString description, EventType type, qint64 mileage, float cost);
    ~CarEvent();

    void modify(QString name, QString description, EventType type, qint64 mileage, float cost);
    QSharedPointer<CarEvent> get();

    std::tuple<QString, QString, EventType, qint64, float> carEventTuple;

    QString _name;
    QDateTime _timestamp;
    QString _description;
    EventType _service;
    qint64 _mileage;
    float _cost;

    static unsigned int NUMBER_OF_EVENTS;
};

#endif // CAREVENT_H
