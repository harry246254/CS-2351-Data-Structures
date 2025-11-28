#include <iostream>
#include <string>
using namespace std;

template <class T>
class Stack
{
private:
    T *stack;
    int top;
    int capacity;

public:
    Stack(int cap = 100)
    {
        if (cap < 1)
            throw "Stack cpacity must be > 0";
        stack = new T[cap];
        capacity = cap;
        top = -1;
    }
    bool IsEmpty() const
    {
        return top == -1;
    }
    T &Top()
    {
        if (IsEmpty())
            throw "Stack is empty";
        return stack[top];
    }
    void Push(const T &x)
    {
        if (top == capacity - 1)
        {
            cout << "Full" << endl;
            return;
        }
        stack[++top] = x;
    }
    void Pop()
    {
        if (IsEmpty())
            throw "Stack is Empty";
        top--;
    }
    T &value(int top)
    {
        return stack[top];
    }
    int getSize()
    {
        return top + 1;
    }
};
int Score(int g, int s)
{
    if (g == 3)
    {
        return 500;
    }
    else if (g == 2 && s == 1)
    {
        return 300;
    }
    else if (g == 1 && s == 2)
    {
        return 150;
    }
    else if (s == 3)
    {
        return 50;
    }
}
int main()
{
    Stack<string> path;
    Stack<string> score;
    Stack<string> score_real;
    string a;
    string s;
    string r;
    int gold_s = 0;
    int silver_s = 0;
    int gold_r = 0;
    int silver_r = 0;
    int score_r = 0;
    int score_s = 0;
    int size;
    int j = 0;
    bool check;
    while(1)
    {
        cin >> a;
        if (cin.eof())
        {
            break;
        }
        if (a == "TL")
            path.Push("TR");
        else if (a == "TR")
            path.Push("TL");
        if (a == "MISS")
        {
            check = true;
            j = 0;
        }
        if (j == 4)
        {
            check = false;
            j = 0;
        }
        if ((a == "GOLD" || a == "SILVER") && check == false)
        {
            score.Push(a);
            score_real.Push(a);
        }
        else if ((a == "GOLD" || a == "SILVER") && check == true)
        {
            score.Push(a);
            j++;
        }
        size = score_real.getSize();
        if (size == 3)
        {
            for (int i = 0; i < 3; i++)
            {
                r = score_real.value(i);
                if (r == "GOLD")
                {
                    gold_r += 1;
                }
                else if (r == "SILVER")
                {
                    silver_r += 1;
                }
            }
            score_r += Score(gold_r, silver_r);
            gold_r = 0;
            silver_r = 0;
            score_real.Pop();
            score_real.Pop();
            score_real.Pop();
        }
        size = score.getSize();
        if (size == 3)
        {
            for (int i = 0; i < 3; i++)
            {
                s = score.value(i);
                if (s == "GOLD")
                {
                    gold_s += 1;
                }
                else if (s == "SILVER")
                {
                    silver_s += 1;
                }
            }
            score_s += Score(gold_s, silver_s);
            gold_s = 0;
            silver_s = 0;
            score.Pop();
            score.Pop();
            score.Pop();
        }
    }
    {
        size = path.getSize();
        for (int i = size - 1; i > 0; i--)
        {
            a = path.value(i);
            cout << a << "->";
        }
        a = path.value(0);
        cout << a << endl;
    }
    cout << score_r << endl;
    cout << score_s << endl;
    return 0;
}