#include <conio.h>
#include <fstream>
#include <iostream>
#include <string>

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
    string word;
    treeNode *left;
    treeNode *right;
    int height;

    treeNode(string word)
    {
        this->word = word;
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
    treeNode *insert(treeNode *root, string word)
    {
        if (root == nullptr)
            return new treeNode(word);

        if (root->word > word)
            root->left = insert(root->left, word);
        else if (root->word < word)
            root->right = insert(root->right, word);
        else
            return root; // equal case (not allowed)

        root->height = 1 + max(height(root->left), height(root->right));
        int balanceFactor = getBalance(root);

        // Balance the tree
        // LL case
        if (balanceFactor > 1 && word < root->left->word)
            return rightRotation(root);
        // RR case
        if (balanceFactor < -1 && word > root->right->word)
            return leftRotation(root);
        // LR
        if (balanceFactor > 1 && word > root->left->word)
        {
            root->left = leftRotation(root->left);
            return rightRotation(root);
        }
        // RL case
        if (balanceFactor < -1 && word < root->right->word)
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
    treeNode *deletetreeNode(treeNode *root, string word)
    {
        if (root == nullptr)
            return root;

        if (root->word > word)
            root->left = deletetreeNode(root->left, word);
        else if (root->word < word)
            root->right = deletetreeNode(root->right, word);
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
            root->word = temp->word;
            root->left = deletetreeNode(root->left, temp->word);
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
        // LR case
        if (balanceFactor > 1 && getBalance(root->left) < 0)
        {
            root->left = leftRotation(root->left);
            return rightRotation(root);
        }
        // RR case
        if (balanceFactor < -1 && getBalance(root->right) <= 0)
            return leftRotation(root);
        // RL case
        if (balanceFactor < -1 && getBalance(root->right) > 0)
        {
            root->right = rightRotation(root->right);
            return leftRotation(root);
        }

        return root;
    }

    bool SearchNode(treeNode *root, string word)
    {
        if (root == nullptr)
            return false;
        if (root->word == word)
            return true;

        else if (root->word > word)
            return SearchNode(root->left, word);
        else
            return SearchNode(root->right, word);
    }

    ////////////////////////
    /// calling functions///

    void insertTreeNode(string word) { root = insert(root, word); }
    void Delete(string word) { root = deletetreeNode(root, word); }
    bool Search(string word) { return SearchNode(root, word); }
};

AVLTree *readDictFile()
{
    AVLTree *tree = new AVLTree();

    ifstream file("dictionary.txt");
    if (file.is_open())
    {
        string line;
        while (getline(file, line))
        {
            // inserting it to the AVL tree
            tree->insertTreeNode(line);
        }
    }
    else
    {
        // show error and close window
        cout << "error opening file";
    }
    file.close();

    return tree;
}

int main()
{

    // making the dictionary tree
    AVLTree *dict = readDictFile();
    Queue word();

    cout << "\t\tNOTEPAD\n";
    cout << "\t-----------------------\n";

    char input;
    do
    {
        input = getche(); // echoes onto the screen

    } while (input != 27); // ESC key (quit)

    return 0;
}