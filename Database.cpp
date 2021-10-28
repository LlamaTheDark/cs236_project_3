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
    for(auto it : database){
        if(it.first->compare(*name) == 0){
            return it.second;
        }
    }
    // else throw a big doodoo error;
    return new Relation();
    // Relation *r = database[name];
    // return r;
    // return database[name];
}

// YOU CAN'T COMPARE STRING POINTERS YOU DINGUS
// YOU NEED SOME MAJOR REFACTORING - USE REFERENCES TO STRINGS INSTEAD OF POINTERS