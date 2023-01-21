#ifndef TREE_H
#define TREE_H

#include<iostream>
#include<bits/stdc++.h>
#include "consts.h"

/* 
Implements a tree. Each node can have many child nodes 
as the operators can be unary, binary or ternary.
*/


struct node
{
    types type;
    char value;
    std::string proposition;
    node *left, *right, *next;
    node* parent;

    node(){
        this->value = EMPTY_NODE;
        this->type = (types)empty;
        this->parent = nullptr;
        this->left = nullptr;
        this->right = nullptr;
        this->next = nullptr;
        this->proposition = "";
    }

    node(char val, types type){
        this->value = val;
        this->parent = nullptr;
        this->type = type;
    }    
};


class tree
{
private:
    node* cur;
    void add_operator(char opt, types opt_type);
    void add_operand(std::string operand);
public:
    node* root;
    tree();
    ~tree();
    void connect(node* parent, node* child);
    void change_root();
    void update_root(node* newnode);
    std::string evaluate(node* current);
    void construct_parse_tree(std::string &property);
};






#endif