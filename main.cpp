#include <iostream>
#include <limits> // for std::numeric_limits
using namespace std;

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

void getPlayerMove(char board[3][3], char player)
{
    int row, col;
    while (true)
    {
        cout << "Player " << player << ", enter your move (row and column): ";
        cin >> row >> col;

        // Check if the input is valid
        if (cin.fail())
        {
            cin.clear();                                         // clear the fail flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ignore the invalid input
            cout << "Invalid input. Please enter numbers for row and column." << endl;
            continue;
        }

        // Check if the move is within bounds and the cell is empty
        if (row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == ' ')
        {
            board[row][col] = player;
            break;
        }
        else
        {
            cout << "Invalid move. Try again." << endl;
        }
    }
}

// Function to check for a win
bool checkWin(const char board[3][3], char player)
{
    // Check rows and columns
    for (int i = 0; i < 3; i++)
    {
        if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) ||
            (board[0][i] == player && board[1][i] == player && board[2][i] == player))
        {
            return true;
        }
    }
    // Check diagonals
    if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
        (board[0][2] == player && board[1][1] == player && board[2][0] == player))
    {
        return true;
    }
    return false;
}

// Function to check for a draw
bool checkDraw(const char board[3][3])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == ' ')
            {
                return false;
            }
        }
    }
    return true;
}

// Function to switch player
char switchPlayer(char currentPlayer)
{
    return (currentPlayer == 'X') ? 'O' : 'X';
}

// Function to find the best move for the AI
int minimax(char board[3][3], bool isMaximizing)
{
    // Check for terminal states (win, loss, draw)
    if (checkWin(board, 'X'))
        return -1;
    if (checkWin(board, 'O'))
        return 1;
    if (checkDraw(board))
        return 0;

    if (isMaximizing)
    {
        int bestScore = -1000;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (board[i][j] == ' ')
                {
                    board[i][j] = 'O';
                    int score = minimax(board, false);
                    board[i][j] = ' ';
                    bestScore = max(score, bestScore);
                }
            }
        }
        return bestScore;
    }
    else
    {
        int bestScore = 1000;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (board[i][j] == ' ')
                {
                    board[i][j] = 'X';
                    int score = minimax(board, true);
                    board[i][j] = ' ';
                    bestScore = min(score, bestScore);
                }
            }
        }
        return bestScore;
    }
}

// Ai player
pair<int, int> findBestMove(char board[3][3])
{
    int bestScore = -1000;
    pair<int, int> bestMove = {-1, -1};
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == ' ')
            {
                board[i][j] = 'O';
                int score = minimax(board, false);
                board[i][j] = ' ';
                if (score > bestScore)
                {
                    bestScore = score;
                    bestMove = {i, j};
                }
            }
        }
    }
    return bestMove;
}

void displayMenu()
{
    cout << "Tic-Tac-Toe Game" << endl;
    cout << "1. Player vs Player" << endl;
    cout << "2. Player vs AI" << endl;
    cout << "3. Exit" << endl;
    cout << "Choose an option: ";
}

int main()
{
    char board[3][3];
    char currentPlayer = 'X';
    initializeBoard(board);

    while (true)
    {
        displayBoard(board);
        getPlayerMove(board, currentPlayer);

        if (checkWin(board, currentPlayer))
        {
            displayBoard(board);
            cout << "Player " << currentPlayer << " wins!" << endl;
            break;
        }

        if (checkDraw(board))
        {
            displayBoard(board);
            cout << "It's a draw!" << endl;
            break;
        }

        currentPlayer = switchPlayer(currentPlayer);
    }

    return 0;
}
