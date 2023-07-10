#include <iostream>
#include <string>
#include <algorithm>
#include <ctime>
#include <vector>
using namespace std;

struct Contact
{
    string name;
    string phoneNumber;
    string birthday;

    Contact(const string &name, const string &phoneNumber, const string &birthday)
        : name(name), phoneNumber(phoneNumber), birthday(birthday) {}
};

class AVLNode
{
public:
    Contact contact;
    AVLNode *left;
    AVLNode *right;
    int height;

    AVLNode(const Contact &contact)
        : contact(contact), left(nullptr), right(nullptr), height(1) {}
};

class Phonebook
{
private:
    AVLNode *root;

    int getHeight(AVLNode *node)
    {
        if (node == nullptr)
        {
            return 0;
        }
        return node->height;
    }

    int getBalanceFactor(AVLNode *node)
    {
        if (node == nullptr)
        {
            return 0;
        }
        return getHeight(node->left) - getHeight(node->right);
    }

    AVLNode *rotateLeft(AVLNode *node)
    {
        AVLNode *newRoot = node->right;
        AVLNode *newRootLeftChild = newRoot->left;

        newRoot->left = node;
        node->right = newRootLeftChild;

        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        newRoot->height = 1 + max(getHeight(newRoot->left), getHeight(newRoot->right));

        return newRoot;
    }

    AVLNode *rotateRight(AVLNode *node)
    {
        AVLNode *newRoot = node->left;
        AVLNode *newRootRightChild = newRoot->right;

        newRoot->right = node;
        node->left = newRootRightChild;

        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        newRoot->height = 1 + max(getHeight(newRoot->left), getHeight(newRoot->right));

        return newRoot;
    }

    AVLNode *insertNode(AVLNode *node, const Contact &contact)
    {
        if (node == nullptr)
        {
            return new AVLNode(contact);
        }

        if (contact.name < node->contact.name)
        {
            node->left = insertNode(node->left, contact);
        }
        else if (contact.name > node->contact.name)
        {
            node->right = insertNode(node->right, contact);
        }
        else
        {
            // Duplicate contact names are not allowed
            return node;
        }

        node->height = 1 + max(getHeight(node->left), getHeight(node->right));

        int balanceFactor = getBalanceFactor(node);

        // Left-Left case
        if (balanceFactor > 1 && contact.name < node->left->contact.name)
        {
            return rotateRight(node);
        }

        // Right-Right case
        if (balanceFactor < -1 && contact.name > node->right->contact.name)
        {
            return rotateLeft(node);
        }

        // Left-Right case
        if (balanceFactor > 1 && contact.name > node->left->contact.name)
        {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        // Right-Left case
        if (balanceFactor < -1 && contact.name < node->right->contact.name)
        {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    AVLNode *findMinNode(AVLNode *node)
    {
        while (node->left != nullptr)
        {
            node = node->left;
        }
        return node;
    }

    AVLNode *deleteNode(AVLNode *node, const string &name)
    {
        if (node == nullptr)
        {
            return nullptr;
        }

        if (name < node->contact.name)
        {
            node->left = deleteNode(node->left, name);
        }
        else if (name > node->contact.name)
        {
            node->right = deleteNode(node->right, name);
        }
        else
        {
            if (node->left == nullptr && node->right == nullptr)
            {
                delete node;
                return nullptr;
            }
            else if (node->left == nullptr)
            {
                AVLNode *temp = node;
                node = node->right;
                delete temp;
            }
            else if (node->right == nullptr)
            {
                AVLNode *temp = node;
                node = node->left;
                delete temp;
            }
            else
            {
                AVLNode *minRight = findMinNode(node->right);
                node->contact = minRight->contact;
                node->right = deleteNode(node->right, minRight->contact.name);
            }
        }

        if (node == nullptr)
        {
            return node;
        }

        node->height = 1 + max(getHeight(node->left), getHeight(node->right));

        int balanceFactor = getBalanceFactor(node);

        if (balanceFactor > 1)
        {
            // Left-Left or Left-Right case
            if (getBalanceFactor(node->left) >= 0)
            {
                return rotateRight(node);
            }
            else
            {
                node->left = rotateLeft(node->left);
                return rotateRight(node);
            }
        }
        else if (balanceFactor < -1)
        {
            // Right-Right or Right-Left case
            if (getBalanceFactor(node->right) <= 0)
            {
                return rotateLeft(node);
            }
            else
            {
                node->right = rotateRight(node->right);
                return rotateLeft(node);
            }
        }

        return node;
    }

    void prefixSearchNode(AVLNode *node, const string &prefix)
    {
        if (node == nullptr)
        {
            return;
        }

        if (node->contact.name.find(prefix) == 0)
        {
            cout << "Name: " << node->contact.name << ", Phone Number: " << node->contact.phoneNumber << endl;
        }

        if (node->contact.name.compare(0, prefix.length(), prefix) >= 0)
        {
            prefixSearchNode(node->left, prefix);
        }

        prefixSearchNode(node->right, prefix);
    }

    bool isDuplicateNode(AVLNode *node, const string &name, const string &phoneNumber)
    {
        if (node == nullptr)
        {
            return false;
        }

        if (node->contact.name == name || node->contact.phoneNumber == phoneNumber)
        {
            return true;
        }

        if (name < node->contact.name)
        {
            return isDuplicateNode(node->left, name, phoneNumber);
        }
        else
        {
            return isDuplicateNode(node->right, name, phoneNumber);
        }
    }

    void displayInOrder(AVLNode *node)
    {
        if (node != nullptr)
        {
            displayInOrder(node->left);
            cout << "Name: " << node->contact.name << ", Phone Number: " << node->contact.phoneNumber
                 << ", Birthdate: " << node->contact.birthday << endl;
            displayInOrder(node->right);
        }
    }

    bool searchContactNode(AVLNode *node, const string &name)
    {
        if (node == nullptr)
        {
            return false;
        }

        if (node->contact.name == name)
        {
            return true;
        }

        if (name < node->contact.name)
        {
            return searchContactNode(node->left, name);
        }
        else
        {
            return searchContactNode(node->right, name);
        }
    }

    bool searchPhoneNumberNode(AVLNode *node, const string &phoneNumber)
    {
        if (node == nullptr)
        {
            return false;
        }

        if (node->contact.phoneNumber == phoneNumber)
        {
            return true;
        }

        if (phoneNumber < node->contact.phoneNumber)
        {
            return searchPhoneNumberNode(node->left, phoneNumber);
        }
        else
        {
            return searchPhoneNumberNode(node->right, phoneNumber);
        }
    }

    void displayUpcomingBirthdays()
    {
        time_t now = time(nullptr);
        tm *current_time = localtime(&now);
        int current_month = current_time->tm_mon + 1; // tm_mon ranges from 0 to 11
        int current_day = current_time->tm_mday;


        for (int i = 1; i <= 12; i++) // Iterate through all possible months
        {
            for (AVLNode *node : getAllNodes(root))
            {
                // DD/MM/YYYY
                int contact_month = stoi(node->contact.birthday.substr(3, 2));
                int contact_day = stoi(node->contact.birthday.substr(0, 2));

                if (contact_month == i && (contact_day >= current_day || contact_month > current_month))
                {
                    cout << node->contact.name << "'s birthday comes on: " << node->contact.birthday << endl;
                }
            }
        }
    }

    void inorderTraversal(AVLNode *node, vector<AVLNode *> &nodes)
    {
        if (node != nullptr)
        {
            inorderTraversal(node->left, nodes);
            nodes.push_back(node);
            inorderTraversal(node->right, nodes);
        }
    }

    vector<AVLNode *> getAllNodes(AVLNode *node)
    {
        vector<AVLNode *> nodes;
        inorderTraversal(node, nodes);
        return nodes;
    }

public:
    Phonebook() : root(nullptr) {}

    void addContact(const string &name, const string &phoneNumber, const string &birthDate)
    {
        string formattedName = name;
        formattedName.erase(remove(formattedName.begin(), formattedName.end(), ' '), formattedName.end());

        Contact contact(formattedName, phoneNumber, birthDate);
        root = insertNode(root, contact);
    }

    bool searchContactbyName(const string &name)
    {
        return searchContactNode(root, name);
    }

    bool searchContactbyNumber(const string &num)
    {
        return searchPhoneNumberNode(root, num);
    }

    void deleteContact(const string &name)
    {
        string formattedName = name;
        formattedName.erase(remove(formattedName.begin(), formattedName.end(), ' '), formattedName.end());
        if (searchContactNode(root, name))
        {
            root = deleteNode(root, formattedName);
            cout << "DELETED SUCCESSFULLY!" << endl;
        }
        else
        {
            cout << "CONTACT NOT FOUND!" << endl;
        }
    }

    void displayAllContacts()
    {
        displayInOrder(root);
    }

    void prefixSearch(const string &prefix)
    {
        prefixSearchNode(root, prefix);
    }

    bool isDuplicate(const string &name, const string &phoneNumber)
    {
        return isDuplicateNode(root, name, phoneNumber);
    }

    void displayBirthdays()
    {
        displayUpcomingBirthdays();
    }
};

int main()
{
    Phonebook phonebook;

    int choice;
    string name, phoneNumber, prefix, birthday;

    while (true)
    {
        cout << "Contact List Actions\n";
        cout << "1. Add a Contact\n";
        cout << "2. Delete a Contact\n";
        cout << "3. Search for a Contact\n";
        cout << "4. Prefix Search for Contacts\n";
        cout << "5. Display All Contacts\n";
        cout << "6. Display Upcoming Birthdays\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter contact name: ";
            cin.ignore(); // Ignore any remaining newline characters in the input stream
            getline(cin, name);

            cout << "Enter contact number: ";
            getline(cin, phoneNumber);

            cout << "Enter contact birthday (DD/MM/YYYY): ";
            getline(cin, birthday);

            if (phonebook.isDuplicate(name, phoneNumber))
            {
                cout << "Contact already exists!\n";
            }
            else
            {
                phonebook.addContact(name, phoneNumber, birthday);
                cout << "Contact added successfully!\n";
            }
            break;

        case 2:
            cout << "Enter contact name to delete: ";
            cin >> name;
            phonebook.deleteContact(name);
            break;

        case 3:
            cout << "1. Search contact by name\n";
            cout << "2. Search contact by phone number\n";
            int searchChoice;
            cout << "Enter your choice for searching: ";
            cin >> searchChoice;

            switch (searchChoice)
            {
            case 1:
                cin >> name;
                if (phonebook.searchContactbyName(name))
                {
                    cout << "Contact found!\n";
                }
                else
                {
                    cout << "Contact not found!\n";
                }
                break;
            case 2:
                cin >> phoneNumber;
                if (phonebook.searchContactbyNumber(phoneNumber))
                {
                    cout << "Contact found!\n";
                }
                else
                {
                    cout << "Contact not found!\n";
                }
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
                break;
            }
            cin.ignore();
            cout << endl;
            break; // Add break statement to exit the switch statement

        case 4:
            cout << "Enter prefix to search: ";
            cin >> prefix;
            phonebook.prefixSearch(prefix);
            break;

        case 5:
            cout << "All Contacts:\n";
            phonebook.displayAllContacts();
            break;
        case 6:
            cout << "Upcoming Birthdays:\n";
            phonebook.displayBirthdays();
            break;
        case 7:
            cout << "Exiting Phonebook...\n";
            return 0;

        default:
            cout << "Invalid choice! Please try again.\n";
            break;
        }

        cout << endl;
    }

    return 0;
}

/*Both AVL trees and red-black trees are self-balancing binary search trees that provide efficient operations for maintaining a sorted order and searching. Here's a detailed comparison of these two data structures:

Balance Factor:

AVL trees use a balance factor, which is the difference between the heights of the left and right subtrees, to ensure the tree remains balanced. The balance factor of any node in an AVL tree must be either -1, 0, or 1.
Red-black trees use color properties (red or black) on nodes to maintain balance. The color properties ensure that no path from the root to a leaf has more than twice the length of any other path.
Balancing Mechanism:

AVL trees perform more rotations than red-black trees to maintain balance. This results in faster search operations but slower insertion and deletion operations compared to red-black trees.
Red-black trees have a simpler balancing mechanism that requires fewer rotations than AVL trees. This makes them slightly more efficient for insertion and deletion operations but can lead to slower search operations compared to AVL trees.
Time Complexity:

Both AVL trees and red-black trees provide efficient time complexities for operations:
Search: O(log n)
Insertion: O(log n)
Deletion: O(log n)
However, AVL trees typically have faster search times due to their more rigid balance criteria, which guarantees a maximum height difference of 1 between subtrees.
Space Overhead:

Red-black trees require additional space to store color information (typically one extra bit per node). This slightly increases the memory overhead compared to AVL trees.
Use Cases:

AVL trees are generally preferred when the application requires faster search times, such as in databases or applications with more frequent read operations.
Red-black trees are often chosen when a good balance between search, insertion, and deletion operations is needed, such as in file systems or memory management.
In summary, the choice between AVL trees and red-black trees depends on the specific requirements of your application. If you prioritize faster search times and can tolerate slightly slower insertion and deletion operations, AVL trees may be the better choice. On the other hand, if you seek a balance between all operations and prefer a simpler balancing mechanism, red-black trees are a good option. Both data structures offer efficient performance for small to moderate-sized phonebooks like the one you described with a maximum of 500 contacts.*/