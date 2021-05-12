#define _NODE_H

#include <iostream>
using namespace std;

class Node{
    private: 
    string data;
    int counter; 

    public:
    Node(): data(nullptr), counter(0), left(nullptr), right(nullptr){}
    Node(string name): data(name), counter(0), left(nullptr), right(nullptr){}

    Node *left;
    Node *right;


    void addCounter();
    void decreaseCounter();
    string getString();
    void setCounter(int);
    void setString(const string &);
    int getCounter() const;
};

