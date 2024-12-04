#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <ctime>

using namespace std;

template<class T>
class Node
{
public:
    Node()
    {
        data = new T;
    }
    Node(T d)
    {
        data = new T;
        (*data) = d;
    }
    Node &operator=(T d)
    {
        (*data) = d;
        return *this;
    }
    friend std::ostream &operator<<(std::ostream &out, Node n)
    {
        out << *(n.data);
        return out;
    }
    friend std::ostream &operator<<(std::ostream &out, Node *n)
    {
        out << *(n->data);
        return out;
    }
    void setData(T d)
    {
        *data = d;
    }
    T &getData() const
    {
        return *data;
    }
protected:
    T *data;
};

template<class T>
class BinaryTreeNode : public Node<T>
{
public:
    BinaryTreeNode() : Node<T>()
    {
        left = NULL;
        right = NULL;
        height = 1;
    }
    BinaryTreeNode(T d) : Node<T>(d)
    {
        left = NULL;
        right = NULL;
        height = 1;
    }
    void setLeft(BinaryTreeNode<T> *l)
    {
        left = l;
    }
    void setRight(BinaryTreeNode<T> *r)
    {
        right = r;
    }
    BinaryTreeNode<T> *&getLeft()
    {
        return left;
    }
    BinaryTreeNode<T> *&getRight()
    {
        return right;
    }
	bool operator>(BinaryTreeNode<T> n)
	{
		if(*(this->data) > *(n.data))
			return true;
		return false;
	}
	bool operator==(BinaryTreeNode<T> n)
	{
		if(*(this->data) == *(n.data))
			return true;
		return false;
	}
    int getHeight()
    {
        return height;
    }
    void setHeight(int h)
    {
        height = h;
    }
private:
    BinaryTreeNode<T> *left, *right;
    int height;
};

template<class T>
class AVLTree
{
private:
    BinaryTreeNode<T> *root;

    int height(BinaryTreeNode<T> *node)
    {
        return node == NULL ? 0 : node->getHeight();
    }

    int balanceFactor(BinaryTreeNode<T> *node)
    {
        return node == NULL ? 0 : height(node->getLeft()) - height(node->getRight());
    }

    BinaryTreeNode<T> *rotateRight(BinaryTreeNode<T> *y)
    {
        BinaryTreeNode<T> *x = y->getLeft();
        BinaryTreeNode<T> *T2 = x->getRight();
        x->setRight(y);
        y->setLeft(T2);
        y->setHeight(max(height(y->getLeft()), height(y->getRight())) + 1);
        x->setHeight(max(height(x->getLeft()), height(x->getRight())) + 1);
        return x;
    }

    BinaryTreeNode<T> *rotateLeft(BinaryTreeNode<T> *x)
    {
        BinaryTreeNode<T> *y = x->getRight();
        BinaryTreeNode<T> *T2 = y->getLeft();
        y->setLeft(x);
        x->setRight(T2);
        x->setHeight(max(height(x->getLeft()), height(x->getRight())) + 1);
        y->setHeight(max(height(y->getLeft()), height(y->getRight())) + 1);
        return y;
    }

    BinaryTreeNode<T> *insertNode(BinaryTreeNode<T> *node, T key)
    {
        if (node == NULL)
            return new BinaryTreeNode<T>(key);

        if (key < node->getData())
            node->setLeft(insertNode(node->getLeft(), key));
        else if (key > node->getData())
            node->setRight(insertNode(node->getRight(), key));
        else
            return node;

        node->setHeight(1 + max(height(node->getLeft()), height(node->getRight())));
        int balance = balanceFactor(node);

        if (balance > 1 && key < node->getLeft()->getData()) //left left
            return rotateRight(node);
        if (balance < -1 && key > node->getRight()->getData()) // right right
            return rotateLeft(node);
        if (balance > 1 && key > node->getLeft()->getData()) // left right
        {
            node->setLeft(rotateLeft(node->getLeft()));
            return rotateRight(node);
        }
        if (balance < -1 && key < node->getRight()->getData()) // right left
        {
            node->setRight(rotateRight(node->getRight()));
            return rotateLeft(node);
        }
        return node;
    }

    void inorder(BinaryTreeNode<T> *cur, int n)
    {
        if (cur == NULL)
            return;
        inorder(cur->getRight(), n + 1);
        for (int j = 0; j < n; j++)
            cout << "  ";
        cout << cur << endl;
        inorder(cur->getLeft(), n + 1);
    }

public:
    AVLTree() : root(NULL) {}
    void insert(T d)
    {
        root = insertNode(root, d);
    }
    void inorder()
    {
        inorder(root, 0);
    }
};

int main()
{
	AVLTree<int> *tree = new AVLTree<int>();
	srand(0);
	int j, k, i;
	for(j = 0;j < 20;j ++)
	{
		tree->insert(rand() % 100);
		tree->inorder();
	}
}
