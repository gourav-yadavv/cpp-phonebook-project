# cpp-phonebook-project
A C++ phonebook application for managing and organizing contacts efficiently using AVL Tree (self-balancing tree).
Phonebook with AVL Trees is a command-line application written in C++ that allows you to manage a list of contacts using AVL tree data structure. With the help of AVL trees, the phonebook ensures efficient searching, insertion, deletion, and sorting of contacts.

## Features

- Add a new contact with name, phone number, and birthday
- Delete a contact by name
- Search for a contact by name or phone number
- Perform prefix search to find contacts with a given prefix
- Display all contacts
- Display upcoming birthdays
- Update the phone number or birthday of an existing contact

## AVL Trees

The Phonebook utilizes AVL trees, a self-balancing binary search tree, to store and organize the contacts. AVL trees maintain balance through rotations, which ensures efficient search and insertion operations even in the presence of frequent modifications.

## Left Rotation
A left rotation is a restructuring operation performed on a node in the AVL tree. It aims to restore balance to the tree by adjusting the positions of nodes. The left rotation involves promoting the right child of the current node as the new root, while the current node becomes the left child of the new root.

Here's a step-by-step breakdown of the left rotation process:

1. Identify the node on which the left rotation is to be performed. Let's call this node A.
1. Assign the right child of A as the new root. Let's call this node B.
1. Make the left child of B the right child of A.
1. Update the height of A by calculating the maximum height between its left and right subtrees plus one.
1. Update the height of B by calculating the maximum height between its left and right subtrees plus one.
1. Return B as the new root of the rotated subtree.
1. The purpose of the left rotation is to balance the tree when a node becomes right-heavy. By performing the left rotation, we move a node from the right subtree to the left subtree, which can help maintain the AVL tree's balance condition.

## Right Rotation
A right rotation is the counterpart of the left rotation and is used to balance the tree when a node becomes left-heavy. It involves promoting the left child of the current node as the new root, while the current node becomes the right child of the new root.

Here's a step-by-step breakdown of the right rotation process:

1. Identify the node on which the right rotation is to be performed. Let's call this node A.
1. Assign the left child of A as the new root. Let's call this node B.
1. Make the right child of B the left child of A.
1. Update the height of A by calculating the maximum height between its left and right subtrees plus one.
1. Update the height of B by calculating the maximum height between its left and right subtrees plus one.
1. Return B as the new root of the rotated subtree.
1. The right rotation helps in maintaining the balance of the AVL tree by moving a node from the left subtree to the right subtree.

## Note 
It's important to remember that rotations can be performed multiple times in succession, depending on the specific situation, to restore the balance of the tree. The rotations help in maintaining the AVL property, which ensures that the tree's height remains logarithmic in relation to the number of nodes, resulting in efficient search and insertion operations.

## Find Minimum Node
The findMinNode function in AVL trees is used to find the node with the minimum value in a given subtree. It is commonly used during the deletion operation when we need to find the successor of a node.

Here's how the findMinNode function works:

1. Start with the given node, which represents the root of the subtree.
1. Iterate through the left children of each node until we reach a node that does not have a left child (i.e., node->left == nullptr).
1. Return the current node, which represents the node with the minimum value in the subtree.

In an AVL tree, the leftmost node (the node with the smallest value) will always be the leftmost child of the leftmost child, and so on. Therefore, by traversing the left child pointers until reaching a null left child, we can find the node with the minimum value in the subtree.

### In AVL trees, the Left-Left and Right-Right cases, as well as the Left-Right and Right-Left cases, are rotation operations performed to maintain the balance of the tree when it becomes unbalanced due to node insertions or deletions.

Let's explore each case in detail:

1. Left-Left Case:

- Condition: The left subtree of the left child of a node is higher by 2 or more levels compared to the right subtree of the left child.
- Situation: The left subtree of the left child is too heavy.
- Solution: To restore balance, a right rotation is performed.
- Process: The left child becomes the new root of the subtree, and the original root becomes the right child of the new root. The right subtree of the new root remains unchanged.
- Effect: The heights of both the left and right subtrees are adjusted, and the overall balance of the tree is restored.

2. Right-Right Case:

- Condition: The right subtree of the right child of a node is higher by 2 or more levels compared to the left subtree of the right child.
- Situation: The right subtree of the right child is too heavy.
- Solution: To restore balance, a left rotation is performed.
- Process: The right child becomes the new root of the subtree, and the original root becomes the left child of the new root. The left subtree of the new root remains unchanged.
- Effect: The heights of both the left and right subtrees are adjusted, and the overall balance of the tree is restored.

3. Left-Right Case:

- Condition: The right subtree of the left child of a node is higher by 2 or more levels compared to the left subtree of the right child.
- Situation: The right subtree of the left child is too heavy.
- Solution: To restore balance, a left rotation is performed on the left child, followed by a right rotation on the original node.
- Process: First, a left rotation is performed on the left child. Then, a right rotation is performed on the original node. This sequence of rotations brings the tree into a balanced state.
- Effect: The heights of both the left and right subtrees are adjusted, and the overall balance of the tree is restored.

4. Right-Left Case:

- Condition: The left subtree of the right child of a node is higher by 2 or more levels compared to the right subtree of the left child.
- Situation: The left subtree of the right child is too heavy.
- Solution: To restore balance, a right rotation is performed on the right child, followed by a left rotation on the original node.
- Process: First, a right rotation is performed on the right child. Then, a left rotation is performed on the original node. This sequence of rotations brings the tree into a balanced state.
- Effect: The heights of both the left and right subtrees are adjusted, and the overall balance of the tree is restored.

These rotation operations ensure that the AVL tree maintains its balanced property, where the heights of the left and right subtrees of each node differ by at most 1. By performing these rotations when necessary, the tree avoids becoming skewed and maintains efficient search, insertion, and deletion operations with a time complexity of O(log n).

## Prefix Search 
The prefixSearchNode function performs a prefix search in the AVL tree. It takes a node pointer and a prefix string as parameters. Here's how the prefix search is implemented:

1. If the current node is nullptr, which means we have reached the end of the subtree, we return and stop the recursion.

1. We check if the name of the contact stored in the current node starts with the given prefix. If it does, we print the contact's name and phone number, indicating a match.

1. We compare the prefix with the beginning of the contact's name. If the prefix is less than or equal to the contact's name (lexicographically), we recursively call the prefixSearchNode function on the left subtree of the current node. This is because any contact with a name greater than or equal to the prefix will be found in the left subtree due to the properties of a binary search tree.

1. Regardless of the previous condition, we always recursively call the prefixSearchNode function on the right subtree of the current node. This is because there may be contacts with names that start with the prefix in the right subtree.

The prefix search feature is a valuable functionality of the phone book project. It allows users to find contacts by typing a partial name or prefix, and the program returns all contacts whose names match the given prefix. This feature enables quick and efficient search based on partial names, making it convenient for users with large contact lists.

## Operations and Time Complexity
- Insertion: Inserting a new contact into the AVL tree takes O(log n) time complexity on average, where n is the number of contacts in the tree. The AVL tree automatically performs rotations and re-balancing if necessary to maintain its height balance.
- Deletion: Deleting a contact from the AVL tree also takes O(log n) time complexity on average. Similar to insertion, the AVL tree adjusts its structure to maintain balance after the deletion operation.
- Search: Searching for a contact by name or phone number in the AVL tree has a time complexity of O(log n) on average. The tree's balanced nature allows for efficient traversal, narrowing down the search path with each comparison.
- Prefix Search: Performing a prefix search to find contacts with a given prefix takes O(k + m) time complexity, where k is the number of contacts matching the prefix and m is the number of characters in the prefix. The AVL tree optimizes the search by traversing only the relevant subtree.
- Display All Contacts: Displaying all contacts in the AVL tree requires an in-order traversal, which visits each node once. The time complexity for this operation is O(n), where n is the number of contacts in the tree.

- Display Upcoming Birthdays: Displaying upcoming birthdays involves traversing the AVL tree and comparing each contact's birthday with the current date. The time complexity depends on the number of contacts and the number of months to consider. However, since the AVL tree is already sorted by name, the traversal is efficient, resulting in a time complexity of O(n), where n is the number of contacts.



