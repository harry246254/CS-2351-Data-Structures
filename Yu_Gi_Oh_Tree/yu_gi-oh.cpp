#include <iostream>
#include <string>
using namespace std;

template <typename T>
struct Node
{
    T data;
    Node<T> *left;
    Node<T> *right;
};

template <typename T>
Node<T> *creatNode(T a)
{
    Node<T> *newNode = new Node<T>;
    newNode->data = a;
    newNode->left = nullptr;
    newNode->right = nullptr;
    return newNode;
}

template <typename T>
void Preorder(Node<T> *currentNode)
{
    static bool firstNode = true;
    if (currentNode)
    {
        if (currentNode->data == "real world")
        {
            Preorder(currentNode->left);
            Preorder(currentNode->right);
            return;
        }
        if (firstNode) {
            cout << currentNode->data;
            firstNode = false;
        } else {
            cout << " " << currentNode->data;
        }
        Preorder(currentNode->left);
        Preorder(currentNode->right);
    }else
    {
        return;   
    }
}

int main()
{
    Node<string> *root;
    Node<string> *insert;
    string motion;
    string arrowhead;
    string star;
    int count;
    int damage_left;
    int damage_right;
    int damage = 0;
    root = creatNode<string>("real world");
    while (1)
    {
        cin >> motion;
        if (motion == "TheEnd")
        {
            break;
        }else if (motion == "Summon")
        {
            cin >> arrowhead >> star;
            count = star.at(0) - 48;
            if (count <= 4)
            {
                if (root -> left == nullptr && root -> right == nullptr)
                {
                    root -> left = creatNode<string>(star);
                }else if (root -> left != nullptr && root -> right == nullptr)
                {
                    root -> right = creatNode<string>(star);
                }
            }else if (count == 5 || count == 6)
            {
                insert = creatNode<string>(star);
                if (root -> left != nullptr && root -> right == nullptr)
                {
                    insert -> left = root -> left;
                    root -> left = insert;
                }else if (root -> right != nullptr && root -> left == nullptr)
                {
                    insert -> right= root ->right;
                    root -> right = insert;
                }else if (root -> right != nullptr && root -> left)
                {
                    int min = root -> left -> data.at(0);
                    if (root -> right -> data.at(0) < min)
                    {
                        insert -> right = root -> right;
                        root -> right = insert;
                    }else
                    {
                        insert -> left = root -> left;
                        root -> left = insert;
                    }
                }    
            }else if (count == 7 || count == 8)
            {
                insert = creatNode<string>(star);
                if (root -> left != nullptr && root -> right != nullptr)
                {
                    insert -> right = root -> right;
                    insert -> left = root -> left;
                    root -> left = insert;
                    root -> right = nullptr;
                }
            }
        }else if (motion == "Attack")
        {
            damage_left = 0;
            damage_right = 0;
            if (root -> left != nullptr)
            {
                damage_left = root -> left -> data.at(0) - 48;
            }
            if (root -> right != nullptr)
            {
                damage_right = root -> right -> data.at(0) - 48;
            }
            damage += damage_left;
            damage += damage_right;
        }
    }
    Preorder(root);
    cout << endl;
    cout << damage << endl;
}