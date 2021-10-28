#include "Database.h"

Database::Database(){}

void Database::addRelation(std::string &name, Relation *relation){
    // database.insert(
    //     std::pair<std::string*, Relation*>(
    //         relation->getName(),
    //         relation
    //     )
    // );

    database[name] = relation;
}

Relation *Database::getRelation(std::string &name) {
    for(auto it : database){
        if(it.first == name){
            return it.second;
        }
    }
    std::cerr << "ERROR: Attempted to get relation with name \'" << name << "\' when none exists." << std::endl;
    return NULL;
}