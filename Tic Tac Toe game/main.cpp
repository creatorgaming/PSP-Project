#include <iostream>
using namespace std;

char *squares = new char[9]{'1', '2', '3', '4', '5', '6', '7', '8', '9'};

void play();
void getBoard();
int checkWin();

int main()
{
    char *playAgain = new char;
    do
    {
        play();
        cout << "Do you want to play again(y/n): ";
        cin >> *playAgain;

    } while (tolower(*playAgain) == 'y');
    delete squares, playAgain;
    cin.get();
    return 0;
}

//Play the game
void play()
{
    int *i = new int;
    int player = 1;
    int *choice = new int;
    char *mark = new char;

    do
    {
        getBoard();
        player = (player%2) ? 1 : 2;
        cout << "Enter your choice: ";
        cin >> *choice;
        *mark = (player == 1) ? 'X' : 'O';

        if (squares[0] == '1' && *choice == 1)
        {
            squares[0] = *mark;
        }
        else if (squares[1] == '2' && *choice == 2)
        {
            squares[1] = *mark;
        }
        else if (squares[2] == '3' && *choice == 3)
        {
            squares[2] = *mark;
        }
        else if (squares[3] == '4' && *choice == 4)
        {
            squares[3] = *mark;
        }
        else if (squares[4] == '5' && *choice == 5)
        {
            squares[4] = *mark;
        }
        else if (squares[5] == '6' && *choice == 6)
        {
            squares[5] = *mark;
        }
        else if (squares[6] == '7' && *choice == 7)
        {
            squares[6] = *mark;
        }
        else if (squares[7] == '8' && *choice == 8)
        {
            squares[7] = *mark;
        }
        else if (squares[8] == '9' && *choice == 9)
        {
            squares[8] = *mark;
        }
        else
        {
            cout << "Invalid move ";

            player--;
            cin.ignore();
            cin.get();
        }

        *i = checkWin();
        player++;

    } while (*i == -1);
    getBoard();
    if (*i == 1)
    {
        cout << "\aPlayer " << --player << " Wins" << endl;
        delete mark, choice, i;
    }
    else
    {
        cout << "\aGame Draw" << endl;
        delete mark, choice, i;
    }
}

// Print the board
void getBoard()
{
    cout << "\n\n\tTic Tac Toe\n\n";

    cout << "Player 1 (X)  -  Player 2 (O)" << endl
         << endl;
    cout << endl;

    cout << "     |     |     " << endl;
    cout << "  " << squares[0] << "  |  " << squares[1] << "  |  " << squares[2] << endl;

    cout << "_____|_____|_____" << endl;
    cout << "     |     |     " << endl;

    cout << "  " << squares[3] << "  |  " << squares[4] << "  |  " << squares[5] << endl;

    cout << "_____|_____|_____" << endl;
    cout << "     |     |     " << endl;

    cout << "  " << squares[6] << "  |  " << squares[7] << "  |  " << squares[8] << endl;

    cout << "     |     |     " << endl
         << endl;
}

/**********************************************************************************************************
Return 1 if some one wins
Return 0 if draw
Return -1 if the game is not over
***********************************************************************************************************/

int checkWin()
{
    if (squares[0] == squares[1] && squares[1] == squares[2])
    {
        return 1;
    }
    else if (squares[0] == squares[3] && squares[3] == squares[6])
    {
        return 1;
    }
    else if (squares[0] == squares[4] && squares[4] == squares[8])
    {
        return 1;
    }
    else if (squares[3] == squares[4] && squares[4] == squares[5])
    {
        return 1;
    }
    else if (squares[1] == squares[4] && squares[4] == squares[7])
    {
        return 1;
    }
    else if (squares[6] == squares[4] && squares[4] == squares[2])
    {
        return 1;
    }
    else if (squares[6] == squares[7] && squares[7] == squares[8])
    {
        return 1;
    }
    else if (squares[2] == squares[5] && squares[5] == squares[8])
    {
        return 1;
    }
    else if (squares[0] != '1' && squares[1] != '2' && squares[2] != '3' && squares[3] != '4' && squares[4] != '5' && squares[5] != '6' && squares[6] != '7' && squares[7] != '8' && squares[8] != '9')
    {
        return 0;
    }
    else
    {
        return -1;
    }
}