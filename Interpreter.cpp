#include "Interpreter.h"
#include "Tuple.h"
#include "vendor/utils/FileHelper.h"
#include "vendor/parser/Parameter.h"

#include <vector>
#include <sstream>

Interpreter::Interpreter(DatalogProgram *dp): dp(dp){
    db = Database();

    // evaluate schemes
    for(auto scheme : *(dp->getSchemes())){
        Header *header = new Header();

        for(auto parameter : *(scheme->getParameters())){
            header->addAttribute(parameter);
        }

        std::string *name = scheme->getId();
        db.addRelation(*name, new Relation(*name, header));
    }
    // evalutate facts
    for(auto fact : *(dp->getFacts())){
        Tuple *instance = new Tuple();

        for(auto parameter : *(fact->getParameters())){
            instance->addValue(parameter);
        }

        db.getRelation( *fact->getId() )->addInstance(instance);
    }

}

void Interpreter::evaluateQueries(){
    std::ostringstream oss;
    // for each query ‘q’
    for(auto query : *(dp->getQueries())){
        Relation *r = evaluatePredicate(query);
        oss << *query << "?";
        if(r->isEmpty()){
            oss << " No";
        }else{
            oss << " Yes(" << r->getInstanceCount() << ")" << std::endl;
            oss << *r;
        }
    }
    oss << std::endl;
    if(!FileHelper::write("out/tests/output.txt", oss.str()))
        std::cout << "Failed to write file" << std::endl;

}

Relation *Interpreter::evaluatePredicate(Predicate *query){
    /*
    nonConsts is a map that links each non-constant (variable) parameter we've seen to the index
    that it first appeared.
    */
    std::map<Parameter*, int> variables;

    //     get the relation ‘r’ with the same name as the query ‘q’
    Relation *result = new Relation();
    *result = *db.getRelation( *query->getId() );
    Relation *tmp;

    std::vector<Parameter*> queryParameters = *(query->getParameters());

    for(unsigned int i = 0; i < queryParameters.size(); i++){
    //     select for each constant in the query ‘q’
        if(queryParameters.at(i)->isConstant()){
            // selects all instances (rows) that have the value queryParameters[i] in column i
            tmp = result->select(i, queryParameters.at(i));
            *result = *tmp;
            delete tmp;
        }else{
    //     select for each pair of matching variables in ‘q’
            // auto it = variables.find(queryParameters.at(i)->toString());

            // search the map for anything with the same name
            // if we have the same name, we want to select for those two columns
            // if we can't find the same name, then we want to add the variable
            //    to the map.

            auto it = variables.begin();
            while(
                it != variables.end()
                && *it->first != *queryParameters.at(i)
            ){
                it++;
            }
            // at this point, i should point to either the end of the map or the variable with the same name
            // if it got to the end of the map, we want to select
            // otherwise, we should add the variable to the map.

            if(it == variables.end()){
                variables[queryParameters.at(i)] = i;
            }else{
                tmp = result->select(i, it->second);
                *result = *tmp;
                delete tmp;
            }
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