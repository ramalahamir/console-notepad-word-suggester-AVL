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

    /**
     * Constructs a Node from a given value.
     *
     * @param val the value stored in the node
     */
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

    /**
     * Inserts a new node with the given character at the end of the linked list
     *
     * @param data the character to be inserted
     */
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

    /**
     * Displays the characters stored in the linked list in sequence.
     * Outputs each character to the console followed by a newline.
     */
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

    /**
     * Deletes the last character stored in the linked list
     *
     * Does nothing if the list is empty. Otherwise, deletes the last node
     * in the list and adjusts the list's internal pointers accordingly.
     */
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

    /**
     * Saves the characters stored in the linked list to a file named
     * "save.txt". Each character is written to the file in sequence, without
     * any line breaks. The file is closed after all characters have been
     * written.
     */
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

    /**
     * Loads characters from the file named "save.txt" and inserts them into the
     * linked list. If the file is successfully opened, it reads each character
     * from the file and appends it to the end of the current list using the
     * Insertion function. The file is closed after all characters have been
     * read and inserted. If the file cannot be opened, a message is displayed
     * indicating that there is no saved data.
     */
    void load()
    {
        ifstream file("save.txt");
        if (file.is_open())
        {
            Node<char> *temp = head;

            char ch;
            // iterate till the cursor position in the text
            while (temp != nullptr)
                temp = temp->next;

            while (file.get(ch)) // insert if the character is present
                Insertion(ch);

            file.close();
        }
        else
            cout << "\nno presaved data!";
    }

    /**
     * Returns the first character of the linked list without removing it.
     *
     * @return the first character of the linked list, or a space if the list is
     * empty
     */
    char Peek()
    {
        if (head == nullptr)
            return ' ';
        return head->data;
    }

    /**
     * Destructor for the List class.
     *
     * This function iterates through the linked list and deletes each node,
     * freeing up memory for other uses. It displays a message when it is
     * finished.
     */
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

    /**
     * Inserts a new node with the given string at the end of the linked list.
     *
     * @param data The string to be inserted into the linked list.
     *
     * This function allocates a new node with the given string and inserts it
     * at the end of the linked list. If the list is empty, the new node becomes
     * the head of the list.
     */
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

    /**
     * Displays all the strings in the linked list, with a number from 1
     * onwards, and a 0 option to ignore all suggestions.
     *
     * @return true if there are suggestions, false if there are none.
     */
    bool Display()
    {
        Node<string> *temp = head;

        // if no suggestions found
        if (head == nullptr)
        {
            cout << "\nNo suggestions found\n";
            // getch();
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

    /**
     * Retrieves the word at the specified position in the linked list.
     *
     * @param choice The position of the word to retrieve (1-based index).
     * @return The word at the specified position, or an empty string if the
     * position is invalid.
     */
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

    /**
     * Destructor for the StrList class.
     *
     * This function iterates through the linked list and deletes each node,
     * freeing up memory for other uses. It displays a message when it is
     * finished.
     */
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

    /**
     * Adds a new character to the end of the queue.
     *
     * @param value The character to be added to the queue.
     *
     * This function creates a new node with the given character and appends it
     * to the end of the queue. If the queue is empty, the new node becomes both
     * the front and rear of the queue.
     */
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

    /**
     * Removes the character from the front of the queue and returns it.
     *
     * @return The character removed from the queue, or '\0' if the queue is
     * empty.
     *
     * This function removes the front node from the queue and updates the front
     * and rear pointers accordingly. If the queue becomes empty, it deletes the
     * last node and sets the front and rear to nullptr.
     */
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

    /**
     * Combines all characters in the queue into a single string.
     *
     * @return A string containing all the characters from the front to the rear
     * of the queue in sequence. If the queue is empty, returns an empty string.
     */
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

    /**
     * Returns the front character of the queue without removing it.
     *
     * @return The front character of the queue, or a space if the queue is
     * empty.
     */
    char peek()
    {
        if (front == nullptr)
            return '\0';
        return front->data;
    }

    bool isEmpty() { return front == nullptr; }

    /**
     * Destructor for the Queue class.
     *
     * This function iterates through the linked list and deletes each node,
     * freeing up memory for other uses. It does not display a message when
     * it is finished.
     */
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

    /**
     * Constructor for the treeNode class.
     *
     * Constructs a new treeNode object with the given word. The left and right
     * children are set to nullptr, and the height is set to 1.
     *
     * @param word the word stored in the node
     */
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

    /**
     * Destructor for the AVLTree class.
     *
     * This function iterates through the tree and deletes each node, freeing up
     * memory for other uses. It displays a message when it is finished.
     */
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

    /**
     * Calculates the height of the given tree node.
     *
     * If the given node is nullptr, this function returns 0. Otherwise, it
     * returns the height of the node as stored in the node's height field.
     *
     * @param N the node whose height to calculate
     * @return the height of the node

     */
    int height(treeNode *N)
    {
        if (N == nullptr)
            return 0;
        return N->height;
    }

    /**
     * Calculates the balance factor of the given tree node.
     *
     * The balance factor of a node is the difference between the height of its
     * left subtree and the height of its right subtree. If the given node is
     * nullptr, this function returns 0.
     *
     * @param N the node whose balance factor to calculate
     * @return the balance factor of the node
     */
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
    /**
     * Inserts a new node with the given word into the AVL tree.
     *
     * The word is inserted into the tree such that the tree remains balanced.
     * If the word is already present in the tree, this function does nothing.
     *
     * @param root The root of the AVL tree to insert the new word into.
     * @param word The word to insert into the tree.
     * @return The root of the AVL tree after insertion.
     */
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

    /**
     * Finds the node with the maximum value in the left subtree of the given
     * root node.
     *
     * This function traverses the left subtree of the given root node and
     * continues to move to the right child of each node until it reaches the
     * rightmost node, which contains the maximum value in that subtree. If the
     * root node is nullptr, the function returns nullptr.
     *
     * @param root The root node of the subtree to search for the maximum value.
     * @return The node with the maximum value in the left subtree.
     */
    treeNode *FindMax(treeNode *root)
    {
        root = root->left;
        while (root->right != nullptr && root != nullptr)
            root = root->right;

        return root;
    }

    // Delete root
    /**
     * Deletes the node with the given word from the AVL tree.
     *
     * If the given root node is nullptr, this function returns nullptr.
     * Otherwise, it recursively traverses the tree and deletes the node with
     * the given word by rearranging the tree's internal pointers. If the
     * deleted node has two children, the function finds the maximum value in
     * the left subtree of the node and replaces the node's word with it, then
     * deletes the maximum node in the left subtree. After deletion, the
     * function rebalances the tree if necessary by rotating nodes.
     *
     * @param root The root node of the AVL tree to delete the given word from.
     * @param word The word to delete from the AVL tree.
     * @return The root of the AVL tree after deletion. If the root node is
     * nullptr, this function returns nullptr.
     */
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

    /**
     * Searches for a given word in the AVL tree starting from the given root
     * node.
     *
     * @param root The root node of the AVL tree to search in.
     * @param word The word to search for.
     * @return true if the word is found in the tree, false otherwise.
     */
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

/**
 * Finds words with a single letter substitution and adds them to the
 * suggestions list.
 *
 * @param word The word to modify.
 * @param dict The AVL tree to search for modified words.
 * @param suggestions The list to add valid modified words to.
 *
 * For each letter in the given word, every letter a-z is tried as a replacement
 * and if the modified word is found in the dictionary, it is added to the
 * suggestions list.
 */
void letterSubstitution(string word, AVLTree *dict, StrList *&suggestions)
{
    // incase the list is empty
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

/**
 * Finds words with a single letter omission and adds them to the
 * suggestions list.
 *
 * @param word The word to modify.
 * @param dict The AVL tree to search for modified words.
 * @param suggestions The list to add valid modified words to.
 *
 * For each letter in the given word, a new word is created by omitting that
 * letter and if the resulting word is found in the dictionary, it is added to
 * the suggestions list.
 */
void letterOmission(string word, AVLTree *dict, StrList *&suggestions)
{
    // incase the list is empty
    if (suggestions == nullptr)
        suggestions = new StrList();

    string dummy_word; // to prserve the original

    // k tries
    for (int i = 0; i < word.length(); i++)
    {
        dummy_word = "";
        // store the word with omitted letter
        for (int j = 0; j < word.length(); j++)
        {
            // make the new word
            if (j != i)
                dummy_word += word[j];
        }
        // if modified word exists
        if (dict->Search(dummy_word))
            suggestions->Insertion(dummy_word);
    }
}

/**
 * Finds words with a single letter insertion and adds them to the
 * suggestions list.
 *
 * @param word The word to modify.
 * @param dict The AVL tree to search for modified words.
 * @param suggestions The list to add valid modified words to.
 *
 * For each letter in the given word, and for each position in the word, a new
 * word is created by inserting a new letter at that position. If the resulting
 * word is found in the dictionary, it is added to the suggestions list.
 */
void letterInsertion(string word, AVLTree *dict, StrList *&suggestions)
{
    // incase the list is empty
    if (suggestions == nullptr)
        suggestions = new StrList();

    // 26 * k+1 tries
    for (int i = 0; i < word.length(); i++)
    {
        string original_word = word; // to prserve the original
        string dummy_word;
        for (int j = 97; j <= 122; j++)
        {
            // inserting new letter
            dummy_word =
                original_word.substr(0, i) + (char)j + original_word.substr(i);
            // if modified word exists
            if (dict->Search(dummy_word))
                suggestions->Insertion(dummy_word);
        }
    }
}

/**
 * Swaps the values of two characters.
 *
 * @param a The first character.
 * @param b The second character.
 */
void swap(char &a, char &b)
{
    char temp = a;
    a = b;
    b = temp;
}

/**
 * Finds words with a single letter reversal and adds them to the
 * suggestions list.
 *
 * @param word The word to modify.
 * @param dict The AVL tree to search for modified words.
 * @param suggestions The list to add valid modified words to.
 *
 * For each letter in the given word, adjacent characters are swapped and if
 * the resulting word is found in the dictionary, it is added to the suggestions
 * list.
 **/
void letterReversal(string word, AVLTree *dict, StrList *&suggestions)
{
    // incase the list is empty
    if (suggestions == nullptr)
        suggestions = new StrList();

    // k-1 tries
    for (int i = 0; i < word.length() - 1; i++)
    {
        string dummy_word = word; // preserve the original
        // swap the characters
        swap(dummy_word[i], dummy_word[i + 1]);
        // if modified word exists
        if (dict->Search(dummy_word))
            suggestions->Insertion(dummy_word);
    }
}
/**
 * Generates a list of suggested words by applying various word modification
 * techniques to the given word and checking against the provided dictionary.
 *
 * @param word The word to be modified and checked for suggestions.
 * @param dict The AVL tree dictionary to search for modified words.
 * @return A list of suggested words obtained by applying letter substitution,
 * omission, insertion, and reversal to the given word.
 */
StrList *modifiedWord(string word, AVLTree *dict)
{
    StrList *suggestions = nullptr;
    letterSubstitution(word, dict, suggestions);
    letterOmission(word, dict, suggestions);
    letterInsertion(word, dict, suggestions);
    letterReversal(word, dict, suggestions);
    return suggestions;
}

/**
 * Reads words from a file and inserts them into an AVL tree.
 *
 * This function opens the "dictionary.txt" file and reads each line,
 * inserting the read word into an AVL tree. If the file cannot be opened,
 * an error message is displayed. The function returns a pointer to the
 * AVL tree containing the words from the file.
 *
 * @return A pointer to an AVL tree populated with words from the file.
 */
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

/**
 * The main function is the entry point of the program. It creates an AVL tree
 * of words from a file, a queue for words being typed, and a list for the
 * contents of the text editor. It then enters a loop where it waits for a
 * character to be pressed, and depending on the character, it either inserts
 * the character into the list and queue, deletes a character from the list and
 * queue, or displays a menu of spelling suggestions if the word being typed
 * is not in the dictionary. The loop exits when the ESC key is pressed.
 */
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
        ////////////////////////////// BUG Present here!
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
                            // < b/c not appending \0
                            for (int i = 0; i < correction.length(); i++)
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