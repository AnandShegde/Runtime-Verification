#include <iostream>
#include <bits/stdc++.h>
#include "../inc/mtree.h"

mtree::mtree()
{
    root = NULL;
}

mtree::~mtree()
{
}

// Changing time convention (to 0 index) here [1, 5] ---> [0, 4]
// Size of the returned vector is 3, {t1, t2, start of next '(' bracket of child}
// takes the expression starting from the opening square bracket
std::vector<int> mtree::get_times(std::string &expression, int start, int end)
{
    int cur = start;

    if (expression[cur] != '[')
        return {-1, -1, start}; // error (should not happen

    std::vector<int> times(3, 0);

    while (expression[cur] != ',')
        cur++;

    times[0] = std::stoi(expression.substr(start + 1, cur - start - 1)) -1 ; // skipping square bracket

    start = cur;
    while (expression[cur] != ']')
        cur++;
    times[1] = std::stoi(expression.substr(start + 1, cur - start - 1)) -1; // skipping comma
    times[2] = cur + 1;

    return times;
}

void mtree::print(mnode *root)
{
    if (root == NULL)
        return;
    std::cout << root->value << " ";
    std::cout << root->t1 << " ";
    std::cout << root->t2 << " ";
    std::cout << root->proposition << "\n\n";
    print(root->next);
    print(root->left);
    print(root->right);
}

mnode *mtree::deserialize(std::string &expression, int start, int end)
{

    if (start > end)
        return NULL;
    mnode *node;
    // Binary case
    if (expression[start] == '(')
    {
        int bracket_diff = 1;
        int cur = start + 1;

        while (bracket_diff != 0)
        {
            if (expression[cur] == '(')
            {
                bracket_diff++;
            }
            else if (expression[cur] == ')')
            {
                bracket_diff--;
            }

            cur++;
        }

        // After this current points to Binary operator
        node = new mnode(expression[cur], (types)binary);
        auto times = get_times(expression, cur + 1, end);

        node->t1 = times[0];
        node->t2 = times[1];

        node->left = deserialize(expression, start + 1, cur - 2); // -2 and +1 to remove the bracket
        node->right = deserialize(expression, times[2] + 1, end - 1);
    }
    // Unary case
    else if (get_type(expression[start]) == (types)unary)
    {
        node = new mnode(expression[start], (types)unary);

        auto times = get_times(expression, start + 1, end);

        node->t1 = times[0];
        node->t2 = times[1];

        node->next = deserialize(expression, times[2] + 1, end - 1);
    }
    // atomic proposition
    else
    {
        node = new mnode();
        std::string value = expression.substr(start, end - start + 1);
        node->proposition = value;
    }
    return node;
}

// 0: false 1:true -1: don't know.
int mtree::evaluate(std::unordered_map<std::string, bool> prop_val, mnode *node)
{

    // propostion
    if (node->type == (types)empty)
    {
        return prop_val[node->proposition];
    }

    // binary
    if (node->type == (types)binary)
    {
        int left = evaluate(prop_val, node->left);
        int right = evaluate(prop_val, node->right);

        // Updating the queues in the node
        if (left >= 0)
            node->l1.push_back(left);
        if (right >= 0)
            node->l2.push_back(right);

        // Evaluating this node
        return get_value(node);
    }
    // unary

    if (node->type == (types)unary)
    {

        // next
        int next = evaluate(prop_val, node->next);

        if (next == -1)
            return -1;

        node->l1.push_back(next);

        return get_value(node);
    }

    return -1;
}

int mtree::get_value(mnode *node)
{

    switch (node->value)
    {
    case '^':
        return process_and(node);
    case 'v':
        return process_or(node);
    case '>':
        return process_implies(node);
    case '!':
        return process_not(node);
    case 'U':
        return process_until(node);
    case 'X':
        return process_next(node);

    case 'G':
        return process_globally(node);
    case 'F':
        return process_finally(node);
    default:
        return -1;
    }
}

// AND
int mtree::process_and(mnode *node)
{
    if (node->l1.size() && node->l2.size())
    {
        int verdict = node->l1.front() && node->l2.front();
        node->l1.pop_front();
        node->l2.pop_front();
        return verdict;
    }
    return -1;
}

// OR
int mtree::process_or(mnode *node)
{
    if (node->l1.size() && node->l2.size())
    {
        int verdict = node->l1.front() || node->l2.front();
        node->l1.pop_front();
        node->l2.pop_front();
        return verdict;
    }
    return -1;
}

// IMPLIES
int mtree::process_implies(mnode *node)
{
    if (node->l1.size() && node->l2.size())
    {
        int verdict = (!node->l1.front()) || (node->l2.front()); // !p | q
        node->l1.pop_front();
        node->l2.pop_front();
        return verdict;
    }
    return -1;
}

// NOT
int mtree::process_not(mnode *node)
{
    if (node->l1.size())
    {
        int verdict = !node->l1.front();
        node->l1.pop_front();
        return verdict;
    }
    return -1;
}

// NEXT
int mtree::process_next(mnode *node)
{
    if (node->l1.size() > 1)
    {
        int verdict = !node->l1.front();
        node->l1.pop_front();
        return verdict;
    }
    return -1;
}

// UNTIL
int mtree::process_until(mnode *node)
{

    if (node->l1.size() > node->t2 && node->l2.size() > node->t2)
    {
        int verdict = 1;

        // Finding if q is true in the window
        auto itr_q = node->l2.begin();
        std::advance(itr_q, node->t1);
        int qt = -1; // time when q became true between t1 and t2.
        for (int i = node->t1; i <= node->t2; i++)
        {
            if (*itr_q)
            {
                qt = i;
                break;
            }
            itr_q++;
        }
        // No q in the window [t1, t2]
        if (qt == -1)
            verdict = 0;

        // there is a q in the window [t1, t2]
        auto itr_p = node->l1.begin();
        for (int i = 0; i < qt; i++)
        { // check if p is true for all time before q_time.
            if (!(*itr_p))
                verdict = 0;
            itr_p++;
        }
        // Removing the front from both the queues
        node->l1.pop_front();
        node->l2.pop_front();
        return verdict;
    }
    return -1;
}

// Globally
int mtree::process_globally(mnode *node)
{
    if (node->l1.size() > node->t2)
    {
        int verdict = 1;
        auto itr = node->l1.begin();
        std::advance(itr, node->t1);

        for (int i = node->t1; i <= node->t2; i++)
        {
            if (!(*itr)){
                verdict = 0;
                break;
            }    
            itr++;
        }
        // Removing the front from the queue
        node->l1.pop_front();
        return verdict;
    }
    return -1;
}

//Finally
int mtree::process_finally(mnode *node)
{
    if(node->l1.size() > node->t1){
        int verdict = 0, index = node->t1;
        auto itr = node->l1.begin();
        std::advance(itr, node->t1);
        while(index < node->l1.size() && index <= node->t2){
            if (*itr){
                verdict = 1;
                break;
            }
            itr++;
        }
        if(verdict){
            node->l1.pop_front();
            return verdict;
        }
    }
    
    if(node->l1.size() > node->t2){
        node->l1.pop_front();
        return 0;
    }
    return -1;
}