#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

// #define MEMORY_TRACKING
#ifdef MEMORY_TRACKING

size_t total_mem_allocated = 0;

void *operator new(size_t size){
    total_mem_allocated += size;
    std::cout << "New memory allocated of size: " << size << " bytes." << std::endl;
    std::cout << "\tTotal memory currently in use: " << total_mem_allocated << " bytes." << std::endl;
    return malloc(size);
}

void operator delete(void *ptr, size_t size){
    total_mem_allocated -= size;
    std::cout << "Freeing pointer @" << ptr << " of size: " << size << " bytes." << std::endl;
    std::cout << "\tTotal memory currently in use: " << total_mem_allocated << " bytes." << std::endl;
    free(ptr);
}
#endif

#include "Interpreter.h"
#include "vendor/lexer/Lexer.h"
#include "vendor/parser/DatalogProgram.h"

int main(int argc, char **argv){    
    if(argc != 2){
        std::cerr << "Incorrect number of arguments provided (expected 1: filename)" << std::endl;
    }

    std::string fileInput;
    {
        std::string filename(*(argv+1));
        std::ifstream in(filename);
        std::ostringstream result;
        std::string buffer;
        if(in.is_open()){
            while(std::getline(in, buffer, '\n')){
                result << buffer << std::endl;
            }
            in.close();
            fileInput = result.str();
        }else{
            std::cerr << "Could not open file: " << filename << std::endl;
        }
    }

    Lexer *lexer = new Lexer();
    lexer->Run(fileInput);

    DatalogProgram *datalogProgram = new DatalogProgram();
    datalogProgram->start(lexer->getTokens(), true);

    Interpreter *interpreter = new Interpreter(datalogProgram);
    interpreter->evaluateQueries();


    delete lexer;
    delete datalogProgram;
    delete interpreter;

    return 0;
}


/*

TODO:
 - maps won't sort strings correctly if you store them as pointers, so you'll have to fix that.
 - just too many pointers in general. You need some major refactoring of your pointer business you went way overboard.
 - OKAY SO WHAT YOU SHOULD HAVE DONE IS USE PARAMETERS INSTEAD OF STRINGS EVERYWHERE THAT'S LITERALLY WHY THE PARAMETER CLASS EXISTS YOU RETARD
*/