#ifndef TUPLE_H
#define TUPLE_H

#include "vendor/parser/Parameter.h"

#include <vector>
#include <string>

class Tuple {
private:
    std::vector<Parameter*> values;
public:
    Tuple();

    unsigned int getLength();

    void addValue(Parameter *value);
    Parameter *getValue(int index) const;

    bool operator<(const Tuple &rhs) const {
        return values < rhs.values;
    }
    bool operator==(const Tuple &rhs) const {
        for(unsigned int i = 0; i < values.size(); i++){
            if(*values.at(i) != *rhs.getValue(i)){
                return false;
            }
        }
        return true;
    }
};

#endif /* TUPLE_H */