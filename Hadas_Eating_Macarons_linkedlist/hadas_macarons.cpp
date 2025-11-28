#include <iostream>
using namespace std;
struct Node
{
    int label;
    int macarons;
    Node *next;
};
Node *createNode(int label, int macarons)
{
    Node *newNode = new Node;
    newNode->label = label;
    newNode->macarons = macarons;
    newNode->next = nullptr;
    return newNode;
}
Node *clear()
{
    Node *newNode = new Node;
    newNode->label = 0;
    newNode->macarons = 0;
    newNode->next = nullptr;
    return newNode;
}
void printResult(Node *start)
{
    Node *current = start;
    do
    {
        cout << current->label << " / " << current->macarons << endl;
        current = current->next;
    } while (current != start);
}
void Delete(Node *x, Node *y)
{
    y->next = x->next;
    delete x;
}
void reverse(Node *x, Node *z)
{
    Node *t = x;
    x = z;
    z = t;
}
int findNode(int arr[], int max)
{
    int MAX_SIZE = max;
    int max1 = 0;
    bool check = false;
    double bucket[MAX_SIZE + 1] = {0};
    for (int i = 0; i < 6; i++)
    {
        if (arr[i] >= 0 && arr[i] <= MAX_SIZE) 
        {
            bucket[arr[i]]++;
        }
 
    }
    for (int i = 0; i < max; i++)
    {
        if (bucket[i] > 1)
        {
            max1 = i;
            check = true;
        }
    }
    if (check == true)
    {
        return max1;
    }else
    {
        return -1;
    }
}
Node *maximum(Node *current)
{
    Node *max;
    Node *nextnode = current -> next;
    max = nextnode;
    for (int i = 0; i < 6; i++)
    {
        if (nextnode -> macarons > max -> macarons)
        {
            max = nextnode;
        }
        nextnode = nextnode -> next;
    }
    return max;
}
Node *minimum(Node *current)
{
    Node *min;
    Node *nextnode = current -> next;
    min = current;
    for (int i = 0; i < 6; i++)
    {
        if (nextnode -> macarons < min -> macarons)
        {
            min = nextnode;
        }
        nextnode = nextnode -> next;
    }
    return min;
}
Node *findclose(Node *current, Node *target, int mode)
{
    Node *antiwise = current->next->next->next->next->next->next;
    Node *wise = current->next;
    for (int i = 0; i < 3; i++)
    {
    if (i == 1)
    {
        antiwise = current->next->next->next->next->next;
        wise = current->next->next;
    }
    else if (i == 2)
    {
        antiwise = current->next->next->next->next;
        wise = current->next->next->next;
    }
    if (wise -> macarons == mode && antiwise -> macarons == mode)
    {
        target = wise;
    }
    else if (wise -> macarons == mode)
    {
        target = wise;
    }
    else if (antiwise -> macarons == mode)
    {
        target = antiwise;
    }
        if(target -> label != 0) break;
    }
    return target;
}
int main()
{
    int a;
    Node *node[10];
    // input
    for (int i = 1; i <= 10; i++)
    {
        cin >> a;
        node[i - 1] = createNode(i, a);
    }
    // link nodes
    for (int i = 1; i <= 10; i++)
    {
        if (i != 10)
        {
            node[i - 1]->next = node[i];
        }
        else
            node[9]->next = node[0];
    }
    Node *target;
    Node *current;
    Node **renode = new Node *[3];
    for (int j = 0; j < 100; j++)
    {
        if (j == 0)
        {
            current = node[0];
        }else
        {
            Node *newnode = target -> next;
            for (int i = 0; i < 9; i++)
            {
                if (newnode -> label == target -> label % 10 + 1)
                {
                    current = newnode;
                    break;
                }
                newnode = newnode -> next;
            }
        }
        target = clear();
        // remove three node
        for (int i = 0; i < 3; i++)
        {
            renode[i] = new Node;
        }
        for (int i = 0; i < 3; i++)
        {
            renode[i]->label = current->next->label;
            renode[i]->macarons = current->next->macarons;
            if(i == 2)
            {
                renode[i] -> next = nullptr;
            }
            Delete(current->next, current);
        }
        // select target plate
        int b[6];
        Node *check = current->next;
        for (int i = 0; i < 6; i++)
        {
            b[i] = check->macarons;
            check = check->next;
        }
        Node *min = minimum(current);
        Node *max = maximum(current);
        Node *checknode = current -> next;
        Node *Max = createNode(0, 0);
        int mode;
        if (min -> label == current -> label)
        {
            mode = findNode(b, max -> macarons + 1);
            if (mode == -1)
            {
                target = max;
            }else
            {
                if (mode == current -> macarons || mode < max -> macarons)
                {
                    target = max;
                }else
                {
                    target = findclose(current, target, mode);
                }
            }
        }else
        {
            for (int i = 0; i < 6; i++)
            {
                if (checknode -> macarons < current -> macarons)
                {
                    if (checknode -> macarons >= Max -> macarons)
                    {
                        Max = checknode;
                    }
                }
                checknode = checknode -> next;
            }
            mode = findNode(b, current -> macarons);
            if (mode == -1)
            {
                target = Max;
            }else 
            {
                if(Max -> macarons != mode)
                {
                    target = Max;
                }else
                {
                    target = findclose(current, target, mode);
                }
            }
        }
        // eat macarons
        int k = target -> label;
        if (target -> macarons < k)
        {
            target -> macarons += 50;
            target ->macarons -= k;
        }else
        {
            target -> macarons -= k;
        }
        // reverse three nodes
        Node *t = renode[0];
        renode[0] = renode[2];
        renode[2] = t;
        renode[2]->next = target->next;
        target->next = renode[0];
        renode[0]->next = renode[1];
        renode[1]->next = renode[2];
    }
    printResult(target);
}
