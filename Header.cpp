#include "Header.h"

Header::Header(){}

void Header::addAttribute(Parameter *attribute){
    attributes.push_back(attribute);
}
void Header::setAttribute(Parameter *attribute, int index){
    attributes.at(index) = attribute;
}

Parameter *Header::getAttribute(int index){
    return attributes.at(index);
}

unsigned int Header::getLength(){
    return attributes.size();
}