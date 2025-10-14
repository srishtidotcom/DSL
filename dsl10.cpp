
#include <iostream>
#include <string>
using namespace std;

// Node structure for file/folder
struct Node {
    string name;
    bool isFile;   // true if it's a file, false if it's a folder
    Node* left;    // first child
    Node* right;   // next sibling

    Node(string n, bool file) : name(n), isFile(file), left(nullptr), right(nullptr) {}
};

// Function to print tree in hierarchical manner
void printTree(Node* root, string indent = "") {
    if (!root) return;
    cout << indent << (root->isFile ? "File: " : "Folder: ") << root->name << endl;
    printTree(root->left, indent + "    ");  // children
    printTree(root->right, indent);          // siblings
}

int main() {
    // Creating the tree structure
    Node* folder1 = new Node("Folder1", false);

    Node* folderA = new Node("FolderA", false);
    Node* folderB = new Node("FolderB", false);

    Node* fileA1 = new Node("A1", true);
    Node* fileA2 = new Node("A2", true);

    Node* fileB1 = new Node("B1", true);
    Node* fileB2 = new Node("B2", true);

    // Linking children and siblings
    folder1->left = folderA;        // Folder1's first child is FolderA
    folderA->right = folderB;       // FolderA's sibling is FolderB

    folderA->left = fileA1;         // FolderA's first child is A1
    fileA1->right = fileA2;         // A1's sibling is A2

    folderB->left = fileB1;         // FolderB's first child is B1
    fileB1->right = fileB2;         // B1's sibling is B2

    // Print the structure
    printTree(folder1);

    return 0;
}

 