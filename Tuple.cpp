#include "Tuple.h"

Tuple::Tuple(){}

void Tuple::addValue(Parameter *value){
    values.push_back(value);
}
Parameter *Tuple::getValue(int index) const {
    return values.at(index);
}

unsigned int Tuple::getLength(){
    return this->values.size();
}

