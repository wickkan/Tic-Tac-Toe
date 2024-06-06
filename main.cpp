#include <iostream>
#include <limits>  // for std::numeric_limits
#include <fstream> // For file operations
#include <stack>   // For storing move history

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

stack<pair<int, int>> moveHistory;

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
            moveHistory.push(make_pair(row, col)); // Save the move
            break;
        }
        else
        {
            cout << "Invalid move. Try again." << endl;
        }
    }
}

void undoMove(char board[3][3])
{
    if (!moveHistory.empty())
    {
        pair<int, int> lastMove = moveHistory.top();
        moveHistory.pop();
        board[lastMove.first][lastMove.second] = ' ';
    }
    else
    {
        cout << "No moves to undo!" << endl;
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
    pair<int, int> bestMove = make_pair(-1, -1);
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
                    bestMove = make_pair(i, j);
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
    cout << "3. Load Game" << endl; // Add option to load game
    cout << "4. Save Game" << endl; // Add option to save game
    cout << "5. Exit" << endl;
    cout << "Choose an option: ";
}

int playerXWins = 0;
int playerOWins = 0;
int draws = 0;

void updateScore(char winner)
{
    if (winner == 'X')
        playerXWins++;
    else if (winner == 'O')
        playerOWins++;
    else
        draws++;
}

void displayScore()
{
    cout << "Score: " << endl;
    cout << "Player X: " << playerXWins << endl;
    cout << "Player O: " << playerOWins << endl;
    cout << "Draws: " << draws << endl;
}

// Function to save the game state
void saveGame(const char board[3][3], char currentPlayer)
{
    ofstream outFile("savegame.txt");
    if (outFile.is_open())
    {
        outFile << currentPlayer << endl;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                outFile << board[i][j];
            }
            outFile << endl;
        }
        outFile.close();
        cout << "Game saved successfully!" << endl;
    }
    else
    {
        cout << "Unable to open file for saving." << endl;
    }
}

// Function to load the game state
bool loadGame(char board[3][3], char &currentPlayer)
{
    ifstream inFile("savegame.txt");
    if (inFile.is_open())
    {
        inFile >> currentPlayer;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                inFile >> board[i][j];
            }
        }
        inFile.close();
        cout << "Game loaded successfully!" << endl;
        return true;
    }
    else
    {
        cout << "No saved game found." << endl;
        return false;
    }
}

int main()
{
    char board[3][3];
    char currentPlayer = 'X';
    int option;

    while (true)
    {
        displayMenu();
        cin >> option;

        if (option == 5)
            break; // Exit

        if (option == 3)
        { // Load game
            if (!loadGame(board, currentPlayer))
            {
                continue; // If loading fails, return to menu
            }
        }
        else
        {
            initializeBoard(board);
            currentPlayer = 'X';
        }

        while (true)
        {
            displayBoard(board);
            if (option == 1 || (option == 2 && currentPlayer == 'X'))
            {
                getPlayerMove(board, currentPlayer);
            }
            else if (option == 2 && currentPlayer == 'O')
            {
                pair<int, int> bestMove = findBestMove(board);
                board[bestMove.first][bestMove.second] = 'O';
            }

            if (checkWin(board, currentPlayer))
            {
                displayBoard(board);
                cout << "Player " << currentPlayer << " wins!" << endl;
                updateScore(currentPlayer);
                break;
            }

            if (checkDraw(board))
            {
                displayBoard(board);
                cout << "It's a draw!" << endl;
                updateScore(' ');
                break;
            }

            currentPlayer = switchPlayer(currentPlayer);

            if (option == 4)
            { // Save game
                saveGame(board, currentPlayer);
                break; // Return to menu after saving
            }
        }

        displayScore();
    }

    return 0;
}
