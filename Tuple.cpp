#include "Tuple.h"

Tuple::Tuple(){}

void Tuple::addValue(std::string *value){
    values.push_back(value);
}
std::string *Tuple::getValue(int index){
    return values.at(index);
}

unsigned int Tuple::getLength(){
    return this->values.size();
}

