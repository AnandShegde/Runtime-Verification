#ifndef TREE_H
#define TREE_H

#include<iostream>
#include<bits/stdc++.h>

/* 
Implements a tree. Each node can have many child nodes 
as the operators can be unary, binary or ternary.
*/

using namespace std;

enum types {unary, binary, operands, empty};

struct node
{
    types type;
    char value;
    node *left, *right, *next;
    node* parent;

    node(){
        this->type = empty;
        this->parent = nullptr;
        this->left = nullptr;
        this->right = nullptr;
        this->next = nullptr;
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
    unordered_map<char, int> precedence;
public:
    node* root;
    tree(string preced);
    ~tree();
    void connect(node* parent, node* child);
    void add_operator(char operater);
    void add_operand(char operand);
    void proc_left_bracket();
    void proc_right_bracket();
    void change_root();
    void update_root(node* newnode);
};






#endif