#include <iostream>
#include <vector>
#include <string>
#include <functional>
using namespace std;

struct Fruit
{
    string name;
    vector<int> hyperFeatures;
};

struct GradBinHyperWeight
{
    int featureIdx;
    double gradSlider;
    int binThreshold;
};
void Sort(Fruit **arr, Fruit **store, int index, int pivot, int cate)
{
    int count = 0;
    int count_back = cate - 1;
    for (int i = 0; i < cate; i++)
    {
        if ((store[i] -> hyperFeatures)[index] < pivot)
        {
            arr[count] -> name = store[i] -> name;
            (arr[count] -> hyperFeatures)[index] = (store[i] -> hyperFeatures)[index];
            count++;
        }
    }
    for (int i = cate - 1; i >= 0; i--)
    {
        if ((store[i] -> hyperFeatures)[index] >= pivot)
        {
            arr[count_back] -> name = store[i] -> name;
            (arr[count_back] -> hyperFeatures)[index] = (store[i] -> hyperFeatures)[index];
            count_back--;
        }
    }
    for (int i = 0; i < cate; i++)
    {
        store[i] -> name = arr[i] -> name;
        (store[i] -> hyperFeatures)[index] = (arr[i] -> hyperFeatures)[index];
    }
}
int main()
{
    int fruit_cate;
    int fruit_fea;
    string fruit;
    int count;
    int node_count;
    int index;
    double slide;
    int bin;
    Fruit *head = new Fruit;
    Fruit **arr = new Fruit *[fruit_cate];
    Fruit **store = new Fruit *[fruit_cate];
    while (1)
    {
        cin >> fruit_cate;
        if (cin.eof())
        {
            break;
        }
        cin >> fruit_fea;
        for (int i = 0; i < fruit_cate; i++)
        {
            cin >> fruit;
            arr[i] = new Fruit;
            store[i] = new Fruit;
            arr[i]->name = fruit;
            store[i] -> name = fruit;
            for (int j = 0; j < fruit_fea; j++)
            {
                cin >> count;
                arr[i]->hyperFeatures.push_back(count);
                store[i] -> hyperFeatures.push_back(count);
            }
        }
        cin >> node_count;
        GradBinHyperWeight ** node = new GradBinHyperWeight *[node_count];
        Fruit ** insertnode = new Fruit *[node_count];
        for (int i = 0; i < node_count; i++)
        {
            node[i] = new GradBinHyperWeight;
            insertnode[i] = new Fruit;
            cin >> index >> slide >> bin;
            node[i] -> featureIdx = index;
            node[i] -> gradSlider = slide;
            node[i] -> binThreshold = bin;
            for (int j = 0; j < fruit_cate; j++)
            {
                (arr[j] -> hyperFeatures)[index] = (arr[j] -> hyperFeatures)[node[i] -> featureIdx] * node[i] -> gradSlider;   
            }
            Sort(arr, store, node[i] -> featureIdx, node[i] -> gradSlider, fruit_cate);  
        } 
    }
        for (int i = 0; i < fruit_cate; i++)
    {
        cout << arr[i] -> name << " " << (arr[i] -> hyperFeatures)[index] << endl;
    }
    return 0;
}