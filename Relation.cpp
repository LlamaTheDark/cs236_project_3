#include "Relation.h"

#include <iostream>
#include <sstream>

Relation::Relation() {}
Relation::Relation(std::string *name, Header *header): name(name), header(header) {}

void Relation::addInstance(Tuple *instance){
    if(instance->getLength() == header->getLength()){
        instances.insert(instance);
    }else{
        // throw error
        throw 1;
    }
}

Relation *Relation::select(unsigned int index, std::string *value) const {
    Relation *r = new Relation(name, header);
    for(auto i : instances){
        if(value->compare( *(i->getValue(index)) ) == 0){
            r->addInstance(i);
        }
    }
    return r;
}
Relation *Relation::select(int colA, int colB) const {
    Relation *r = new Relation(name, header);
    for(auto i : instances){
        if(i->getValue(colA)->compare( *(i->getValue(colB)) ) == 0){
            r->addInstance(i);
        }
    }
    return r;
}

Relation *Relation::project(int *indices, unsigned int count) const {
    Header *h = new Header();
    Relation *r = new Relation(name, h);
    for(unsigned int i = 0; i < count; i++){
        h->addAttribute(header->getAttribute(*(indices+i)));
    }
    for(auto i : instances){
        Tuple *t = new Tuple();
        for(unsigned int j = 0; j < count; j++){
            t->addValue(i->getValue( *(indices+j) ));
        }
        r->addInstance(t);
    }
    return r;
}
Relation *Relation::rename(std::map<Parameter*, int> &attributes) const {
    Header *h = new Header();
    *h = *header;
    Relation *r = new Relation(name, h);
    
    for(auto it = attributes.begin(); it != attributes.end(); it++){
        h->setAttribute(&it->first->toString(), it->second);
    }
    for(auto i : instances){
        r->addInstance(i);
    }
    return r;
}

std::string *Relation::getName() const {
    return name;
}

std::string Relation::toString() const {
    std::ostringstream result;
    for (Tuple *t : instances){
        for(unsigned int i = 0; i < header->getLength(); i++){
            result << *(header->getAttribute(i)) << "=" << *t->getValue(i) << ", ";
        }
        result << std::endl;
    }
    return result.str();
}

std::ostream &operator<<(std::ostream &out, const Relation &r) {
    out << r.toString();
    return out;
}