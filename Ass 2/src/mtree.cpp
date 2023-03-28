#include<iostream>
#include<bits/stdc++.h>
#include "../inc/mtree.h"


mtree::mtree()
{
    root = NULL;
}

mtree::~mtree()
{
    
}

// Size of the returned vector is 3, {t1, t2, start of next '(' bracket of child} 
// takes the expression starting from the opening square bracket
std::vector<int> mtree::get_times(std::string &expression, int start, int end){
    int cur = start;
    
    if(expression[cur] != '[') return {-1, -1, start}; // error (should not happen
    
    std::vector<int> times(3,0);

    while(expression[cur]!=',') cur++;

    times[0] = std::stoi(expression.substr(start+1, cur-start-1)); // skipping square bracket
    
    start = cur;
    while (expression[cur]!=']') cur++;
    times[1] = std::stoi(expression.substr(start+1, cur-start-1)); // skipping comma
    times[2] = cur + 1;

    return times;


}

void mtree::print(mnode* root){
    if(root == NULL) return;
    std::cout<<root->value<<" ";
    std::cout<<root->t1<<" ";
    std::cout<<root->t2<<" ";
    std::cout<<root->proposition<<"\n\n";
    print(root->next);
    print(root->left);
    print(root->right);
}

mnode* mtree::deserialize(std::string &expression, int start, int end){

    if(start > end) return NULL;
    mnode* node;
    //Binary case 
    if(expression[start] == '('){
        int bracket_diff = 1;
        int cur = start+1;
        
        while(bracket_diff != 0){
            if(expression[cur] == '('){
                bracket_diff++;
            } 
            else if(expression[cur] == ')'){
                bracket_diff--;
            } 
            
            cur++;
        }
        
        // After this current points to Binary operator
        node = new mnode(expression[cur], (types)binary);
        auto times = get_times(expression, cur+1, end);

        node->t1 = times[0];
        node->t2 = times[1];
        
        node->left = deserialize(expression, start+1, cur -2); // -2 and +1 to remove the bracket
        node->right = deserialize(expression, times[2] + 1, end-1);
    }
    //Unary case
    else if(get_type(expression[start]) == (types)unary){
        node = new mnode(expression[start], (types)unary);
        
        auto times = get_times(expression, start+1, end);
        
        node->t1 = times[0];
        node->t2 = times[1];

        node->next = deserialize(expression, times[2] + 1, end - 1);
    

    }
    //atomic proposition
    else{
        node = new mnode();
        std::string value = expression.substr(start, end-start+1);
        node->proposition = value;
    }
    return node;
}

// 0: false 1:true -1: don't know.
int mtree::evaluate(std::unordered_map<std::string, bool> prop_val, mnode* node){
    
    //propostion
    if(node->type == (types)empty){
        return prop_val[node->proposition];
    }

    //binary
    if(node->type == (types)binary){
        int left = evaluate(prop_val, node->left);
        int right = evaluate(prop_val, node->right);
        
    }
    //unary
}
    