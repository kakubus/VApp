#ifndef SERIALIZATIONSQL_H
#define SERIALIZATIONSQL_H

#include "sqlworker.h"

class SerializationSql : public SQLWorker
{
    Q_OBJECT
public:
    explicit SerializationSql(QObject *parent = nullptr);
// Check if possible is decapsulate object (as vehicle, event, etc) into sql table/rows
    virtual void saveElement() = 0;
    virtual void getElement() = 0;
    virtual void findElement() = 0;
};

#endif // SERIALIZATIONSQL_H
