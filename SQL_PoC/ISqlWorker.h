#ifndef ISQLWORKER_H
#define ISQLWORKER_H
#include <QObject>

class ISqlWorker : public QObject
{
    Q_OBJECT
public:
    ISqlWorker();
    virtual ~ISqlWorker();

    virtual void saveElement() = 0;
    virtual void getElement() = 0;
    virtual void findElement() = 0;
};

#endif // ISQLWORKER_H
