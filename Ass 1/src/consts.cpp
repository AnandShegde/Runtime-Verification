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

        case '~':
            return (types)empty;

        default:
            return (types)operands;
    }

    return (types)empty;
}

int get_precendence(char ch){
    switch (ch)
    {
        case '!': return 100;
        case '^': return 99;
        case 'v': return 98;
        case '>': return 97;
    }

    return -1;
}

std::string get_expression(char ch, std::string left, std::string right){
    switch (ch)
    {
    
    //NOT
    case '!':
        return "!("+ left + ")"; 
    case '^':
        return "("+left+")&("+right+")";
    case 'v':
        return "(" + left + ")|(" + right +")";
    case '>':
        return "("+ left+ ")&(!("+right+"))";
    default:
        std::string ret;
        ret += ch;
        return ret;
    }
}