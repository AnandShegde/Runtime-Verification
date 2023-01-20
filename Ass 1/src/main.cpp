#include<stdlib.h>
#include<stdio.h>
#include<iostream>
#include <fstream>
#include "./../inc/tree.h"

using namespace std;

string getProperty(string fileName){

    string property;
    ifstream propertyFile(fileName);
    if(!(getline(propertyFile, property))){
        cout<<"No property found\n";
        propertyFile.close();
        return "";
    }
    propertyFile.close();
    return property;
}



int main(int argc, char *argv[]){

    if(argc < 2){
        std::cout<<"Pass required arguments\n";
        return -1;
    }
    
    string property;

    

    property = getProperty(argv[1]);
     cout<<property<<endl;

    tree tre


    return 0;
}