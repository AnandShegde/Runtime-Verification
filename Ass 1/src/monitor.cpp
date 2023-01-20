#include<iostream>
#include <fstream>

int main(int argc, char* argv[]){


    if(argc != 3){
        std::cout<<"the format should be\n monitor.cpp <input_file> <output_file>";
    }

    std::string line;
    std::ifstream inputFile(argv[1]);
    getline(inputFile,line);

    while(getline(inputFile, line)){
       
    }


    
    
    


}