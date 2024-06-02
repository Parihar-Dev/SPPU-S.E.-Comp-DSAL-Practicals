/*
A Dictionary stores keywords & its meanings. Now provide facility for adding new keywords, deleting keywords, & updating values of any entry.
Also provide facility to display whole data sorted in ascending/ Descending order.Also find how many maximum comparisons may require for finding
any keyword. Use Height Balance tree and find the complexity for finding the keyword.
*/

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

struct Node {
    string keyword;
    string meaning;
    Node* left;
    Node* right;
    int height;
};

class Dictionary {
private:
    Node* root;

    int getHeight(Node* node) {
        if (node == nullptr)
            return 0;
        return node->height;
    }

    int getBalanceFactor(Node* node) {
        if (node == nullptr)
            return 0;
        return getHeight(node->left) - getHeight(node->right);
    }

    Node* rotateRight(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

        return x;
    }

    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

        return y;
    }

    Node* insert(Node* node, string keyword, string meaning) {
        if (node == nullptr) {
            Node* newNode = new Node();
            newNode->keyword = keyword;
            newNode->meaning = meaning;
            newNode->left = nullptr;
            newNode->right = nullptr;
            newNode->height = 1;
            return newNode;
        }

        if (keyword < node->keyword)
            node->left = insert(node->left, keyword, meaning);
        else if (keyword > node->keyword)
            node->right = insert(node->right, keyword, meaning);
        else {
            // Keyword already exists, update meaning
            node->meaning = meaning;
            return node;
        }

        node->height = 1 + max(getHeight(node->left), getHeight(node->right));

        int balance = getBalanceFactor(node);

        if (balance > 1 && keyword < node->left->keyword)
            return rotateRight(node);
        if (balance < -1 && keyword > node->right->keyword)
            return rotateLeft(node);
        if (balance > 1 && keyword > node->left->keyword) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        if (balance < -1 && keyword < node->right->keyword) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current && current->left != nullptr)
            current = current->left;
        return current;
    }

    Node* deleteNode(Node* root, string keyword) {
        if (root == nullptr)
            return root;

        if (keyword < root->keyword)
            root->left = deleteNode(root->left, keyword);
        else if (keyword > root->keyword)
            root->right = deleteNode(root->right, keyword);
        else {
            if (root->left == nullptr || root->right == nullptr) {
                Node* temp = root->left ? root->left : root->right;
                if (temp == nullptr) {
                    temp = root;
                    root = nullptr;
                } else
                    *root = *temp;
                delete temp;
            } else {
                Node* temp = minValueNode(root->right);
                root->keyword = temp->keyword;
                root->meaning = temp->meaning;
                root->right = deleteNode(root->right, temp->keyword);
            }
        }

        if (root == nullptr)
            return root;

        root->height = 1 + max(getHeight(root->left), getHeight(root->right));

        int balance = getBalanceFactor(root);

        if (balance > 1 && getBalanceFactor(root->left) >= 0)
            return rotateRight(root);
        if (balance > 1 && getBalanceFactor(root->left) < 0) {
            root->left = rotateLeft(root->left);
            return rotateRight(root);
        }
        if (balance < -1 && getBalanceFactor(root->right) <= 0)
            return rotateLeft(root);
        if (balance < -1 && getBalanceFactor(root->right) > 0) {
            root->right = rotateRight(root->right);
            return rotateLeft(root);
        }

        return root;
    }

    void inorderTraversal(Node* node) {
        if (node != nullptr) {
            inorderTraversal(node->left);
            cout << node->keyword << " : " << node->meaning << endl;
            inorderTraversal(node->right);
        }
    }

public:
    Dictionary() {
        root = nullptr;
    }

    void insertKeyword(string keyword, string meaning) {
        root = insert(root, keyword, meaning);
    }

    void deleteKeyword(string keyword) {
        root = deleteNode(root, keyword);
    }

    void displayAscending() {
        inorderTraversal(root);
    }

    void displayDescending() {
        // Traversal in reverse order
        reverseInorderTraversal(root);
    }

    void reverseInorderTraversal(Node* node) {
        if (node != nullptr) {
            reverseInorderTraversal(node->right);
            cout << node->keyword << " : " << node->meaning << endl;
            reverseInorderTraversal(node->left);
        }
    }

    Node* search(Node* root, string keyword, int& comparisons) {
        comparisons++;
        if (root == nullptr || root->keyword == keyword)
            return root;

        if (root->keyword < keyword)
            return search(root->right, keyword, comparisons);

        return search(root->left, keyword, comparisons);
    }

    int findMaxComparisons(string keyword) {
        int comparisons = 0;
        search(root, keyword, comparisons);
        return comparisons;
    }
};

int main()
{
    Dictionary mydict;
    int choice;
    string key,value;
    do
    {
        cout<<"\n----------    MENU    ----------";
        cout<<"\n1.Add an entry";
        cout<<"\n2.Remove an entry";
        cout<<"\n3.Find an entry";
        cout<<"\n4.Update an entry";
        cout<<"\n5.Display all entries";
        cout<<"\n6.Exit";
        cout<<"Enter your choice : ";
        cin>>choice;

        switch(choice)
        {
            case 1 :
                cout<<"Enter Key : ";
                cin>>key;
                cout<<"Enter Value : ";
                cin>>value;
                mydict.insertKeyword(key,value);
                cout<<"Entry Added Successfully!\n";
            break;

            case 2:
                cout<<"Enter the key to remove : ";
                cin>>key;
                mydict.deleteKeyword(key);
                cout<<"Node deleted successfully!";
            break;

            case 3:
                cout<<"Enter the key you want to search : ";
                cin>>key;
                cout<<"Comparison Count : "<<mydict.findMaxComparisons(key);
            break;

            case 4:
                cout<<"\nEnter the key to update : ";
                cin>>key;
                cout<<"\nEnter the new value : ";
                cin>>value;
            break;

            case 5:
                cout<<"Ascending Order : \n";
                mydict.displayAscending();
                cout<<"Descending Order : \n";
                mydict.displayDescending();
            break;

            case 6 :
                cout<<"Exiting the Program";
            break;

            default:
                cout<<"Invalid choice";
            break;

        }
    } while (choice != 6);
    return 0;
}
