#include <bits/stdc++.h>

using namespace std;

template<class T>
class BinaryTreeInArray {
private:
  T *array;
  int height;
  int numOfElement;
  void resize(int size) {
    T *temp = new T[numOfElement];
    int j;
    for(j = 0;j < numOfElement;j ++)
      temp[j] = array[j];
    delete array;
    array = new T[static_cast<int>(pow(2, height + 1)) - 1];
    for(j = 0;j < numOfElement;j ++)
      array[j] = temp[j];
    height ++;
    delete temp;
  }
public:
  BinaryTreeInArray() : array(nullptr), height(0), numOfElement(0) {}
  void addElementAsCompleteTree(T data) {
    int cap = pow(2, height) - 1;
    if(numOfElement + 1 > cap)
      resize((cap + 1) * 2 - 1);
    array[numOfElement] = data;
    numOfElement ++;
  }

    //inorder left->parent->right
    void displayInorder() {
        inorder(0);
    }
    void inorder(int i){
        if(i < numOfElement){
            inorder(i * 2 + 1);
            cout << array[i] << " ";
            inorder(i * 2 + 2);
        }
        else return;
    }

    //preorder parant->left->right
    void displayPreorder() {
        preorder(0);
    }
    void preorder(int i){
        if(i < numOfElement){
            cout << array[i] << " ";
            preorder(i * 2 + 1);
            preorder(i * 2 + 2);
        }
    }

    //postorder left->right->parant
    void displayPostorder() {
        postorder(0);
    }
    void postorder(int i){
        if(i < numOfElement){
            postorder(i * 2 + 1);
            postorder(i * 2 + 2);
            cout << array[i] << " ";
        }
    }
};

template<class T>
class BinaryTreeInLinkedList {
private:
  class TreeNode {
  private:
  public:
    TreeNode(T d) : data(d), left(nullptr), right(nullptr) {}
    TreeNode *left, *right;
    T data;
  };
  TreeNode *root;
  int numOfElement;
public:
  BinaryTreeInLinkedList() : root(nullptr), numOfElement(0) {}
  void addElementAsCompleteTree(T data) {
    TreeNode* newNode = new TreeNode(data);
    numOfElement++;
    
    if(!root){
      root = newNode;
      return;
    }

    queue<TreeNode* > q;
    q.push(root);
    while(!q.empty()){
      TreeNode* temp = q.front();
      q.pop();

      if(!temp->left){
        temp->left = newNode;
        return;
      }
      else q.push(temp->left);

      if(!temp->right){
        temp->right = newNode;
        return;
      }
      else q.push(temp->right);
    }
  }

  //inorder left->parent->right
  void displayInorder() {
    inorder(root);
  }
  void inorder(TreeNode* node){
    if (node == nullptr) return;
    inorder(node->left);
    cout << node->data << " ";
    inorder(node->right);
  }
  
  //preorder parant->left->right
  void displayPreorder() {
    preorder(root);
  }
  void preorder(TreeNode* node){
    if (node == nullptr) return;
    cout << node->data << " ";
    preorder(node->left);
    preorder(node->right);
  }

  //postorder left->right->parant
  void displayPostorder() {
    postorder(root);
  }
  void postorder(TreeNode* node){
    if (node == nullptr) return;
    postorder(node->left);
    postorder(node->right);
    cout << node->data << " ";
  }
};

int main()
{
  BinaryTreeInArray<int> *b = new BinaryTreeInArray<int>;
  BinaryTreeInLinkedList<int> *tree = new BinaryTreeInLinkedList<int>;
  int j, n;
  cin >> n;
  for(j = 0;j < n;j ++) {
    b->addElementAsCompleteTree(j);
    tree->addElementAsCompleteTree(j);
  }
  b->displayInorder();
  cout << endl;
  tree->displayInorder();
  cout << endl;
  b->displayPreorder();
  cout << endl;
  tree->displayPreorder();
  cout << endl;
  b->displayPostorder();
  cout << endl;
  tree->displayPostorder();
  cout << endl;
  return 0;
}
