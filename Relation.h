#ifndef RELATION_H
#define RELATION_H

#include "Header.h"
#include "Tuple.h"

#include <string>
#include <set>

class Relation {
private:
    std::string *name;
    Header *header;
    std::set<Tuple*> instances;
public:
    Relation();
    Relation(std::string *name, Header *header);

    /*
    Adds an instance to the relation (i.e. adds another row to the table).
    @param instance: the tuple to be added
    */
    void addInstance(Tuple *instance);

    /*
    Selects rows that contain a specific value for a given column
    @param index: relation column index
    @param value: value to select
    @return A new relation object with only the tuples selected.
    */
    Relation *select(unsigned int index, std::string *value) const;
    /*
    This function selects rows for which values in columns at indices colA and colB are the same.
    @param colA: the first column whose values are to be compared with the second column
    @param colB: the second column
    @return A new relation object which only contains the selected tuples
    */
    Relation *select(int colA, int colB) const;
    /*
    @param indices: A pointer to a list of the indices of the columns we want to keep.
    @param count: the number of indices in the list
    @return A new relation with all but the specified columns removed.
    */
    Relation *project(int *indices, unsigned int count) const;
    /*
    @param attributes: a pointer to a list of strings to define a new header
    @param count: the number of attributes in the list
    @return A new relation with the header changed to the new list of attribtues
    */
    Relation *rename(Header *h) const;

    std::string *getName() const;

    std::string toString() const;

    friend std::ostream &operator<<(std::ostream &out, const Relation &r);
};

#endif /* RELATION_H */