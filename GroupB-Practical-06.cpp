/*
Beginning with an empty search tree, Construct binary search tree by inserting the values in the order given.
After constructing a binary tree -
i. Insert new node
ii. Find number of nodes in longest path from root
iii. Minimum data value found in the tree
iv. Change a tree so that the roles of the left and right pointers are swapped at every node
v. Search a value 
*/

#include<iostream>
#include<queue>
using namespace std;

class node
{
    public:
        int data;
        node *left;
        node *right;
};

class Binary_Search_Tree
{
    public:
        node *root;
        Binary_Search_Tree()
        {
            root = NULL;
        }
    void create();
    void insert(node*,node*);
    int height(node*);
    void min_data(node*);
    void search(int,node*);
    void swap(node*);
    void display_level_wise(node*);
    void mirror();
    void inorder(node*);
};

void Binary_Search_Tree :: create()
{
    node *temp;
    char choice;
    do
    {
        temp = new node;

        cout<<"Enter the data for the node : ";
        cin>>temp->data;

        temp->left = NULL;
        temp->right = NULL;

        if (root == NULL)
        {
            root = temp;
            cout<<"Node Added as Root!";
        }
        else
            insert(root,temp);
        
        cout<<"Do you want to add more nodes (y/n) : ";
        cin>>choice;
    } while (choice == 'y');
}

void Binary_Search_Tree :: insert(node *root, node *temp)
{
    if (temp->data < root->data)
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

int Binary_Search_Tree :: height(node* root)
{
    if (root == NULL)
        return 0;
    else
    {
        if (height(root->left) > height(root->right))
            return (1 + height(root->left));
        else
            return (1 + height(root->right));
    }
}

void Binary_Search_Tree :: min_data(node *root)
{
    if (root->left != NULL)
    {
        min_data(root->left);
    }
    else if (root->left == NULL)
        cout<<"Minimum Data : "<<root->data;
}

void Binary_Search_Tree :: search(int key,node *root)
{
    if (root->data == key)
        cout<<"Data is Present in the Tree";
    else if (key < root->data)
        search(key,root->left);
    else if (key > root->data)
        search(key, root->right);
    else
        cout<<"Data is not present in the Tree";
}

void Binary_Search_Tree :: swap(node *root)
{
    if (root == NULL)
        return;
    else
    {
        node *temp;
        temp = new node;
        swap(root->left);
        swap(root->right);
        temp = root->left;
        root->left = root->right;
        root->right = temp;
    }
}

void Binary_Search_Tree :: display_level_wise(node *root)
{
    if (root == NULL)
        return;
    queue<node*>q;
    q.push(root);
    while(!q.empty())
    {
        int levelsize = q.size();
        for (int i = 0; i<levelsize ; ++i)
        {
            node* temp = q.front();
            q.pop();
            cout<<temp->data<<" ";
            if (temp->left)
                q.push(temp->left);
            if (temp->right)
                q.push(temp->right);
        }
        cout<<endl;
    }
}

void Binary_Search_Tree :: mirror()
{
    cout<<"\nOriginal Tree : \n";
    display_level_wise(root);
    swap(root);
    cout<<"\nTree with Swapped Nodes : \n";
    display_level_wise(root);
    swap(root);
}

void Binary_Search_Tree :: inorder(node* temp)
{
    if (temp != NULL)
    {
        inorder(temp->left);
        cout<<temp->data<<"->";
        inorder(temp->right);
    }
}

int main()
{
    Binary_Search_Tree bst;
    int choice;
    char ch;
    do
    {
        cout<<"\n----------    MENU    ----------";
        cout<<"\n1.Create";
        cout<<"\n2.Display";
        cout<<"\n3.No. of nodes in longest path";
        cout<<"\n4.Minimum Data in Tree";
        cout<<"\n5.Swap Pointer";
        cout<<"\n6.Search a Value";
        cout<<"\nEnter your choice : ";
        cin>>choice;

        switch(choice)
        {
            case 1:
                bst.create();
            break;

            case 2:
                bst.inorder(bst.root);
            break;

            case 3:
                cout<<"\nMaximum Number of Nodes :";
                cout<<bst.height(bst.root);
            break;

            case 4:
                cout<<"\nMinimum Data in the Tree : ";
                bst.min_data(bst.root);
            break;

            case 5:
                bst.mirror();
            break;

            case 6:
                int key;
                cout<<"Enter the value to Search : ";
                cin>>key;
                bst.search(key,bst.root);
            break;

            default:
                cout<<"Invalid Input";
        }
        cout<<"\nDo you want to continue(y/n) : ";
        cin>>ch;
    } while (ch == 'y');
}
