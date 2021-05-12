#include "Node.h"
using namespace std;


void Node::addCounter(){
    counter++;
}

void Node::decreaseCounter(){
    counter--;
}

string Node::getString(){
    return this->data;
}

void Node::setString(const string &a)
{
    data = a;
}

int Node::getCounter() const{
    return counter;
}

void Node::setCounter(int abc){
    counter = abc;
}