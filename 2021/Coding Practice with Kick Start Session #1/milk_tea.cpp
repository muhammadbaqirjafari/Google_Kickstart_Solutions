#include <iostream>
#include <fstream>
using namespace std;

void calculate_total_diff(int *arr, int *diff, int size)
{
    int prev_size = 0;
    for (int i = 0; i < size; ++i)
    {
        for (int j = prev_size; j >= 0; --j)
            arr[j + diff[i]] += arr[j];
        // Current increment
        arr[diff[i]] += 1;
        // Update size
        prev_size += diff[i];
    }
}

int main()
{
    // fstream cin("t1.txt");
    // fstream cout("t1_output.txt", ios::out);

    int n;
    cin >> n;

    for (int t = 0; t < n; ++t)
    {
        int N, M, P;

        cin >> N >> M >> P;
        cin.ignore(); // \n

        // N milks
        int *milks = new int[N];
        // New diff array
        int *diff = new int[P];
        int *ones_counter = new int[P];
        for (int i = 0; i < P; ++i)
        {
            diff[i] = 0;
            ones_counter[i] = 0;
        }
        // Input
        for (int i = 0; i < N; ++i)
        {
            milks[i] = 0;
            for (int j = 0; j < P; ++j)
            {
                char temp;
                cin >> temp;

                milks[i] <<= 1;

                if (temp == '1')
                {
                    milks[i] |= 1;
                    diff[j]++;
                }
                else
                    diff[j]--;
            }
            cin.ignore(); // \n
        }

        // Make Number
        int tt = 0;
        for (int i = 0; i < P; ++i)
        {
            if (diff[i] < 0)
            {
                // Ones Counter
                ones_counter[i] = (N + diff[i]) / 2;

                // Count ones
                tt += ones_counter[i];
            }
            else if (diff[i] == 0)
            {
                ones_counter[i] = N / 2;
                tt += ones_counter[i];
            }
            else
            {
                ones_counter[i] = (diff[i] + N) / 2;

                // Count Zeros
                tt += N - ones_counter[i];
            }
        }

        // Diff to positive
        int total_diff = 1;
        for (int i = 0; i < P; ++i)
        {
            diff[i] = abs(diff[i]);
            total_diff += diff[i];
        }

        // New Array
        int *all_diff = new int[total_diff];
        for (int i = 0; i < total_diff; ++i)
            all_diff[i] = 0;

        // calculate_diff();
        calculate_total_diff(all_diff, diff, P);
        all_diff[0] += 1;

        // M Milks
        for (int i = 0; i < M; ++i)
        {
            int dd = 0;
            for (int j = 0; j < P; ++j)
            {
                char temp;
                cin >> temp;

                if (temp == '1')
                    dd += N - ones_counter[j]; // Count Zeros
                else
                    dd += ones_counter[j]; // Count Ones
            }
            cin.ignore(); // \n
            // Delete diff
            dd -= tt;
            if (dd < total_diff)
            {
                all_diff[dd] -= 1;
            }
        }

        // cout min diff
        for (int i = 0; i < total_diff; ++i)
        {
            if (all_diff[i])
            {
                cout << "Case #" << t + 1 << ": " << i + tt << "\n";
                break;
            }
        }
    }

    return 0;
}