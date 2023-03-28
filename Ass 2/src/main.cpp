#include<stdlib.h>
#include<stdio.h>
#include<iostream>
#include <fstream>
#include "./../inc/tree.h"




std::string get_property(std::string fileName){

    std::string property;
    std::ifstream propertyFile(fileName);
    if(!(getline(propertyFile, property))){
        std::cout<<"No property found\n";
        propertyFile.close();
        return "";
    }
    propertyFile.close();
    return property;
}

void create_monitor_file(std::string expression){
    std::ofstream monitorOutput("src/monitor.cpp");
    std::ifstream monitorTempate("src/monitor_template.cpp");
    std::string line, monitorString;
    while(getline(monitorTempate,line)){
        monitorString += line + "\n";
    }
    monitorTempate.close();
    monitorString += "std::string get_expression(){\n\treturn \"" + expression + "\";\n}";
    monitorOutput << monitorString;
    monitorOutput.close();
    
}



int main(int argc, char *argv[]){

    if(argc < 2){
        std::cout<<"Pass required arguments\n";
        return -1;
    }
    
    std::string property, expression, monitorString;
    tree *root = new tree();
    
    //reading property from file
    property = get_property(argv[1]);
    //std::cout<<property<<std::endl;

    //Preprocessing the input
    root->remove_H_E(property);

    //Constructing parse tree    
    root->construct_parse_tree(property);
    
    
    expression = root->serialize(root->root);
    // std::cout<<expression<<std::endl;


    //writing monitor.cpp file
    create_monitor_file(expression);

    return 0;
}