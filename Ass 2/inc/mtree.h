#include"consts.h"
#include<bits/stdc++.h>

struct mnode
{
    types type;
    char value;
    std::string proposition;
    mnode *left, *right, *next;
    mnode* parent;

    int t1, t2;
    std::list<bool> l1, l2;

    mnode(){
        this->value = EMPTY_NODE;
        this->type = (types)empty;
        this->parent = nullptr;
        this->left = nullptr;
        this->right = nullptr;
        this->next = nullptr;
        this->t1 = -1; //For operators store [t1, t2]
        this->t2 = -1;
        

        //For operators store [t1, t2]
        this->proposition = "";
    }

    mnode(char val, types type){
        this->value = val;
        this->parent = nullptr;
        this->type = type;
    }    
};


class mtree
{
        
    public:
        mnode* root;
        mtree();
        ~mtree();

        mnode* deserialize(std::string &expression, int start, int end);
        std::vector<int> get_times(std::string &expression, int start, int end);
        void print(mnode* root);
        int evaluate(std::unordered_map<std::string, bool> ,mnode* node);
        int get_value(mnode* node);

        int process_and(mnode* node);
        int process_or(mnode* node);
        int process_implies(mnode* node);
        int process_not(mnode* node);

        int process_until(mnode* node);
        int process_next(mnode* node);
        int process_globally(mnode* node);
        int process_finally(mnode* node);


};