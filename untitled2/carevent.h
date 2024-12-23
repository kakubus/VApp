#ifndef CAREVENT_H
#define CAREVENT_H

#include <QObject>
#include <QDateTime>

enum class EventType{
    FUEL,
    SERVICE,
    YEARLY_INSPECTION
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
    const QDateTime _timestamp;
    QString _description;
    EventType _service;
    qint64 _mileage;
    float _cost;

    static unsigned int NUMBER_OF_EVENTS;
};

#endif // CAREVENT_H
