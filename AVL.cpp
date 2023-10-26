/*  AVL.cpp
    Jean Paul López A01632766
    
    última modificación: 25/10/2023
    Define las funciones del archivo AVL.hpp */
#include "AVL.hpp"

// Node
Node::Node(int data) {
    this->data = new int(data);
    this->height = new int(0);
    this->left = nullptr;
    this->right = nullptr;
}
Node::Node() {
    this->data = new int;
    this->height = new int(0);
    this->left = nullptr;
    this->right = nullptr;
}
Node::~Node() {
    delete this->data;
    delete this->height;
    delete this->left;
    delete this->right;
}
    // getters
int Node::getData() {
    return *this->data;
}
int Node::getHeight() {
    return *this->height;
}
Node* Node::getLeft() {
    return this->left;
}
Node* Node::getRight() {
    return this->right;
}
    // setters
void Node::setData(int data) {
    *this->data = data;
}
void Node::setHeight(int height) {
    *this->height = height;
}
void Node::setLeft(Node *left) {
    this->left = left;
}
void Node::setRight(Node *right) {
    this->right = right;
}

// AVL
AVL::AVL() {
    this->root = nullptr;
}
AVL::~AVL() {
    delete root;
}
    // private
int AVL::height(Node *node) {
    if (node == nullptr) {
        return 0;
    }
    return node->getHeight();
}
int AVL::whatLevelIam(int number) {
    Node* aux = this->root;
    int data,level = 0;
    while (aux != nullptr) {
        data = aux->getData();
        if (number == data) {
            return level;
        } else if (number < data) {
            aux = aux->getLeft();
        } else {
            aux = aux->getRight();
        }
        level++;
    }
    return -1;
}
int AVL::balance(Node *node) {
    if (node == nullptr) {
        return 0;
    }
    int heightLeft =  node->getLeft()->getHeight();
    int heightRight = node->getRight()->getHeight();
    return heightLeft - heightRight;
}

    // public
void AVL::insert(int num) {
    Node *aux = this->root;
    Node *next = aux;
    while (next != nullptr) {
        aux = next;
        if (num < aux->getData()) {
            next = aux->getLeft();
        } else {
            next = aux->getRight();
        }
    }
    if (num < aux->getData()) {
        aux->setLeft(new Node(num));
    } else {
        aux->setRight(new Node(num));
    }
}
