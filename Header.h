#ifndef HEADER_H
#define HEADER_H

#include <vector>
#include <string>

class Header {
private:
    std::vector<std::string*> attributes;
public:
    Header();

    void addAttribute(std::string *attribute);
    void setAttribute(std::string *attribute, int index);

    /*
    @param index: the index of the attribute whose name is desired
    @return a pointer to the string containing the attribute's name
    
    */
    std::string *getAttribute(int index);

    unsigned int getLength();
};

#endif /* HEADER_H */