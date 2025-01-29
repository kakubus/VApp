#ifndef PROGRAMDATABASE_H
#define PROGRAMDATABASE_H

#include <QObject>

class ProgramDatabase : public QObject
{
    Q_OBJECT
public:
    explicit ProgramDatabase(QObject *parent = nullptr);

signals:
};

#endif // PROGRAMDATABASE_H
