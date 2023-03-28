#include<iostream>
#include<bits/stdc++.h>
#include "../inc/tree.h"

tree::tree()
{
   // if we want precedence / > * > + > - (BODMAS) give "/*+-" as string.
    root = new node(EMPTY_NODE,(types)empty);
    cur = root;

}

tree::~tree()
{
    
}

void tree::connect(node* parent, node* child){

}

void tree::change_root(){
    cur = new node();
    root = cur;
}

void tree::update_root(node* cur){
    *root = *cur;
}

void tree::add_operator(char opt, types opt_type, std::string number){

    if(cur->value==EMPTY_NODE){ // No operator seen yet, but left child is operand.
        if(opt_type == (types)unary){
            cur->value = opt;
            cur->type = (types)unary;
            cur->proposition = number;
            node* newnode = new node();
            newnode->parent = cur;
            cur->next = newnode;
            cur = newnode;
        }
        else{
            cur->value = opt;
            cur->type = (types)binary;
            cur->proposition = number;
            node* newnode = new node();
            newnode->parent = cur;
            cur->right = newnode;
            cur = newnode;
        }
    }
    else{

        while(cur->parent && get_precendence(opt) < get_precendence(cur->value))cur = cur->parent;

        //newnode will be on top
        if(get_precendence(opt) < get_precendence(cur->value)){

            //this will happen only for binary operator
            node* newnode = new node(opt, opt_type);
            newnode->proposition = number;
            //updating root as the newnode
            root = newnode;

            cur->parent = newnode;
            newnode->left = cur;
            node* newRightnode = new node();
            newRightnode->parent = newnode;
            newnode->right = newRightnode;
            cur = newRightnode;
            
        }

        else{
            node* newnode = new node(opt, opt_type);
            newnode->proposition = number;
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

void tree::add_operand(std::string operand){
    cur->value = ' ';
    cur->type = (types)operands;
    cur->proposition = operand;

    if(!cur->parent){
        node* newnode = new node();
        cur->parent = newnode;
        newnode->left = cur;
        cur = cur->parent;

        //updating root
        root = cur;
    }
    else{
        cur = cur->parent;
    }

   
    
}

void tree::remove_H_E(std::string &property){
    std::string temp = "";

    for(int i=0;i<property.size();i++){
        if(property[i] == ' ') continue;

        if(property[i]=='E'||property[i]=='H'){
            //changing the operator Et -> F[0,t]
            temp += property[i] == 'H' ? "G[0," : "F[0,";
            std::string number = "";
            
            i++;
            while(isdigit(property[i])|| property[i]==' '){
                if(property[i] == ' ') {
                    i++;
                    continue;
                }
                temp += property[i];
                i++;
            } 
            i--; 
            temp+= "]";
        }
        else{
            temp += property[i];
        }
    }
    property = temp;
}

void tree::construct_parse_tree(std::string &property){
    int i = 0;
    while (i < property.length()) {

        if(get_type(property[i]) == (types)operands){
            std::string value = "";
            while(i < property.length() &&  get_type(property[i]) == (types)operands)value += property[i++];
            add_operand(value);
        }
        else if(get_type(property[i]) == (types)unary ){
            std::string number = get_time(property,i);
            // std::cout<<"\n"<<number<<"\n";

            add_operator(property[i], (types)unary, number);
            i += number.size()+1;
        }
        else if(get_type(property[i]) == (types)binary ){
            std::string number = get_time(property,i);
            add_operator(property[i], (types)binary, number);
            i += number.size()+1;
        }
        else{
            std::cout<<"-----------Invalid character----------\n";
            exit(1);
        }
    }

    // if only one operand is there without any operator
    // so root will be empty
    if(root->value==EMPTY_NODE){
        root = root->left;
    }

}

std::string tree::serialize(node* current){
   
    if(!current) return "";

    std::string left, right,expresstion;
    if(current->type == (types)operands){
        return current->proposition;
    }
    
    if((types)current->type == (types) unary){
        left = serialize(current->next);
        return get_expression(current->value, current->proposition,  left, "");
    }

    if(current->type == (types) binary ){
        left = serialize(current->left);
        right = serialize(current->right);
        return get_expression(current->value, current->proposition, left, right);
    }

    return "";
}