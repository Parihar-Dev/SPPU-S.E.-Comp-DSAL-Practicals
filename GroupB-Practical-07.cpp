/*
Construct an Expression tree from given prefix expression and traverse it using post order traversal
(non recursive and then delete the entire tree)
*/

#include <iostream>
#include <cstring>
using namespace std;

struct Node
{
    char data;
    Node *left;
    Node *right;
};

class ExpressionTree
{
    char expression[20];

public:
    Node *root;
    void buildExpressionTree(char[]);
    void display(Node *);
    void nonRecursivePostorder(Node *);
    void deleteTree(Node *);
};

class Stack
{
    Node *data[30];
    int top;

public:
    Stack()
    {
        top = -1;
    }
    int isEmpty()
    {
        return (top == -1);
    }
    void push(Node *p)
    {
        data[++top] = p;
    }
    Node *pop()
    {
        return (data[top--]);
    }
};

void ExpressionTree::buildExpressionTree(char prefix[])
{
    Stack stack;
    Node *t1, *t2;
    int len = strlen(prefix);
    for (int i = len - 1; i >= 0; i--)
    {
        root = new Node;
        root->left = nullptr;
        root->right = nullptr;
        if (isalnum(prefix[i]))
        {
            root->data = prefix[i];
            stack.push(root);
        }
        else if (prefix[i] == '+' || prefix[i] == '*' || prefix[i] == '-' || prefix[i] == '/')
        {
            t2 = stack.pop();
            t1 = stack.pop();
            root->data = prefix[i];
            root->left = t2;
            root->right = t1;
            stack.push(root);
        }
    }
    root = stack.pop();
}

void ExpressionTree::display(Node *root)
{
    if (root != nullptr)
    {
        cout << root->data;
        display(root->left);
        display(root->right);
    }
}

void ExpressionTree::nonRecursivePostorder(Node *root)
{
    Stack s1, s2;
    Node *temp = root;
    s1.push(temp);
    while (!s1.isEmpty())
    {
        temp = s1.pop();
        s2.push(temp);
        if (temp->left != nullptr)
            s1.push(temp->left);
        if (temp->right != nullptr)
            s1.push(temp->right);
    }
    while (!s2.isEmpty())
    {
        root = s2.pop();
        cout << root->data;
    }
}

void ExpressionTree::deleteTree(Node *root)
{
    if (root == nullptr)
        return;
    deleteTree(root->left);
    deleteTree(root->right);
    cout << endl << "Deleting node : " << root->data << endl;
    delete root;
}

int main()
{
    char prefixExpression[20];
    ExpressionTree expressionTree;

    cout << "Enter prefix Expression : ";
    cin >> prefixExpression;
    expressionTree.buildExpressionTree(prefixExpression);
    expressionTree.nonRecursivePostorder(expressionTree.root);
    expressionTree.deleteTree(expressionTree.root);
    return 0;
}
