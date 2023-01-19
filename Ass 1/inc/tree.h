#ifndef TREE_H
#define TREE_H

#include<iostream>
#include<bits/stdc++.h>

/* 
Implements a tree. Each node can have many child nodes 
as the operators can be unary, binary or ternary.
*/

using namespace std;

struct node
{
    char value;
    vector<node*>  children;
    node* parent;

    node(){
        this->parent = nullptr;
    }

    node(char val){
        this->value = val;
        this->parent = nullptr;
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
};






#endif