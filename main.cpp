#include "AVL.hpp"
int main() {
    AVL arbol;
    arbol.insert(5);
    arbol.insert(3);
    arbol.insert(2);
    arbol.insert(1);
    arbol.insert(4);
    arbol.insert(7);
    arbol.insert(8);
    arbol.insert(6);
    arbol.insert(9);

    arbol.visit(1);
    arbol.visit(2);
    arbol.visit(3);
}