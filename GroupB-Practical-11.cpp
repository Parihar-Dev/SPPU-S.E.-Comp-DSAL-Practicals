/*
A Dictionary stores keywords & its meanings. Now provide facility for adding new keywords, deleting keywords, & updating values of any entry.
Also provide facility to display whole data sorted in ascending/ Descending order, Also we have to find how many maximum comparisons may
require for finding any keyword. Use binary search tree for implementation.
*/

#include<iostream>
#include<string>
using namespace std;

class node
{
    public:
        string key;
        string value;
        node *left;
        node *right;
};

class Dictionary
{
    public:
        int count = 0;
        node *root;
        Dictionary()
        {
            root = NULL;
        }
        void create();
        void insert(node*,node*);
        node* inordersucc(node*);
        node* remove(node*,string);
        node* search(string,node*);
        void update(string,string);
        void display(node*);
        int get_count()const
        {
            return count;
        }
};

void Dictionary :: create()
{
    node *temp;
    char choice;
    do
    {
        temp = new node;

        cout<<"Enter the key for the entry : ";
        cin>>temp->key;
        cout<<"Enter the value for the entry :  ";
        cin>>temp->value;

        temp->left = NULL;
        temp->right = NULL;

        if (root == NULL)
        {
            root = temp;
        }
        else
            insert(root,temp);
        
        cout<<"Do you want to add more nodes (y/n) : ";
        cin>>choice;
    } while (choice == 'y');
}

void Dictionary :: insert(node *root, node *temp)
{
    if (temp->key < root->key)
    {
        if (root->left == NULL)
            root->left = temp;
        else
            insert(root->left,temp);
    }
    else
    {
        if (root->right == NULL)
            root->right = temp;
        else
            insert(root->right,temp);
    }
}

node* Dictionary :: inordersucc(node *root)
{
    node *curr = root;
    while(curr && curr->left != NULL)
    {
        curr = curr->left;
    }
    return curr;
}


node* Dictionary :: remove(node *root, string key)
{
    if (root == NULL)
            return root;

    if (key < root->key)
        root->left = remove(root->left, key);
    else if (key > root->key)
        root->right = remove(root->right, key);
    else 
    {
        if (root->left == NULL && root->right == NULL)
        {
            node *temp = root;
            root = NULL;
            delete temp;
        }
        else if (root->left == NULL)
        {
            node *temp = root->right;
            *root = *temp;
            delete temp;
        }
        else if (root->right == NULL)
        {
            node *temp = root->left;
            *root = *temp;
            delete temp;
        }
        else
        {
            node *temp = inordersucc(root->right);
            root->key = temp->key;
            root->value = temp->value;
            root->right = remove(root->right,temp->key);
        }
    }
}

node* Dictionary :: search(string key, node *root)
{
    count++;
    if (root->key == key)
    {   
        cout<<"Data is present in the tree";
        return root;
    }
    else if (key < root->key)
        return search(key,root->left);
    else if (key > root->key)
        return search(key,root->right);
    else
        cout<<"Data is not present in the tree";
        return NULL;
}

void Dictionary :: update(string key , string value)
{
    node* temp = search(key,root);
    if (temp != nullptr)
    {
        temp->value = value;
        cout<<"Updated Successfully\n";
    }
    else
    {
        cout<<"Key not found. Unable to update\n";
    }
}

void Dictionary :: display(node *root)
{
    if (root != NULL)
    {
        display(root->left);
        cout<<root->key<<" : "<<root->value<<endl;
        display(root->right);
    }
}

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
                mydict.create();
            break;

            case 2:
                cout<<"Enter the key to remove : ";
                cin>>key;
                mydict.remove(mydict.root,key);
            break;

            case 3:
                cout<<"Enter the key you want to search : ";
                cin>>key;
                mydict.search(key,mydict.root);
                cout<<"\nTotal comparisons : ";
                cout<<mydict.get_count();
                mydict.count = 0;
            break;

            case 4:
                cout<<"\nEnter the key to update : ";
                cin>>key;
                cout<<"\nEnter the new value : ";
                cin>>value;
                mydict.update(key,value);
            break;

            case 5:
                mydict.display(mydict.root);
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
