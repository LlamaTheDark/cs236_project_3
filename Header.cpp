#include "Header.h"

Header::Header(){}

void Header::addAttribute(std::string *attribute){
    attributes.push_back(attribute);
}
void Header::setAttribute(std::string *attribute, int index){
    attributes.at(index) = attribute;
}

std::string *Header::getAttribute(int index){
    return attributes.at(index);
}

unsigned int Header::getLength(){
    return attributes.size();
}