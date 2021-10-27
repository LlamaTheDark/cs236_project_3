#include "Database.h"

Database::Database(){}

void Database::addRelation(Relation *relation){
    // database.insert(
    //     std::pair<std::string*, Relation*>(
    //         relation->getName(),
    //         relation
    //     )
    // );
    database[relation->getName()] = relation;
}

Relation *Database::getRelation(std::string *name) {
    return database[name];
}