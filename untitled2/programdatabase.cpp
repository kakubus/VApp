#include "programdatabase.h"
#include <QVector>

TableHeaderDefinition VehicleTable = {"ID", "mark", "model", "VIN", "year", "CarBookID" };
TableHeaderDefinition CarBookTable = {"ID", "totalCosts", "VehicleID"};
TableHeaderDefinition CarEventTable = {"ID", "name", "timestamp", "description", "service", "mileage", "cost", "CarBookID"};



ProgramDatabase::ProgramDatabase(QObject *parent)
    : QObject{parent}
{}
