#ifndef TUPLE_H
#define TUPLE_H

#include <vector>
#include <string>

class Tuple {
private:
    std::vector<std::string*> values;
public:
    Tuple();

    unsigned int getLength();

    void addValue(std::string *value);
    std::string *getValue(int index);

    bool operator<(const Tuple &rhs) const {
        return values < rhs.values;
    }
};

#endif /* TUPLE_H */