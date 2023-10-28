/**************************************************************************
 * Encabezado de Arboles AVL
 * Autor: Gerardo Rodríguez Hernández
 * Fecha: 13/10/2023
 * Descripcion:
 * El objetivo de esta actividad es crear un árbol de búsqueda AVL
 **************************************************************************/
#ifndef AVL_h
#define AVL_h

class Node
{
  private:
    int *height;
    int *data;
    Node *right;
    Node *left;

  public:
    //Constructuor sin parámetros crea un nodo vacío
    Node(); 

    //Constructor con parámetros 
    //crea un nodo con los datos y con el apuntador a siguiente = NULL;
    Node(int);

    //Destructor
    ~Node();

    //Métodos Accessores Nodo 
    void setData(int);
    int  getData();

    void setRight(Node*);    
    Node* getRight();

    void setLeft(Node*);
    Node* getLeft();

    void setHeight(int);
    int getHeight();
};

//Class AVL Tree
class AVL{

  protected:
    Node *root;

  private:

    //Regresa la altura del AVL
    int height(Node*);
   
    //Regresa un entero que indica el nivel en que se encuentra un dato, 
    // o -1 en caso de que no se encuentre en el BST
    int whatLevelIam(int);
    
    //Regresa el factor de balanceo del nodo 
    // = altura del sub arbol izquierdo - altura del sub arbol derecho.
    int balance(Node *node);

    Node* rotateRight(Node* x);
    Node* rotateLeft(Node* y);

    Node* findMinNode(Node *node);

    Node* insert(Node* node, int val);
    Node* remove(Node* node, int val);


  public: 
    //Constructor Default
    AVL();

    //Destructor
    //Elimina los nodos de la lista
    ~AVL();

    //Funcion para insertar un nodo en el AVL
    void insert(int);

    //Funcion para remover un nodo del AVL
    void remove(int);

    //Imprime cada uno de los datos almacenados en el BST dependiendo del parámetro en entrada
    // 1: Preorder
    // 2: Inorder
    // 3: Postorder
    // 4: Level by Level
    void visit(int);

    //Función que devuelve la altura del árbol
    int height();

    //Imprime los ancestros de un dato
    void ancestors(int);
    
    void preorder(Node*);
    void inorder(Node*);
    void postorder(Node*);
    void levelbylevel(Node*);
};

#endif