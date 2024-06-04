#include <iostream>
using namespace std;

// Function to initialize the board
void initializeBoard(char board[3][3])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            board[i][j] = ' ';
        }
    }
}

// Function to display the board
void displayBoard(const char board[3][3])
{
    cout << "  0 1 2" << endl;
    for (int i = 0; i < 3; i++)
    {
        cout << i << " ";
        for (int j = 0; j < 3; j++)
        {
            cout << board[i][j];
            if (j < 2)
                cout << "|";
        }
        cout << endl;
        if (i < 2)
            cout << "  -----" << endl;
    }
}

int main()
{
    char board[3][3];
    initializeBoard(board);
    displayBoard(board);

    return 0;
}
