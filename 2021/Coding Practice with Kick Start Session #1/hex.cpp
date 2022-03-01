#include <iostream>
using namespace std;

bool isPathPossible(char **board, int size, int i, int j, char ch)
{
    // Return Case
    if (j == size - 1 && board[i][j] == 'B')
    {
        board[i][j] = 'T';
        return true;
    }
    else if (i == size - 1 && board[i][j] == 'R')
    {
        board[i][j] = 'T';
        return true;
    }

    board[i][j] = 'T';
    bool result = false;

    // Left Check
    if (j > 0 && board[i][j - 1] == ch)
        result = isPathPossible(board, size, i, j - 1, ch);
    // Right Check
    if (!result && j + 1 < size && board[i][j + 1] == ch)
        result = isPathPossible(board, size, i, j + 1, ch);
    // Up Check
    if (!result && i > 0 && board[i - 1][j] == ch)
        result = isPathPossible(board, size, i - 1, j, ch);
    // Down Check
    if (!result && i + 1 < size && board[i + 1][j] == ch)
        result = isPathPossible(board, size, i + 1, j, ch);
    // Up Right Check
    if (!result && i > 0 && j < size - 1 && board[i - 1][j + 1] == ch)
        result = isPathPossible(board, size, i - 1, j + 1, ch);
    // Down Left Check
    if (!result && i < size - 1 && j > 0 && board[i + 1][j - 1] == ch)
        result = isPathPossible(board, size, i + 1, j - 1, ch);

    return result;
}

void resetBoard(char **board, int size, char ch)
{
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            if (board[i][j] == 'T')
                board[i][j] = ch;
        }
    }
}

bool checkPath(char **board, int size, char ch)
{
    // Blue Check
    if (ch == 'B')
    {
        for (int i = 0; i < size; ++i)
        {
            if (board[i][0] == 'B' && isPathPossible(board, size, i, 0, 'B'))
                return true;
        }
    }
    // Red Check
    else
    {
        for (int j = 0; j < size; ++j)
        {
            if (board[0][j] == 'R' && isPathPossible(board, size, 0, j, 'R'))
                return true;
        }
    }

    return false;
}

int main()
{
    int n;
    cin >> n;

    for (int t = 0; t < n; ++t)
    {
        int size;
        cin >> size;

        // Arr
        char **board = new char *[size];
        int red_count = 0, blue_count = 0;
        // Taking input
        for (int i = 0; i < size; ++i)
        {
            board[i] = new char[size];
            for (int j = 0; j < size; ++j)
            {
                cin >> board[i][j];
                if (board[i][j] == 'B')
                    blue_count++;
                else if (board[i][j] == 'R')
                    red_count++;
            }
        }

        string result;
        // First Case
        if ((int)abs(red_count - blue_count) > 1)
        {
            result = "Impossible";
        }
        else
        {
            bool isValid = false;
            bool blueCheck = false;
            // Blue Check
            if (checkPath(board, size, 'B'))
            {
                resetBoard(board, size, 'B');
                blueCheck = true;
                for (int i = 0; i < size; ++i)
                {
                    for (int j = 0; j < size; ++j)
                    {
                        if (board[i][j] == 'B')
                        {
                            board[i][j] = '.';
                            if (!checkPath(board, size, 'B'))
                                isValid = true;
                            resetBoard(board, size, 'B');
                            board[i][j] = 'B';
                        }
                        if (isValid)
                            break;
                    }
                    if (isValid)
                        break;
                }
            }
            resetBoard(board, size, 'B');

            if (blueCheck && !isValid || blueCheck && red_count > blue_count)
                result = "Impossible";
            else if (blueCheck)
                result = "Blue wins";
            else
            {
                isValid = false;
                bool redCheck = false;
                // Red Check
                if (checkPath(board, size, 'R'))
                {
                    resetBoard(board, size, 'R');
                    redCheck = true;
                    for (int i = 0; i < size; ++i)
                    {
                        for (int j = 0; j < size; ++j)
                        {
                            if (board[i][j] == 'R')
                            {
                                board[i][j] = '.';
                                if (!checkPath(board, size, 'R'))
                                    isValid = true;
                                resetBoard(board, size, 'R');
                                board[i][j] = 'R';
                            }
                            if (isValid)
                                break;
                        }
                        if (isValid)
                            break;
                    }
                }
                // Check it
                if (redCheck && !isValid || redCheck && blue_count > red_count)
                    result = "Impossible";
                else if (redCheck)
                    result = "Red wins";
                else
                    result = "Nobody wins";
            }
        }

        cout << "Case #" << t + 1 << ": " << result << "\n";
    }

    return 0;
}