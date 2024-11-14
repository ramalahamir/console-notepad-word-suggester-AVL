#include <conio.h>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string>

using namespace std;

template <typename T> struct Node
{
    T data;
    Node *next;

    Node(T val)
    {
        data = val;
        next = nullptr;
    }
};

class List
{
  private:
    Node<char> *head;

  public:
    List() { head = nullptr; }

    void Insertion(char data)
    {
        Node<char> *newNode = new Node(data);
        if (head == nullptr)
        {
            head = newNode;
            return;
        }
        Node<char> *temp = head;
        while (temp->next != nullptr)
            temp = temp->next;
        temp->next = newNode;
    }

    void Display()
    {
        Node<char> *temp = head;
        while (temp != nullptr)
        {
            cout << temp->data;
            temp = temp->next;
        }
        cout << endl;
    }

    void Backspace()
    {
        // no data to delete
        if (head == nullptr)
            return;

        // If there's only one letter in the list
        if (head->next == nullptr)
        {
            delete head;
            head = nullptr;
            return;
        }

        // delete the last letter
        Node<char> *temp = head;
        while (temp->next->next != nullptr)
            temp = temp->next;

        delete temp->next;
        temp->next = nullptr;
    }

    void save()
    {
        ofstream file("save.txt");
        Node<char> *temp = head;
        while (temp != nullptr)
        {
            file << temp->data;
            temp = temp->next;
        }
        file.close();
    }

    void load()
    {
        ifstream file("save.txt");
        if (file.is_open())
        {
            Node<char> *temp = head;

            char ch;
            while (temp != nullptr)
            {
                // insert if the character is present
                if (file.get(ch))
                    Insertion(ch);
                temp = temp->next;
            }

            file.close();
        }
        else
            cout << "\nno presaved data!";
    }

    char Peek()
    {
        if (head == nullptr)
            return ' ';
        return head->data;
    }

    ~List()
    {
        cout << "\nreleasing notepad memory...completed!";
        Node<char> *curr = head;
        Node<char> *NN;
        while (curr != nullptr)
        {
            NN = curr->next;
            delete curr;
            curr = NN;
        }
    }
};

class StrList
{
  private:
    Node<string> *head;

  public:
    StrList() { head = nullptr; }

    void Insertion(string data)
    {
        Node<string> *newNode = new Node(data);
        if (head == nullptr)
        {
            head = newNode;
            return;
        }
        Node<string> *temp = head;
        while (temp->next != nullptr)
            temp = temp->next;
        temp->next = newNode;
    }

    bool Display()
    {
        Node<string> *temp = head;

        // if no suggestions found
        if (head == nullptr)
        {
            cout << "\nNo suggestions found\n";
            return false;
        }

        int i = 1;
        cout << "\nsuggestions for correction: \n";
        cout << "0. ignore all\n";

        while (temp != nullptr)
        {
            cout << i << ". " << temp->data << endl;
            temp = temp->next;
            i++;
        }
        cout << endl;
        return true;
    }

    string retrieveWord(int choice)
    {
        Node<string> *temp = head;
        int i = 1;
        while (temp != nullptr)
        {
            if (i == choice)
                return temp->data;
            temp = temp->next;
            i++;
        }
        return "\0";
    }

    ~StrList()
    {
        Node<string> *curr = head;
        Node<string> *NN;
        while (curr != nullptr)
        {
            NN = curr->next;
            delete curr;
            curr = NN;
        }
    }
};

class Queue
{
  private:
    Node<char> *front;
    Node<char> *rear;

  public:
    Queue() { rear = front = nullptr; }

    void enqueue(char value)
    {
        Node<char> *newNode = new Node(value);
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

        Node<char> *temp = front;
        front = front->next;

        // list becomes empty
        if (front == nullptr)
            rear = nullptr;

        char data = temp->data;
        delete temp;
        return data;
    }

    string combineletters()
    {
        string word = "";
        Node<char> *temp = front;
        while (temp != nullptr)
        {
            word += temp->data;
            temp = temp->next;
        }
        return word;
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
    ~AVLTree()
    {
        cout << "\nreleasing dictionary memory...completed!";
        releaseMemory(root);
    }

    // deleting in postorder this way childern are deleted first
    // and no dangling pointers or issues occur
    void releaseMemory(treeNode *root)
    {
        if (root == nullptr)
            return;
        releaseMemory(root->left);
        releaseMemory(root->right);
        delete root;
    }

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
        // LR case
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

// word modification functions
void letterSubstitution(string word, AVLTree *dict, StrList *&suggestions)
{
    if (suggestions == nullptr)
        suggestions = new StrList();

    // 25 * k tries
    for (int i = 0; i < word.length(); i++)
    {
        string dummy_word = word; // to prserve the original
        for (int j = 97; j <= 122; j++)
        {
            // replacing with a-z ascii one by one
            dummy_word[i] = j;
            // if modified word exists
            if (dict->Search(dummy_word))
                suggestions->Insertion(dummy_word);
        }
    }
}

StrList *modifiedWord(string word, AVLTree *dict)
{
    StrList *suggestions = nullptr;
    letterSubstitution(word, dict, suggestions);
    return suggestions;
}

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
    Queue *wordQueue = new Queue();
    List *Text = new List();

    cout << "\t\tNOTEPAD\n";
    cout << "\t-----------------------\n";

    char input;
    // keeps track of if the word or corrected or not
    bool corrected = false;
    do
    {
        input = getch();

        // set new queue for new word after space
        if (wordQueue == nullptr)
        {
            wordQueue = new Queue();
            // reset the flag for a new word
            corrected = false;
        }

        // CTRL + S ascii
        if (input == 19)
            Text->save();

        // CTRL + L ascii
        else if (input == 12)
            Text->load();

        // BACKSPACE ascii
        else if (input == 8)
            Text->Backspace();

        // if space key isn't pressed keep enqueueing the word letters
        else if (input != 32)
        {
            // inserting to the list and queue
            Text->Insertion(input);
            wordQueue->enqueue(input);
        }

        // when space is pressed spell check is triggered
        else
        {
            // space is also included into the Text list
            Text->Insertion(input);

            // if the last character entered was also a space
            if (Text->Peek() == ' ' || corrected == true)
                continue;

            // combining queue into a string
            string checkWord = wordQueue->combineletters();
            string correction = "";

            // word suggestions and modifications if word
            //  doesn't exist in dictionary
            if (dict->Search(checkWord) == false)
            {
                StrList *suggestions = nullptr;
                suggestions = modifiedWord(checkWord, dict);

                // if suggestions exist then display menu
                if (suggestions != nullptr)
                {
                    // clear screen first
                    system("cls");
                    // display suggestion menu
                    // and returns state if suggestions exist
                    bool correctWord = suggestions->Display();
                    if (correctWord)
                    {
                        int choice;
                        cout << "enter correction choice: ";
                        cin >> choice;

                        if (choice != 0)
                        {
                            correction = suggestions->retrieveWord(choice);
                            cout << correction;
                            // erase the incorrect word
                            for (int i = 0; i <= checkWord.length(); i++)
                                Text->Backspace();
                            // enter the new word
                            for (int i = 0; i <= correction.length(); i++)
                                Text->Insertion(correction[i]);

                            corrected = true;
                        }
                    }
                }
            }
            // delete the queue and set it to null
            if (wordQueue != nullptr)
            {
                delete wordQueue;
                wordQueue = nullptr;
            }
        }

        // clear screen everytime and show the updated text
        system("cls");
        cout << "\t\tNOTEPAD\n";
        cout << "\t-----------------------\n";
        Text->Display();

    } while (input != 27); // ESC key (quit)

    // releasing memories
    if (wordQueue != nullptr)
        delete wordQueue;
    if (Text != nullptr)
        delete Text;
    if (dict != nullptr)
        delete dict;

    return 0;
}