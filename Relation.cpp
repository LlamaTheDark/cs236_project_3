#include "Relation.h"

#include <iostream>
#include <sstream>

Relation::Relation() {}
Relation::Relation(std::string name, Header *header): name(std::move(name)), header(header) {}

void Relation::addInstance(Tuple *instance){
    if(instance->getLength() == header->getLength()){
        instances.insert(instance);
    }else{
        // throw error
        std::cerr << "Failed to add instance; Tuple not the same size as header." << std::endl;
    }
}
bool Relation::containstInstance(Tuple *instance){
    for(Tuple *t : instances){
        if(*t == *instance){
            return true;
        }
    }
    return false;
}

Relation *Relation::select(unsigned int index, Parameter *value) const {
    Relation *r = new Relation(name, header);
    for(auto i : instances){
        if(*value == *i->getValue(index)){
            r->addInstance(i);
        }
    }
    return r;
}
Relation *Relation::select(int a, int b) const {
    Relation *r = new Relation(name, header);
    for(auto i : instances){
        if(*i->getValue(a) == *i->getValue(b)){
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
        if(!r->containstInstance(t))
            r->addInstance(t);
        else
            delete t;
    }
    return r;
}
Relation *Relation::rename(std::map<Parameter*, int> &attributes) const {
    Header *h = new Header();
    *h = *header;
    Relation *r = new Relation(name, h);
    
    for(auto it = attributes.begin(); it != attributes.end(); it++){
        h->setAttribute(it->first, it->second);
    }
    for(auto i : instances){
        r->addInstance(i);
    }
    
    return r;
}

std::string Relation::getName() const {
    return name;
}

void Relation::removeDuplicates(Relation &r){
}

std::string Relation::toString() const {
    int length = header->getLength();
    if( 
        isEmpty() // this shouldn't ever be the case
        || length == 0
    ){
        return "";
    }

    std::ostringstream result;
    for (Tuple *t : instances){
        for(int i = 0; i < length-1; i++){
            result << "  " << *(header->getAttribute(i)) << "=" << *t->getValue(i) << ", ";
        }
        result << "  " << *(header->getAttribute(length-1)) << "=" << *t->getValue(length-1);
        result << std::endl;
    }
    return result.str();
}

std::ostream &operator<<(std::ostream &out, const Relation &r) {
    out << r.toString();
    return out;
}