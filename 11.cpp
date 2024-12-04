#include <iostream>
#include <string>

using namespace std;

template<class T>
class BinarySearchTree {
private:
  struct Node {
    T data;
    Node *left, *right;
  };
  void inorder(Node *cur) {
    if(!cur)
      return;
    inorder(cur->left);
    cout << cur->data << " ";
    inorder(cur->right);
  }
  Node *root;

  Node* insertRecursion(Node *node, T elem){
    if(node == nullptr){
        node = new Node;
        node->data = elem;
        node->left = nullptr;
        node->right = nullptr;
    }

    else {
        if(elem < node->data){
            node->left = insertRecursion(node->left, elem);
        }
        else {
            node->right = insertRecursion(node->right, elem);
        }
    }

    return node;
  }

  bool searchRecursion(Node *node, T elem){
    if(node == nullptr)return false;

    if(elem < node->data)return searchRecursion(node->left, elem);

    else if(elem > node->data)return searchRecursion(node->right, elem);

    else return true;
  }

  int heightRecursion(Node *node){
    if(node == nullptr)return 0;
    
    return max(heightRecursion(node->left), heightRecursion(node->right)) + 1;
  }
public:
  BinarySearchTree() : root(nullptr) {}

  void insertElement(T d) {
    if(search(d)) return;

    else {
        root = insertRecursion(root, d);
        return;
    }
  }

  void print() {
    inorder(root);
    cout << endl;
  }

  bool search(T d) {
    return searchRecursion(root, d);
  }

  int height() {
    return heightRecursion(root);
  }
};

int main() {
  int data;
  string command;
  BinarySearchTree<int> *bst = new BinarySearchTree<int>();
  while(true) {
    cin >> command;
    if(command == "insert") {
      cin >> data;
      bst->insertElement(data);
    }
    else if(command == "search") {
      cin >> data;
      if(bst->search(data))
        cout << "true" << endl;
      else
        cout << "false" << endl;
    }
    else if(command == "height") {
      cout << bst->height() << endl;
    }
    else if(command == "print") {
      bst->print();
    }
    else if(command == "exit") {
      break;
    }
  }
}