#include<iostream>
#include <fstream>
#include<unordered_map>

bool evaluate(std::unordered_map<std::string, bool>&prop_val);
//getting index for the propostion
void get_index(std::unordered_map<int, std::string> &umap, std::string line, std::unordered_map<std::string, bool>&propVal){
    int i = 0, index = 0;
    std::string temp;
    line += ",";
    while(i < line.length()){
        if(line[i] == ','){
            umap[index++] = temp;
            propVal[temp] = false;
            temp = "";
        }
        else{
            temp += line[i];
        }
        i++;
    }
}


//updating the boolean value of the proposition using map
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
    std::string line, outputString;
    std::ifstream inputFile(argv[1]);
    std::ofstream outputFile(argv[2]);
    std::unordered_map<int, std::string> u_map;
    std::unordered_map<std::string, bool>prop_val;

    getline(inputFile,line);
    get_index(u_map, line, prop_val);
    
    while(getline(inputFile, line)){
        update_val(u_map, line, prop_val);
        output = evaluate(prop_val); // Replace with the expression got from the evaluate parse tree
        outputString = output ? "1\n" : "0\n";
        outputFile << outputString;
    }
    inputFile.close();
    outputFile.close();
    return 0;
}


bool evaluate(std::unordered_map<std::string, bool>&prop_val){
	return (!(prop_val["R"]))|(!(prop_val["G"]));
}