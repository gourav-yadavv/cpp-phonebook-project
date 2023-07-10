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

## Operations and Time Complexity
- Insertion: Inserting a new contact into the AVL tree takes O(log n) time complexity on average, where n is the number of contacts in the tree. The AVL tree automatically performs rotations and re-balancing if necessary to maintain its height balance.
- Deletion: Deleting a contact from the AVL tree also takes O(log n) time complexity on average. Similar to insertion, the AVL tree adjusts its structure to maintain balance after the deletion operation.
- Search: Searching for a contact by name or phone number in the AVL tree has a time complexity of O(log n) on average. The tree's balanced nature allows for efficient traversal, narrowing down the search path with each comparison.
- Prefix Search: Performing a prefix search to find contacts with a given prefix takes O(k + m) time complexity, where k is the number of contacts matching the prefix and m is the number of characters in the prefix. The AVL tree optimizes the search by traversing only the relevant subtree.
- Display All Contacts: Displaying all contacts in the AVL tree requires an in-order traversal, which visits each node once. The time complexity for this operation is O(n), where n is the number of contacts in the tree.

- Display Upcoming Birthdays: Displaying upcoming birthdays involves traversing the AVL tree and comparing each contact's birthday with the current date. The time complexity depends on the number of contacts and the number of months to consider. However, since the AVL tree is already sorted by name, the traversal is efficient, resulting in a time complexity of O(n), where n is the number of contacts.



