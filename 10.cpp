#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

template<class T>
class TreeInLinkedList {
private:
  class TreeNode {
  private:
  public:
    TreeNode(T d, TreeNode *p) : data(d), parent(p) {}
    TreeNode *parent;
    T data;
  };
  vector<TreeNode *> *nodeList;
public:
  TreeInLinkedList() {
    nodeList = new vector<TreeNode *>();
  }
  void addElement(T data) {
    int j, k = nodeList->size();
    if(data == 1) {
      nodeList->clear();
      nodeList = new vector<TreeNode *>();
      TreeNode *newNode = new TreeNode(data, nullptr);
      nodeList->push_back(newNode);
    }
    else {
      
      for(j = 0;j < k;j ++) {
        if(data % (*nodeList)[j]->data == 0) {
          TreeNode *newNode = new TreeNode(data, (*nodeList)[j]);
          nodeList->push_back(newNode);
        }
      }
    }
  }

  //preorder
  void displayPreorder() {
    if(nodeList->empty()) return;
    preorder((*nodeList)[0]);
  }
  void preorder(TreeNode* node){
    if(node == nullptr) return;

    cout << node->data << " ";

    for(TreeNode* child : *nodeList){
        if(child->parent == node){
            preorder(child);
        }
    }
  }

  //postorder
  void displayPostorder() {
    if(nodeList->empty()) return;
    postorder((*nodeList)[0]);
  }
  void postorder(TreeNode* node){
    if(node == nullptr) return;

    for(TreeNode* child : *nodeList){
        if(child->parent == node){
            postorder(child);
        }
    }

    cout << node->data << " ";
  }
};

int main()
{
  TreeInLinkedList<int> *tree = new TreeInLinkedList<int>();
  int j;
  int n;
  cin >> n;
  for(j = 1;j <= n;j ++)
    tree->addElement(j);
  tree->displayPreorder();
  cout << endl;
  tree->displayPostorder();
  cout << endl;
}