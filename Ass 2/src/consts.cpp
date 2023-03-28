#include "../inc/consts.h"
#include<stdlib.h>
#include<bits/stdc++.h>
#include<string>

types get_type(char ch){
    switch (ch)
    {
        case '^':
        case 'v':
        case '>':
            return (types)binary;
        case '!':
            return (types)unary;
            
        case 'U':
            return (types)binary;
        case 'X':
            return (types)unary;

        case 'G':
            return (types)unary;
        case 'F':
            return (types)unary;

        case '~':
            return (types)empty;
        default:
            return (types)operands;
    }

    return (types)empty;
}

int get_precendence(char ch){

    std::string prec = "!XFGU^v>";
    for(int i=0;i<prec.length();i++){
        if(prec[i]==ch) return 100 - i;
    }

    // switch (ch)
    // {
    //     case '!': return 100;
    //     case 'X': return 99;
    //     case '^': return 98;
    //     case 'F': return 92;
    //     case 'v': return 96;
    //     case '>': return 95;
    //     case 'G': return 94;
    //     case 'H': return 93;
        
    //     case 'U': return 91;
    //     case ''
    // }

    return -1;
}

std::string get_expression(char ch, std::string time, std::string left, std::string right){

    if(get_type(ch) == (types)unary){
        return ch + time + "(" + left + ")";
    }
    else{
        return "(" + left + ")" + ch  + time + "(" + right + ")";
    }
}

std::string get_time(std::string property, int i){

    if(property[i] == 'G' || property[i] == 'F' || property[i] == 'U'){
        std::string ret_time;
        i++;
        do{
            ret_time += property[i];
        }while(property[i++] != ']');

        return ret_time;
    } 
    return "";
}
