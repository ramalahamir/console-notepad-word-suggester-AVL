# ✨ Console Notepad – Word Suggestion Generator
Author: Ramalah Amir 

## 📌 Overview
This project is a console-based word suggestion tool that mimics a simple notepad. It uses a self-balancing AVL Tree to store a dictionary of valid words and suggests similar alternatives when a word is not found, using letter substitution and letter omission techniques.

## 🌲 AVLTree Class
Implements a self-balancing Binary Search Tree for efficient storage, search, and modification of words.

## 🔧 Public Methods:
### 🔹 insertTreeNode(string word)
- Inserts a new word into the tree while maintaining AVL balance.
- Skips insertion if the word already exists.

### 🔹 Delete(string word)
- Removes a word from the tree while preserving AVL balance.
- Handles nodes with 0, 1, or 2 children.
- Uses in-order predecessor for replacing nodes with two children.
- Rebalances after deletion.

### 🔹 Search(string word)
- Checks if a word exists in the tree.
- Returns true if found, otherwise false.

## 🧠 Word Suggestion Logic
- Suggests words based on modification strategies if a search fails.

### 🔸 letterSubstitution(string word, AVLTree* dict, StrList*& suggestions)
- Replaces each letter of the word (one at a time) with all alphabet letters.
- Checks if the resulting word exists in the dictionary.
- Adds valid results to suggestions.

### 🔸 letterOmission(string word, AVLTree* dict, StrList*& suggestions)
- Removes one letter at a time from the original word.
- Checks resulting word in the dictionary.
- Adds matches to suggestions.

# 🧩 Features Summary
- 📂 Loads and stores a dictionary of words in an AVL Tree.
- 🔍 Fast search, insertion, and deletion (O(log n) complexity).
- ✏️ Suggests similar words if an entry isn't found.
- 🧠 Uses intelligent algorithms for substitution and omission.
- 🖥️ Console-based interface, suitable for small editors or search helpers.
