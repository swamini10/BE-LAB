//Design and implement Parallel Breadth First Search based on existing 
//algorithms using OpenMP. Use a Tree or an undirected graph for BFS.
#include <iostream>
#include <vector>
#include <queue>
#include <omp.h>
using namespace std;
class node {
public:
    int data;
    node *left, *right;

    node(int val) {
        data = val;
        left = right = NULL;
    }
};
class Breadthfs {
public:
    node* insert(node*, int);
    void parallel_bfs(node*);
};
// Insert node (level order)
node* Breadthfs::insert(node* root, int data) {
    if (!root) return new node(data);
    queue<node*> q;
    q.push(root);
    while (!q.empty()) {
        node* temp = q.front();
        q.pop();
        if (!temp->left) {
            temp->left = new node(data);
            return root;
        } else {
            q.push(temp->left);
        }
        if (!temp->right) {
            temp->right = new node(data);
            return root;
        } else {
            q.push(temp->right);
        }
    }
    return root;
}
// Parallel BFS
void Breadthfs::parallel_bfs(node* root) {
    if (!root) return;
    vector<node*> current_level;
    current_level.push_back(root);
    while (!current_level.empty()) {
        vector<node*> next_level;
        #pragma omp parallel for
        for (int i = 0; i < (int)current_level.size(); i++) {
            node* curr = current_level[i];
            // Safe printing
            #pragma omp critical
            cout << curr->data << " ";
            // Add children safely
            if (curr->left) {
                #pragma omp critical
                next_level.push_back(curr->left);
            }
            if (curr->right) {
                #pragma omp critical
                next_level.push_back(curr->right);
            }
        }
        current_level = next_level;
    }
}
// Main function
int main() {
    Breadthfs obj;
    node* root = NULL;

    int data;
    char ans;

    do {
        cout << "Enter data: ";
        cin >> data;
        root = obj.insert(root, data);
        cout << "Insert more? (y/n): ";
        cin >> ans;
    } while (ans == 'y' || ans == 'Y');
    cout << "\nParallel BFS Traversal: ";
    obj.parallel_bfs(root);
    cout << endl;
    return 0;
}

/*
Aim: To implement a binary tree and perform parallel Breadth-First Search (BFS) traversal using OpenMP in C++.
This program:
Builds a binary tree using level-order insertion.
Traverses the tree using BFS (level order traversal).
Uses OpenMP to perform traversal in parallel at each level.
🧱 Node Structure
A node class is used to represent each tree node.
It contains:
data → stores integer value
left → pointer to left child
right → pointer to right child
Constructor initializes node values.
🌿 Tree Construction (Insert Function)
The function insert() builds the tree in level order.
Steps:
If tree is empty → create root node.
Use a queue to traverse level by level.
Insert new node at the first available position:
First check left child
Then right child
This ensures the tree remains complete binary tree structure.
🚀 Parallel BFS Traversal
Function: parallel_bfs()
Uses a vector to store nodes at each level.
🔄 Working:
Start with root node in current_level.
While nodes exist:
Create next_level vector.
Use:
#pragma omp parallel for
to process nodes of the same level in parallel.
For each node:
Print node value (protected using critical section).
Add left and right children to next_level.
Move to next level.
⚙️ OpenMP Usage
#pragma omp parallel for → divides loop iterations among threads.
#pragma omp critical → ensures:
No mixed output while printing
Safe updates to shared vector
📥 Input Process
User enters node values one by one.
After each input, user decides:
y → continue inserting
n → stop insertion
📤 Output
Displays tree nodes in BFS order (level-wise).
Example:
Parallel BFS Traversal: 1 2 3 4 5
📌 Key Concepts Used
Binary Tree
Queue (for insertion)
Vector (for level storage)
Breadth-First Search (BFS)
Parallel Programming (OpenMP)
⚠️ Important Note
Output order is mostly consistent, but slight variation may occur due to parallel execution.
This improves performance for large trees.
🎯 Conclusion
This program demonstrates how BFS traversal of a binary tree can be parallelized using OpenMP, making execution faster by processing each level of the tree simultaneously using multiple threads

*/