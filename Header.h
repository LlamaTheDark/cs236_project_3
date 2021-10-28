#ifndef HEADER_H
#define HEADER_H

#include "vendor/parser/Parameter.h"

#include <vector>
#include <string>

class Header {
private:
    std::vector<Parameter*> attributes;
public:
    Header();

    void addAttribute(Parameter *attribute);
    void setAttribute(Parameter *attribute, int index);

    /*
    @param index: the index of the attribute whose name is desired
    @return a pointer to the string containing the attribute's name
    
    */
    Parameter *getAttribute(int index);

    unsigned int getLength();
};

#endif /* HEADER_H */