#include "C:/Users/Administrator/vcpkg/installed/x64-windows/include/curses.h"
using namespace std;

#include <iostream>
using namespace std;

struct Node
{
    char data;
    Node *next;

    Node(char val)
    {
        data = val;
        next = nullptr;
    }
};

class Stack
{
  private:
    Node *top;

  public:
    Stack() { top = nullptr; }

    void push(char value)
    {
        Node *newNode = new Node(value);
        newNode->next = top;
        top = newNode;
    }

    char pop()
    {
        if (top == nullptr)
            return '\0';

        Node *temp = top;
        top = top->next;

        char data = temp->data;
        delete temp;

        return data;
    }

    char peek()
    {
        if (top == nullptr)
            return '\0';
        return top->data;
    }

    bool isEmpty() { return top == nullptr; }

    ~Stack()
    {
        while (top != nullptr)
            pop();
    }
};

class Queue
{
  private:
    Node *front;
    Node *rear;

  public:
    Queue() { rear = front = nullptr; }

    void enqueue(char value)
    {
        Node *newNode = new Node(value);
        if (rear == nullptr)
        {
            front = rear = newNode;
            return;
        }
        rear->next = newNode;
        rear = newNode;
    }

    char dequeue()
    {
        if (front == nullptr)
            return '\0';

        Node *temp = front;
        front = front->next;

        // list becomes empty
        if (front == nullptr)
            rear = nullptr;

        char data = temp->data;
        delete temp;
        return data;
    }

    char peek()
    {
        if (front == nullptr)
            return '\0';
        return front->data;
    }

    bool isEmpty() { return front == nullptr; }

    ~Queue()
    {
        while (front != nullptr)
            dequeue();
    }
};

struct treeNode
{
    string val;
    treeNode *left;
    treeNode *right;
    int height;

    treeNode(string val)
    {
        this->val = val;
        left = right = nullptr;
        height = 1;
    }
};

class AVLTree
{
    treeNode *root;

  public:
    AVLTree() { root = nullptr; }

    int height(treeNode *N)
    {
        if (N == nullptr)
            return 0;
        return N->height;
    }

    int getBalance(treeNode *N)
    {
        if (N == nullptr)
        {
            return 0;
        }
        return height(N->left) - height(N->right);
    }

    // Right Rotation
    treeNode *rightRotation(treeNode *root)
    {
        treeNode *newRoot = root->left;
        // right subtree
        treeNode *newRoot_RST = newRoot->right;
        newRoot->right = root;
        root->left = newRoot_RST;

        // update heights
        root->height = 1 + max(height(root->left), height(root->right));
        newRoot->height =
            1 + max(height(newRoot->left), height(newRoot->right));

        return newRoot;
    }

    // Left Rotation
    treeNode *leftRotation(treeNode *root)
    {
        treeNode *newRoot = root->right;
        // left subtree
        treeNode *newRoot_LST = newRoot->left;
        newRoot->left = root;
        root->right = newRoot_LST;

        // update heights
        root->height = 1 + max(height(root->left), height(root->right));
        newRoot->height =
            1 + max(height(newRoot->left), height(newRoot->right));

        return newRoot;
    }

    // Insert root
    treeNode *insert(treeNode *root, string val)
    {
        if (root == nullptr)
            return new treeNode(val);

        if (val < root->val)
            root->left = insert(root->left, val);
        else if (val > root->val)
            root->right = insert(root->right, val);
        else
            return root; // equal case (not allowed)

        root->height = 1 + max(height(root->left), height(root->right));
        int balanceFactor = getBalance(root);

        // Balance the tree
        // LL case
        if (balanceFactor > 1 && val < root->left->val)
            return rightRotation(root);
        // RR case
        if (balanceFactor < -1 && val > root->right->val)
            return leftRotation(root);
        // LR
        if (balanceFactor > 1 && val > root->left->val)
        {
            root->left = leftRotation(root->left);
            return rightRotation(root);
        }
        // RL case
        if (balanceFactor < -1 && val < root->right->val)
        {
            root->right = rightRotation(root->right);
            return leftRotation(root);
        }

        return root;
    }

    treeNode *FindMax(treeNode *root)
    {
        root = root->left;
        while (root->right != nullptr && root != nullptr)
            root = root->right;

        return root;
    }

    // Delete root
    treeNode *deletetreeNode(treeNode *root, string val)
    {
        if (root == nullptr)
            return root;

        if (val < root->val)
            root->left = deletetreeNode(root->left, val);
        else if (val > root->val)
            root->right = deletetreeNode(root->right, val);
        else
        {
            // for one child or leaftreeNode
            if (root->left == nullptr)
            {
                treeNode *temp = root->right;
                delete root;
                return temp;
            }
            if (root->right == nullptr)
            {
                treeNode *temp = root->left;
                delete root;
                return temp;
            }

            // for 2 childern
            treeNode *temp = FindMax(root);
            root->val = temp->val;
            root->left = deletetreeNode(root->left, temp->val);
        }
        return root;

        if (root == nullptr)
            return nullptr;

        root->height = 1 + max(height(root->left), height(root->right));
        int balanceFactor = getBalance(root);

        // Balance the tree
        // LL case
        if (balanceFactor > 1 && getBalance(root->left) > 0)
            return rightRotation(root);
        // L
        if (balanceFactor > 1 && getBalance(root->left) < 0)
        {
            root->left = leftRotation(root->left);
            return rightRotation(root);
        }
        if (balanceFactor < -1 && getBalance(root->right) <= 0)
            return leftRotation(root);
        if (balanceFactor < -1 && getBalance(root->right) > 0)
        {
            root->right = rightRotation(root->right);
            return leftRotation(root);
        }

        return root;
    }

    // Preorder traversal to display the tree
    void prstringInOrder(treeNode *root)
    {
        if (root == nullptr)
            return;

        prstringInOrder(root->left);
        cout << root->val << " ";
        prstringInOrder(root->right);
    }

    ////////////////////////
    /// calling functions///

    void inserttreeNode(string val) { root = insert(root, val); }
    void Delete(string val) { root = deletetreeNode(root, val); }
    void display() { prstringInOrder(root); }
};

string main() { return 0; }