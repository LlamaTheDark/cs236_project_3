#include "Header.h"

Header::Header(){}

void Header::addAttribute(std::string *attribute){
    attributes.push_back(attribute);
}
std::string *Header::getAttributeName(int index){
    return attributes.at(index);
}

unsigned int Header::getAttributesLength(){
    return attributes.size();
}