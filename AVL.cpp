/*  AVL.cpp
    Jean Paul López A01632766
    
    última modificación: 25/10/2023
    Define las funciones del archivo AVL.hpp */
#include "AVL.hpp"
#include <iostream>
#include <queue>

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
    return height(node->getLeft()) - height(node->getRight());
}
Node* rotateRight(Node* y) {
    Node* x = y->getLeft();
    Node* T2 = x->getRight();

    x->setRight(y);
    y->setLeft(T2);
    y->setHeight(1 + (x->getLeft() != nullptr ? x->getLeft()->getHeight() : 0));
    x->setHeight(1 + (y->getRight() != nullptr ? y->getRight()->getHeight() : 0));

    return x;
}
Node* rotateLeft(Node* x) {
    Node* y = x->getRight();
    Node* T2 = y->getLeft();

    y->setLeft(x);
    x->setRight(T2);
    x->setHeight(1 + (x->getLeft() != nullptr ? x->getLeft()->getHeight() : 0));
    y->setHeight(1 + (y->getRight() != nullptr ? y->getRight()->getHeight() : 0));

    return y;
}
Node* AVL::findMinNode(Node *node) {
    Node* aux = node->getRight();
    while (aux->getLeft() != nullptr) {
        aux = aux->getLeft();
    }
    
    return aux;
}
Node* AVL::insert(Node *node,int num) {
    // busca el lugar vacío para el nodo
    if (node == nullptr) {
        Node *newNode = new Node(num);
        return newNode;
    } if (num < node->getData()) {
        node->setLeft(insert(node->getLeft(),num));
    } else if (num > node->getData()) {
        node->setRight(insert(node->getRight(),num));
    } else {
        return node;
    }

    // actualiza la altura
    int leftH = height(node->getLeft()), rightH = height(node->getRight());
    int height_ = leftH > rightH ? (1 + leftH) : (1 + rightH);
    node->setHeight(height_);

    // encuentra su balance y hace rotaciones al respecto
    int balance_ = balance(node);
    if (balance_ > 1 && num < node->getLeft()->getData()) {
        return rotateRight(node);
    }
    if (balance_ < -1 && num > node->getRight()->getData()) {
        return rotateLeft(node);
    }
    if (balance_ > 1 && num > node->getLeft()->getData()) {
        node->setLeft(rotateLeft(node->getLeft()));
        return rotateRight(node);
    }
    if (balance_ < -1 && num < node->getRight()->getData()) {
        node->setRight(rotateRight(node->getRight()));
        return rotateLeft(node);
    }

    return node;
}
Node* AVL::remove(Node *node,int num) {
    if (node == nullptr) {
        return node;
    }

    // busca el nodo a eliminar
    if (num < node->getData()) {
        node->setLeft(remove(node->getLeft(),num));
    } else if (num > node->getData()) {
        node->setRight(remove(node->getRight(),num));
    } else {
        if (node->getLeft() == nullptr || node->getRight() == nullptr) {
            Node *aux = node->getLeft() ? node->getLeft() : node->getRight();
            if (aux == nullptr) {
                delete node;
            } else {
                *node = *aux;
            }
            delete aux;
        } else {
            Node *aux = findMinNode(node);
            node->setData(aux->getData());
            node->setRight(remove(node->getRight(),aux->getData()));
        }
    }

    // revisa si ya puede salirse o si necesita balancear
    if (node == nullptr) {
        return node;
    }

    // actualiza altura
    int leftH = height(node->getLeft()), rightH = height(node->getRight());
    int height_ = leftH > rightH ? (1 + leftH) : (1 + rightH);
    node->setHeight(height_);

    // balancea el nodo
    int balance_ = balance(node);
    if (balance_ > 1 && balance(node->getLeft()) >= 0) {
        return rotateRight(node);
    }
    if (balance_ < -1 && balance(node->getRight()) <= 0) {
        return rotateLeft(node);
    }
    if (balance_ > 1 && balance(node->getLeft()) < 0) {
        node->setLeft(rotateLeft(node->getLeft()));
        return rotateRight(node);
    }
    if (balance_ < -1 && balance(node->getRight()) > 0) {
        node->setRight(rotateRight(node->getRight()));
        return rotateLeft(node);
    }

    return node;
}
    // public
void AVL::insert(int num) {
    insert(this->root,num);
}
void AVL::remove(int num) {
    remove(this->root,num);
}
void AVL::visit(int option) {
    switch (option) {
        case 1:
            preorder(this->root);
            break;
        case 2:
            inorder(this->root);
            break;
        case 3:
            postorder(this->root);
            break;
        case 4:
            levelbylevel(this->root);
            break;
        default:
            std::cout << "invalid option\n";
    }
    
    std::cout << std::endl;
}
int AVL::height() {
    height(this->root);
}

// print format
void preorder(Node *node) {
    if (node != nullptr) {
        std::cout << node->getData() << " ";
        preorder(node->getLeft());
        preorder(node->getRight());
    }
}
void inorder(Node *node) {
    if (node != nullptr) {
        inorder(node->getLeft());
        std::cout << node->getData() << " ";
        inorder(node->getRight());
    }
}
void postorder(Node *node) {
    if (node != nullptr) {
        postorder(node->getLeft());
        postorder(node->getRight());
        std::cout << node->getData() << " ";
    }
}
void levelbylevel(Node *node) {
    if (node != nullptr) {
        std::queue <Node*> lista;
        lista.push(node);

        while (!lista.empty()) {
            Node *aux = lista.front();
            std::cout << aux->getData() << " ";
            lista.pop();

            if (aux->getLeft() != nullptr) {
                lista.push(node->getLeft());
            } if (aux->getRight() != nullptr) {
                lista.push(node->getRight());
            }
        }
    }
}
