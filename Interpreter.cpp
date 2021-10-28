#include "Interpreter.h"
#include "Tuple.h"
#include "vendor/utils/FileHelper.h"
#include "vendor/parser/Parameter.h"

#include <vector>

Interpreter::Interpreter(DatalogProgram *dp): dp(dp){

    db = Database();

    // evaluate schemes
    for(auto scheme : *(dp->getSchemes())){
        Header *header = new Header();
        for(auto parameter : *(scheme->getParameters())){
            header->addAttribute(parameter->toString());
        }
        db.addRelation(new Relation(scheme->getId(), header));
    }
    // evalutate facts
    for(auto fact : *(dp->getFacts())){
        Tuple *instance = new Tuple();
        for(auto parameter : *(fact->getParameters())){
            instance->addValue(parameter->toString());
        }
        db.getRelation(fact->getId())->addInstance(instance);
    }
}

void Interpreter::evaluateQueries(){
    // for each query ‘q’
    for(auto query : *(dp->getQueries())){
        Relation *r = evaluatePredicate(query);
        if(!FileHelper::write("out/tests/output.txt", r->toString()))
            std::cout << "Failed to write file" << std::endl;
        // std::cout << *r << std::endl;
    }
}

Relation *Interpreter::evaluatePredicate(Predicate *query){
    /*
    nonConsts is a map that links each non-constant (variable) parameter we've seen to the index
    that it first appeared.
    */
    std::map<Parameter*, int> variables;

    //     get the relation ‘r’ with the same name as the query ‘q’
    Relation *result = new Relation();
    *result = *db.getRelation(query->getId());

    Relation *tmp;

    std::vector<Parameter*> queryParameters = *(query->getParameters());

    for(unsigned int i = 0; i < queryParameters.size(); i++){
    //     select for each constant in the query ‘q’
        if(queryParameters.at(i)->isConstant()){
            tmp = result->select(i, queryParameters.at(i)->toString());
            // selects all instances (rows) that have the value queryParameters[i] in column i
            *result = *tmp;
            delete tmp;
        }else{
    //     select for each pair of matching variables in ‘q’
            // auto it = variables.find(queryParameters.at(i)->toString());
            auto it = variables.begin();
            while(it != variables.end() 
                    && it->first->toString()->compare(*queryParameters.at(i)->toString()) != 0) { it++; }

            if( it != variables.end() ){
                tmp = result->select(i, it->second);
                *result = *tmp;
                delete tmp;
            }
            // so we have the positions of each variable. Note: this will only store
            // the most recent variable index
            variables[queryParameters.at(i)] = i;
        }
    }
    //     project using the positions of the variables in ‘q’
    // build indices array
    unsigned int count = 0;
    int *indices = new int(variables.size());

    //     rename to match the names of variables in ‘q’
    for(auto var : variables){
        *(indices+count) = var.second;
        count++;
    }

    // rename
    tmp = result->rename(variables);
    *result = *tmp;
    delete tmp;

    // project
    tmp = result->project(indices, count);
    *result = *tmp;
    delete tmp;



    /*
    TODO:
    - be able to pass an array of the variables
    - determine whether a parameter is a variable or string (when we're creating it in the parser)
    */


    //     print the resulting relation
    
    return result;
}