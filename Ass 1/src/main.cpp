#include<stdlib.h>
#include<stdio.h>
#include<iostream>
#include <fstream>
#include "./../inc/tree.h"





std::string get_monitorString(std::string expression){
    std::string monitor_template_start= " \
    #include<iostream> \
    #include <fstream> \
    #include<unordered_map> \
                            \
    //getting index for the propostion  \
    void get_index(std::unordered_map<int, std::string> &umap, std::string line, std::unordered_map<std::string, bool>&propVal){    \
        int i = 0, index = 0;           \
        std::string temp;               \
        line += \",\";                  \
        while(i < line.length()){       \
            if(line[i] == ','){         \
                umap[index++] = temp;   \
                propVal[temp] = false;  \
                temp = \"\";            \
            }                           \
            else{                       \
                temp += line[i];        \
            }                           \
            i++;                        \
        }                               \
    }                                   \
                                        \
    //updating the boolean value of the proposition using map   \
    void update_val(std::unordered_map<int, std::string> &umap, std::string line, std::unordered_map<std::string, bool>&propVal){   \
        int i = 0, index = 0, val;                              \
        line += \",\";                                          \
        while(i < line.length()){                               \
            if(line[i] == \',\'){                               \                          
                index++;                                        \
            }                                                   \
            else{                                               \  
                propVal[umap[index]] = line[i] - '0';           \
            }                                                   \
            i++;                                                \
        }                                                       \
    }                                                           \
                                                                \
                                                                \
    int main(int argc, char* argv[]){                           \
                                                                \
                                                                \
        if(argc != 3){                                          \
            std::cout<<\"the format should be\\n monitor.cpp <input_file> <output_file>\";  \
        }                                                       \
                                                                \
        int output;                                             \
        std::string line, outputString;                         \
        std::ifstream inputFile(argv[1]);                       \
        std::ofstream outputFile(argv[2]);                      \
        std::unordered_map<int, std::string> u_map;             \
        std::unordered_map<std::string, bool>prop_val;          \
                                                                \
        getline(inputFile,line);                                \
        get_index(u_map, line, prop_val);                       \
                                                                \
        while(getline(inputFile, line)){                        \
            update_val(u_map, line, prop_val);                  \
            output =";

    std::string monitor_template_end = "\
        ; // Replace with the expression got from the evaluate parse tree   \
        outputString = output ? \"1\\n\" : \"0\\n\";                        \
        outputFile << outputString;                                         \
    }                                                                       \
    inputFile.close();                                                      \
    outputFile.close();                                                     \
    return 0;                                                               \
    }                                                                       \
    ";

    return monitor_template_start + expression + monitor_template_end;
}


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

void create_monitor_file(std::string monitorString){
    std::ofstream monitorOutput("monitor.cpp");
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

    //Constructing parse tree    
    root->construct_parse_tree(property);
    
    expression = root->evaluate(root->root);
    //std::cout<<expression<<std::endl;


    //getting monitor.cpp template
    monitorString = get_monitorString(expression);

    //writing monitor.cpp file
    create_monitor_file(monitorString);

    return 0;
}