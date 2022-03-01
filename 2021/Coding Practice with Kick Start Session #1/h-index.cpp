#include <iostream>
#include <queue>
#include <vector>
#include <functional> // std::greater
using namespace std;

int main()
{
    int n;
    cin >> n;

    for (int i = 0; i < n; ++i)
    {
        // Min Heap
        priority_queue<int, vector<int>, greater<int>> min_heap;

        int papers;
        cin >> papers;

        int current_index = 1;
        cout << "Case #" << i + 1 << ":";
        for (int j = 0; j < papers; ++j)
        {
            int c;
            cin >> c;

            // Logic goes here
            if (current_index < c)
            {
                min_heap.push(c);
            }

            // Check size
            if (min_heap.size() > current_index)
            {
                ++current_index;
            }

            // Remove Nodes
            while (!min_heap.empty() && min_heap.top() <= current_index)
                min_heap.pop();

            cout << " " << current_index;
        }
        cout << "\n";
    }

    return 0;
}