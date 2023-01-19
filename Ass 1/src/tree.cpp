#include<iostream>
#include<bits/stdc++.h>
#include "../inc/tree.h"
#include "../inc/consts.h"

tree::tree(string preced)
{
   // if we want precedence / > * > + > - (BODMAS) give "/*+-" as string.
    root = new node(EMPTY_NODE,types(empty));
    cur = root;

    int n_ops = preced.size();
    for(int i =0;i<n_ops;i++){
        this->precedence[preced[i]] = n_ops - i;
    }

}

tree::~tree()
{
    
}

void tree::connect(node* parent, node* child){
    parent->children.push_back(child);
    child->parent = parent;
}

void tree::change_root(){
    cur = new node(EMPTY_NODE);
    root = cur;
}

void tree::update_root(node* cur){
    root = cur;
}

void tree::add_operator(char operater, types operator_type){

    if(cur->value==EMPTY_NODE){
        if(operator_type == unary){
            cur->value = operator;
            node* newnode = new node();
            newnode->parent = cur;
            cur->next = newnode;
            cur = newnode;
        }
        else{
            cur->value = operator;
            node* newnode = new node();
            newnode->parent = cur;
            cur->right = newnode;
            cur = newnode;
        }
    }
    else{

        while(cur->parent && get_precendence(operator) < get_precendence(cur->value))cur = cur->parent;

        //newnode will be on top
        if(get_precendence(operator) < get_precendence(cur->value)){

            //this will happen only for binary operator
            node* newnode = new node(operator, operator_type);

            //updating root as the newnode
            update_root(newnode);

            cur->parent = newnode;
            newnode->left = cur;
            node* newRightnode = new node();
            newRightnode->parent = newnode;
            newnode->right = newRightnode;
            cur = newRightnode;
            
        }

        else{
            node* newnode = new node(operator, operator_type);
            newnode->left = cur->right;
            cur->right = newnode;
            newnode->parent = cur;
            node* newRightnode = new node();
            newRightnode->parent = newnode;
            newnode->right = newRightnode;
            cur = newRightnode;
        }

    }

}

void tree::add_operand(char operand){
    cur->value = operand;
    cur->type = operands;

    if(!cur->parent){
        node* newnode = new node();
        cur->parent = newnode;
        newnode->left = cur;
    }

    cur = cur->parent;
}

void proc_left_bracket(){
    
}
void proc_right_bracket(){

}
    