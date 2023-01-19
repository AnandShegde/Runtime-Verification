#include<iostream>
#include<bits/stdc++.h>
#include "../inc/tree.h"
#include "../inc/consts.h"

tree::tree(string preced)
{
   // if we want precedence / > * > + > - (BODMAS) give "/*+-" as string.
    root = new node(EMPTY_NODE);
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

void tree::add_operator(char operater){

    if(cur->value==EMPTY_NODE){
        cur->value = operater;
        cur = cur->parent;
        if(!cur){
            change_root();
        }
    }
    else{

        if(precedence[operater] > precedence[cur->value]){
            // make the new operator child of current node
            
        }
        else{
            // make the new operator, child of current node.
            // current node will usually have a child.
            // we have to make it child of the new operator.
            // and go to the right child of our new operator.
            // look at example here - https://www.notion.so/Example-8434c5a6a1c14a3cbb34cac2d1d527b9
            
            node* newnode = new node(operater);
            newnode->children = cur->children; // copy children of current node
            vector<node*> empty_vec;
            cur->children = empty_vec; // remove children of current node
            cur->children.push_back(newnode);


        }


    }

}

void tree::add_operand(char operand){

}

void proc_left_bracket();
void proc_right_bracket();
    