#include<iostream>
#include <fstream>
#include<unordered_map>

void get_index(std::unordered_map<int, std::string> &umap, std::string line, std::unordered_map<std::string, bool>&propVal){
    int i = 0, index = 0;
    std::string temp;
    line += ",";
    while(i < line.length()){
        if(line[i] == ','){
            umap[index] = temp;
            propVal[temp] = false;
            index++;
            temp = "";
        }
        else{
            temp += line[i];
        }
        i++;
    }
}

void update_val(std::unordered_map<int, std::string> &umap, std::string line, std::unordered_map<std::string, bool>&propVal){
    int i = 0, index = 0, val;
    line += ",";
    while(i < line.length()){
        if(line[i] == ','){
            index++;
        }
        else{
            propVal[umap[index]] = line[i] - '0';
        }
        i++;
    }
}

int main(int argc, char* argv[]){


    if(argc != 3){
        std::cout<<"the format should be\n monitor.cpp <input_file> <output_file>";
    }

    int output;
    std::string line;
    std::ifstream inputFile(argv[1]);
    std::unordered_map<int, std::string> u_map;
    std::unordered_map<std::string, bool>prop_val;

    getline(inputFile,line);
    get_index(u_map, line, prop_val);
    
    while(getline(inputFile, line)){
        update_val(u_map, line, prop_val);
        std::cout<<output<<std::endl;
    }
    inputFile.close();
    
    return 0;

}