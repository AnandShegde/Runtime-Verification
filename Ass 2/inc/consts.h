#include<string>
#ifndef CONSTS_HPP
#define CONSTS_HPP
const char EMPTY_NODE = '~';
enum types {unary, binary, operands, empty};

types get_type(char ch);

int get_precendence(char ch);

std::string get_expression(char ch, std::string time, std::string left, std::string right);

std::string get_time(std::string property, int i);

#endif