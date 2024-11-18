# assignment_04

console based notepad
author Ramalah amir

# Word Suggestion Generator

This project is a word suggestion generator that suggests alternative words based on letter substitution and omission. It uses a self-balancing binary search tree (AVLTree) to store a dictionary of words.

## Table of Contents

- [AVLTree Class](#avltree-class)
- [Word Modification Functions](#word-modification-functions)

## AVLTree Class

The `AVLTree` class represents a self-balancing binary search tree. It provides the following public methods:

- [insertTreeNode(string word)](cci:1://file:///c:/Users/Administrator/OneDrive/Desktop/university/dataStructures/assignment_04/23i2644_DSC.cpp:680:4-680:67): Inserts a new node with the given word into the tree.

  - The word is inserted into the tree such that the tree remains balanced.
  - If the word is already present in the tree, this function does nothing.
  - @param root The root of the AVL tree to insert the new word into.
  - @param word The word to insert into the tree.
  - @return The root of the AVL tree after insertion.

- `Delete(string word)`: Deletes a node with the given word from the tree.

  - If the given root node is nullptr, this function returns nullptr.
  - Otherwise, it recursively traverses the tree and deletes the node with the given word by rearranging the tree's internal pointers.
  - If the deleted node has two children, the function finds the maximum value in the left subtree of the node and replaces the node's word with it, then deletes the maximum node in the left subtree.
  - After deletion, the function rebalances the tree if necessary by rotating nodes.
  - @param root The root node of the AVL tree to delete the given word from.
  - @param word The word to delete from the AVL tree.
  - @return The root of the AVL tree after deletion. If the root node is nullptr, this function returns nullptr.

- [Search(string word)](cci:1://file:///c:/Users/Administrator/OneDrive/Desktop/university/dataStructures/assignment_04/23i2644_DSC.cpp:656:4-675:5): Searches for a given word in the AVL tree starting from the given root node.
  - @param root The root node of the AVL tree to search in.
  - @param word The word to search for.
  - @return true if the word is found in the tree, false otherwise.

## Word Modification Functions

The following functions generate word suggestions based on letter substitution and omission:

- `letterSubstitution(string word, AVLTree* dict, StrList*& suggestions)`: Generates a list of word suggestions by substituting each letter in the given word.

  - @param word The original word.
  - @param dict The AVLTree dictionary to search for word suggestions.
  - @param suggestions The list of word suggestions.

- `letterOmission(string word, AVLTree* dict, StrList*& suggestions)`: Generates a list of word suggestions by omitting each letter in the given word.
  - @param word The original word.
  - @param dict The AVLTree dictionary to search for word suggestions.
  - @param suggestions The list of word suggestions.
