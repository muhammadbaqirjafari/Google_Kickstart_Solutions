#include <iostream>
using namespace std;

char vowels[] = {'a', 'e', 'i', 'o', 'u'};

string find_ruler(string str)
{
    char last_char = tolower(str[str.length() - 1]);

    // Check for nobody
    if (last_char == 'y')
        return "nobody";
    for (int i = 0; i < 5; ++i)
    {
        if (vowels[i] == last_char)
            return "Alice";
    }
    return "Bob";
}

int main()
{
    int n;
    cin >> n;
    cin.ignore();

    for (int i = 0; i < n; ++i)
    {
        string str;
        getline(cin, str);

        string ruler = find_ruler(str);

        cout << "Case #" << i + 1 << ": " << str << " is ruled by " << ruler << ".\n";
    }

    return 0;
}