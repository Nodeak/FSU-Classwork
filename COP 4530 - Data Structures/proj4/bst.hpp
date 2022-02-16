/*  Kaedon Hamm
    COP4530 - Duan
    Project 4 - BST Class
    11/15/2018
*/

#include "bst.h"


// Constructor. Th specifies value for the single rotation threshold.
template <typename T>
BST<T>::BST(int th): root{nullptr}{
    
}


// Constructor with string of integers as first parameter and threshold as second.
template <typename T>
BST<T>::BST(const std::string input, int th): root{nullptr}{
    buildFromInputString(input);
}

// copy constructor
template <typename T>
BST<T>::BST(const BST& rhs): root{nullptr}{
    root = clone(rhs.root);
}


// move constructor
template <typename T>
BST<T>::BST(BST&& rhs){
    if( this != &rhs ){
        makeEmpty();
        root = clone( rhs.root );
    }
}

// Deconstructor
template <typename T>
BST<T>::~BST(){
    makeEmpty();
}


template <typename T>
void BST<T>::buildFromInputString(const std::string input){
    if(!empty())
        makeEmpty();


    std::vector<std::string> i;
    std::istringstream iss(input);
    for(std::string x; iss >> x;){
        i.push_back(x);
    }

    T temp;
    for(auto itr : i){
        std::stringstream holder(itr);
        holder >> temp;
        insert(temp);
    }


}


template <typename T>
const BST<T>& BST<T>::operator=(const BST& rhs){
    if(this != &rhs){
        makeEmpty();
        root = clone(rhs.root);
    }
    return *this;
}

template <typename T>
const BST<T>& BST<T>::operator=(BST&& rhs){
    if( this != &rhs ){
            makeEmpty();
            root = clone( rhs.root );
    }
    return *this;
}

template <typename T>
bool BST<T>::empty() const{
    return root == nullptr;
}


// Public functions
template <typename T>
void BST<T>::printInOrder() const{
    if(empty())
          std::cout << "Empty tree" << std::endl;
    else
        printInOrder(root);
}

template <typename T>
void BST<T>::printLevelOrder() const{
    printLevelOrder(root);
}

template <typename T>
int BST<T>::numOfNodes() const{
    return numOfNodes(root);
}

template <typename T>
int BST<T>::height() const{
    return height(root);
}

template <typename T>
void BST<T>::makeEmpty(){
    makeEmpty(root);
}

template <typename T>
void BST<T>::insert(const T& v){
    if(root == nullptr)
        root = new BSTNode{v, nullptr, nullptr};
    insert(v, root);
}

template <typename T>
void BST<T>::insert(T &&v){
    if(root == nullptr)
        root = new BSTNode{v, nullptr, nullptr};
    insert(v, root);
}

template <typename T>
void BST<T>::remove(const T& v){
    remove(v, root);
}

template <typename T>
bool BST<T>::contains(const T& v){
    return contains(v, root);
}










// Private functions
template <typename T>
void BST<T>::printInOrder(BSTNode *t) const{
    if( t == nullptr )
        return;

    printInOrder( t->left );
        std::cout << t->element << " ";
    printInOrder( t->right );
}

template <typename T>
void BST<T>::printLevelOrder(BSTNode *t) const{
    if(t == nullptr)
        return;
    std::cout << t->element << " ";
    printLevelOrder(t->left);
    printLevelOrder(t->right);
}

template <typename T>
void BST<T>::makeEmpty(BSTNode* &t){
    if( t != nullptr )
    {
        makeEmpty( t->left );
        makeEmpty( t->right );
        delete t;
    }
    t = nullptr;
    //root = nullptr;
}

template <typename T>
void BST<T>::insert(const T& v, BSTNode *&t){
    if( t == nullptr )
        t = new BSTNode{ v, nullptr, nullptr };
    else if( v < t->element )
        insert( v, t->left );
    else if( t->element < v )
        insert( v, t->right );
    else;  // Duplicate; do nothing

}

template <typename T>
void BST<T>::insert(T&& v, BSTNode *&t){
    if( t == nullptr )
        t = new BSTNode{ v, nullptr, nullptr };
    else if( v < t->element )
        insert( v, t->left );
    else if( t->element < v )
        insert( v, t->right );
    else;  // Duplicate; do nothing
}

template <typename T>
void BST<T>::remove(const T& v, BSTNode *&t){
    if( t == nullptr )
        return;   // Item not found; do nothing
    if( v < t->element )
        remove( v, t->left );
    else if( t->element < v )
        remove( v, t->right );
    else if( t->left != nullptr && t->right != nullptr )  { // two children
        t->element = findMin( t->right )->element;
        remove( t->element, t->right );
    }
    else {
        BSTNode *oldNode = t;
        t = ( t->left != nullptr ) ? t->left : t->right;
        delete oldNode;
    }
}

template <typename T>
bool BST<T>::contains(const T& v, BSTNode *&t){
    if( t == nullptr )
        return false;
    else if( v < t->element )
        return contains( v, t->left );
    else if( t->element < v )
        return contains( v, t->right );
    else
        return true;    // Match
} 

template <typename T>
int BST<T>::numOfNodes(BSTNode *t) const{
    if(t == nullptr)
        return 0;
    return 1+numOfNodes(t->left)+numOfNodes(t->right);
}

template <typename T>
int BST<T>::height(BSTNode *t) const{
    if (t == nullptr)
        return 0;
    return 1 + std::max(height(t->left), height(t->right));
}


template <typename T>
typename BST<T>::BSTNode* BST<T>::clone( BSTNode *t ) const{
    if( t == nullptr )
        return nullptr;
    else
        return new BSTNode{ t->element, clone( t->left ), clone( t->right ) };
}


template <typename T>
typename BST<T>::BSTNode* BST<T>::findMin(BSTNode *t) const{
    if( t == nullptr )
        return nullptr;
    if( t->left == nullptr )
        return t;
    return findMin( t->left );
}

template <typename T>
typename BST<T>::BSTNode* BST<T>::findMax(BSTNode *t) const{
    if( t == nullptr )
        return nullptr;
    if( t->right == nullptr )
        return t;
    return findMin( t->right );
}