//
//  main.cpp
//  Project 7
//
//  Created by Vignesh Balasundaram on 6/5/17.
//  Copyright © 2017 Vignesh Balasundaram. All rights reserved.
//

// scorpions.cpp

// Portions you are to complete are marked with a TODO: comment.
// We've provided some incorrect return statements (so indicated) just
// to allow this skeleton program to compile and run, albeit incorrectly.
// The first thing you probably want to do is implement the trivial
// functions (marked TRIVIAL).  Then get Pit::display going.  That gives you
// more flexibility in the order you tackle the rest of the functionality.
// As you finish implementing each TODO: item, remove its TODO: comment.

#include <iostream>
#include <string>
#include <random>
#include <utility>
#include <cstdlib>
using namespace std;


///////////////////////////////////////////////////////////////////////////
// Manifest constants
///////////////////////////////////////////////////////////////////////////

const int MAXROWS = 20;             // max number of rows in the pit
const int MAXCOLS = 40;             // max number of columns in the pit
const int MAXSCORPIONS = 160;       // max number of scorpions allowed

const int UP    = 0;
const int DOWN  = 1;
const int LEFT  = 2;
const int RIGHT = 3;
const int NUMDIRS = 4;

///////////////////////////////////////////////////////////////////////////
// Type definitions
///////////////////////////////////////////////////////////////////////////

class Pit;  // This is needed to let the compiler know that Pit is a
            // type name, since it's mentioned in the Scorpion declaration.

class Scorpion
{
public:
    // Constructor
    Scorpion(Pit* pp, int r, int c);
    
    // Accessors
    int  row() const;
    int  col() const;
    
    // Mutators
    void move();
    
private:
    Pit* m_pit;
    int  m_row;
    int  m_col;
};

class Player
{
public:
    // Constructor
    Player(Pit *pp, int r, int c);
    
    // Accessors
    int  row() const;
    int  col() const;
    int  age() const;
    bool isDead() const;
    
    // Mutators
    void   stand();
    void   move(int dir);
    void   setDead();
    
private:
    Pit*  m_pit;
    int   m_row;
    int   m_col;
    int   m_age;
    bool  m_dead;
};

class Pit
{
public:
    // Constructor/destructor
    Pit(int nRows, int nCols);
    ~Pit();
    
    // Accessors
    int     rows() const;
    int     cols() const;
    Player* player() const;
    int     scorpionCount() const;
    int     numberOfScorpionsAt(int r, int c) const;
    void    display() const;
    
    // Mutators
    bool   addScorpion(int r, int c);
    bool   addPlayer(int r, int c);
    bool   destroyOneScorpion(int r, int c);
    bool   moveScorpions();
    
private:
    int        m_rows;
    int        m_cols;
    Player*    m_player;
    Scorpion*  m_scorpions[MAXSCORPIONS];
    int        m_nScorpions;
    
    // Helper functions
    bool isPosInBounds(int r, int c) const;
};

class Game
{
public:
    // Constructor/destructor
    Game(int rows, int cols, int nScorpions);
    ~Game();
    
    // Mutators
    void play();
    
private:
    Pit* m_pit;
};

///////////////////////////////////////////////////////////////////////////
//  Auxiliary function declarations
///////////////////////////////////////////////////////////////////////////

int randInt(int min, int max);
int decodeDirection(char dir);
bool directionToDeltas(int dir, int& rowDelta, int& colDelta);
void clearScreen();

///////////////////////////////////////////////////////////////////////////
//  Scorpion implementation
///////////////////////////////////////////////////////////////////////////

Scorpion::Scorpion(Pit* pp, int r, int c)
{
    if (pp == nullptr)
    {
        cout << "***** A scorpion must be created in some Pit!" << endl;
        exit(1);
    }
    if (r < 1  ||  r > pp->rows()  ||  c < 1  ||  c > pp->cols())
    {
        cout << "***** Scorpion created with invalid coordinates (" << r << ","
        << c << ")!" << endl;
        exit(1);
    }
    m_pit = pp;
    m_row = r;
    m_col = c;
}

int Scorpion::row() const
{
    return m_row;
}

int Scorpion::col() const
{
    //Returns the column the scorpion is at.
    return m_col;
}

void Scorpion::move()
{
    //Defines the movements of the scorpions
    switch (randInt(0, NUMDIRS-1))
    {
        case UP:
            if (m_row > 1)
            {
                m_row--;
            }
            else
                break;
            break;
        case DOWN:
            if (m_row < m_pit->rows())
            {
                m_row++;
            }
            else
                break;
            break;
        case LEFT:
            if (m_col > 1)
            {
                m_col--;
            }
            else
                break;
            break;
        case RIGHT:
            if (m_col < m_pit->cols())
            {
                m_col++;
            }
            else
                break;
            break;
        default:
            break;
    }
}

///////////////////////////////////////////////////////////////////////////
//  Player implementation
///////////////////////////////////////////////////////////////////////////

Player::Player(Pit* pp, int r, int c)
{
    if (pp == nullptr)
    {
        cout << "***** The player must be created in some Pit!" << endl;
        exit(1);
    }
    if (r < 1  ||  r > pp->rows()  ||  c < 1  ||  c > pp->cols())
    {
        cout << "**** Player created with invalid coordinates (" << r
        << "," << c << ")!" << endl;
        exit(1);
    }
    m_pit = pp;
    m_row = r;
    m_col = c;
    m_age = 0;
    m_dead = false;
}

int Player::row() const
{
    //Returns the row the player is at.
    return m_row;
}

int Player::col() const
{
    //Returns the column the player is at.
    return m_col;
}

int Player::age() const
{
    //Returns the player's age.
    return m_age;
}

void Player::stand()
{
    m_age++;
}

void Player::move(int dir)
{
    m_age++;
    
    if (dir == 0)                   //PLAYER MOVEMENT UP
    {
        if (m_row==1)
            return;
        else if (m_row >= 2 && m_pit->numberOfScorpionsAt(m_row-1, m_col)==0)
        {
            m_row--;
            return;
        }
        else if (m_row >= 2 && m_pit->numberOfScorpionsAt(m_row-1, m_col)>=1)
        {
            if (m_row >= 3 && m_pit->numberOfScorpionsAt(m_row-2, m_col)==0)
            {
                m_row = m_row - 2;
                m_pit->destroyOneScorpion(m_row+1, m_col);
                return;
            }
            else if (m_row >= 3 && m_pit->numberOfScorpionsAt(m_row-2, m_col)>=1)
            {
                m_row = m_row - 2;
                m_pit->destroyOneScorpion(m_row+1, m_col);
                setDead();
                return;
            }
            else if (m_row == 2 && m_pit->numberOfScorpionsAt(m_row-1, m_col)>=1)
            {
                if (m_pit->numberOfScorpionsAt(m_row-1, m_col)==1)
                {
                    m_row--;
                    m_pit->destroyOneScorpion(m_row, m_col);
                    return;
                }
                else if (m_pit->numberOfScorpionsAt(m_row-1, m_col)>1)
                {
                    m_row--;
                    m_pit->destroyOneScorpion(m_row, m_col);
                    setDead();
                    return;
                }
            }
        }
    }
    
    if (dir == 1)                   //PLAYER MOVEMENT DOWN
    {
        if (m_row == m_pit->rows())
            return;
        else if (m_row <= m_pit->rows()-1 && m_pit->numberOfScorpionsAt(m_row+1, m_col)==0)
        {
            m_row++;
            return;
        }
        else if (m_row <= m_pit->rows()-1 && m_pit->numberOfScorpionsAt(m_row+1, m_col)>=1)
        {
            if (m_row <= m_pit->rows()-2 && m_pit->numberOfScorpionsAt(m_row+2, m_col)==0)
            {
                m_row = m_row + 2;
                m_pit->destroyOneScorpion(m_row-1, m_col);
                return;
            }
            else if (m_row <= m_pit->rows()-2 && m_pit->numberOfScorpionsAt(m_row+2, m_col)>=1)
            {
                m_row = m_row + 2;
                m_pit->destroyOneScorpion(m_row-1, m_col);
                setDead();
                return;
            }
            else if (m_row == m_pit->rows()-1 && m_pit->numberOfScorpionsAt(m_row+1, m_col)>=1)
            {
                if (m_pit->numberOfScorpionsAt(m_row+1, m_col)==1)
                {
                    m_row++;
                    m_pit->destroyOneScorpion(m_row, m_col);
                    return;
                }
                else if (m_pit->numberOfScorpionsAt(m_row, m_col)>1)
                {
                    m_row++;
                    m_pit->destroyOneScorpion(m_row, m_col);
                    setDead();
                    return;
                }
            }
        }
        cout << "none" << endl;
    }
    
    if (dir == 2)                           //PLAYER MOVEMENT LEFT
    {
        if (m_col==1)
            return;
        else if (m_col >= 2 && m_pit->numberOfScorpionsAt(m_row, m_col-1)==0)
        {
            m_col--;
            return;
        }
        else if (m_col >= 2 && m_pit->numberOfScorpionsAt(m_row, m_col-1)>=1)
        {
            if (m_col >= 3 && m_pit->numberOfScorpionsAt(m_row, m_col-2)==0)
            {
                m_col = m_col - 2;
                m_pit->destroyOneScorpion(m_row, m_col+1);
                return;
            }
            else if (m_col >= 3 && m_pit->numberOfScorpionsAt(m_row, m_col-2)>=1)
            {
                m_col = m_col - 2;
                m_pit->destroyOneScorpion(m_row, m_col+1);
                setDead();
                return;
            }
            else if (m_col == 2 && m_pit->numberOfScorpionsAt(m_row, m_col-1)>=1)
            {
                if (m_pit->numberOfScorpionsAt(m_row, m_col-1)==1)
                {
                    m_col--;
                    m_pit->destroyOneScorpion(m_row, m_col);
                    return;
                }
                else if (m_pit->numberOfScorpionsAt(m_row, m_col-1)>1)
                {
                    m_col--;
                    m_pit->destroyOneScorpion(m_row, m_col);
                    setDead();
                    return;
                }
            }
        }
    }
    
    if (dir == 3)                       //PLAYER MOVEMENT RIGHT
    {
        if (m_col == m_pit->cols())
        {
            return;
        }
        else if (m_col <= m_pit->cols()-1 && m_pit->numberOfScorpionsAt(m_row, m_col+1)==0)
        {
            m_col++;
            return;
        }
        else if (m_col <= m_pit->cols()-1 && m_pit->numberOfScorpionsAt(m_row, m_col+1)>=1)
        {
            if (m_col <= m_pit->cols()-2 && m_pit->numberOfScorpionsAt(m_row, m_col+2)==0)
            {
                m_col = m_col + 2;
                m_pit->destroyOneScorpion(m_row, m_col-1);
                return;
            }
            else if (m_col <= m_pit->cols()-2 && m_pit->numberOfScorpionsAt(m_row, m_col+2)>=1)
            {
                m_col = m_col + 2;
                m_pit->destroyOneScorpion(m_row, m_col-1);
                setDead();
                return;
            }
            else if (m_col == m_pit->cols()-1 && m_pit->numberOfScorpionsAt(m_row, m_col+1)>=1)
            {
                if (m_pit->numberOfScorpionsAt(m_row, m_col+1)==1)
                {
                    m_col++;
                    m_pit->destroyOneScorpion(m_row, m_col);
                    return;
                }
                else if (m_pit->numberOfScorpionsAt(m_row, m_col+1)>1)
                {
                    m_col++;
                    m_pit->destroyOneScorpion(m_row, m_col);
                    setDead();
                    return;
                }
            }
        }
    }
    return;                     //CODE SHOULD NEVER REACH HERE
}
bool Player::isDead() const
{
    //Returns whether the player is dead.
    if (m_dead == false)
        return false;
    else
        return true;
}

void Player::setDead()
{
    m_dead = true;
}

///////////////////////////////////////////////////////////////////////////
//  Pit implementation
///////////////////////////////////////////////////////////////////////////

Pit::Pit(int nRows, int nCols)
{
    if (nRows <= 0  ||  nCols <= 0  ||  nRows > MAXROWS  ||  nCols > MAXCOLS)
    {
        cout << "***** Pit created with invalid size " << nRows << " by "
        << nCols << "!" << endl;
        exit(1);
    }
    m_rows = nRows;
    m_cols = nCols;
    m_player = nullptr;
    m_nScorpions = 0;
}

Pit::~Pit()
{
    //DESTRUCTOR
    delete m_player;
    for (int i=0; i < m_nScorpions; i++)
    {
        delete m_scorpions[i];
    }
}

int Pit::rows() const
{
    //Returns the number of rows in the pit.
    return m_rows;
}

int Pit::cols() const
{
    //Returns the number of columns in the pit.
    return m_cols;
}

Player* Pit::player() const
{
    return m_player;
}

int Pit::scorpionCount() const
{
    return m_nScorpions;
}

int Pit::numberOfScorpionsAt(int r, int c) const
{
    //Counts the number of scorpions at row r, column c
    int count = 0;
    for (int i=0; i < m_nScorpions; i++)
    {
        if (m_scorpions[i]->row() == r && m_scorpions[i]->col()==c)
            count++;
    }
    return count;
}

void Pit::display() const
{
    // Position (row,col) in the pit coordinate system is represented in
    // the array element grid[row-1][col-1]
    char grid[MAXROWS][MAXCOLS];
    int r, c;
    
    // Fill the grid with dots
    for (r = 0; r < rows(); r++)
        for (c = 0; c < cols(); c++)
            grid[r][c] = '.';
    
    // Indicate each scorpion's position
    for (r = 1; r <= rows(); r++)
        for (c = 1; c <= cols(); c++)
        {
            if (numberOfScorpionsAt(r, c) == 1)
                grid[r-1][c-1] = 'S';
            else if (numberOfScorpionsAt(r, c) == 2)
                grid[r-1][c-1] = '2';
            else if (numberOfScorpionsAt(r, c) == 3)
                grid[r-1][c-1] = '3';
            else if (numberOfScorpionsAt(r, c) == 4)
                grid[r-1][c-1] = '4';
            else if (numberOfScorpionsAt(r, c) == 5)
                grid[r-1][c-1] = '5';
            else if (numberOfScorpionsAt(r, c) == 6)
                grid[r-1][c-1] = '6';
            else if (numberOfScorpionsAt(r, c) == 7)
                grid[r-1][c-1] = '7';
            else if (numberOfScorpionsAt(r, c) == 8)
                grid[r-1][c-1] = '8';
            else if (numberOfScorpionsAt(r, c) >= 9)
                grid[r-1][c-1] = '9';
        }
    
    // Indicate player's position
    if (m_player != nullptr)
    {
        char& gridChar = grid[m_player->row()-1][m_player->col()-1];
        if (m_player->isDead())
            gridChar = '*';
        else
            gridChar = '@';
    }
    
    // Draw the grid
    clearScreen();
    for (r = 0; r < rows(); r++)
    {
        for (c = 0; c < cols(); c++)
            cout << grid[r][c];
        cout << endl;
    }
    cout << endl;
    
    // Write message, scorpion, and player info
    cout << "There are " << scorpionCount() << " scorpions remaining." << endl;
    if (m_player == nullptr)
        cout << "There is no player." << endl;
    else
    {
        if (m_player->age() > 0)
            cout << "The player has lasted " << m_player->age() << " steps." << endl;
        if (m_player->isDead())
            cout << "The player is dead." << endl;
    }
}

bool Pit::addScorpion(int r, int c)
{
    if (! isPosInBounds(r, c))
        return false;
    
    // Don't add a scorpion on a spot with a player
    if (m_player != nullptr  &&  m_player->row() == r  &&  m_player->col() == c)
        return false;
    
    if (m_nScorpions == MAXSCORPIONS)
        return false;

    m_scorpions[m_nScorpions] = new Scorpion(this, r, c);
    m_nScorpions++;
    return true;
}

bool Pit::addPlayer(int r, int c)
{
    if (! isPosInBounds(r, c))
        return false;
    
    // Don't add a player if one already exists
    if (m_player != nullptr)
        return false;
    
    // Don't add a player on a spot with a scorpion
    if (numberOfScorpionsAt(r, c) > 0)
        return false;
    
    // Dynamically allocate a new Player and add it to the pit
    m_player = new Player(this, r, c);
    return true;
}

bool Pit::destroyOneScorpion(int r, int c)
{
    //Destroys One Scorpion
    for (int i = 0; i < m_nScorpions; i++)
    {
        if (m_scorpions[i]->row() == r && m_scorpions[i]->col() == c)
        {
            delete m_scorpions[i];
            
            while (i < m_nScorpions-1)
            {
                m_scorpions[i] = m_scorpions[i+1];
                i++;
            }
            m_nScorpions--;
            return true;
        }
    }
    return false;               //FAILSAFE
}

bool Pit::moveScorpions()
{
    //Defines movement of Scorpions
    for (int k = 0; k < m_nScorpions; k++)
    {
        m_scorpions[k]->move();
        if (m_scorpions[k]->row()==m_player->row() && m_scorpions[k]->col()==m_player->col())
            m_player->setDead();
    }
    
    // return true if the player is still alive, false otherwise
    return ! m_player->isDead();
}

bool Pit::isPosInBounds(int r, int c) const
{
    return (r >= 1  &&  r <= m_rows  &&  c >= 1  &&  c <= m_cols);
}

///////////////////////////////////////////////////////////////////////////
//  Game implementation
///////////////////////////////////////////////////////////////////////////

Game::Game(int rows, int cols, int nScorpions)
{
    if (nScorpions < 0)
    {
        cout << "***** Cannot create Game with negative number of scorpions!" << endl;
        exit(1);
    }
    if (nScorpions > MAXSCORPIONS)
    {
        cout << "***** Trying to create Game with " << nScorpions
        << " scorpions; only " << MAXSCORPIONS << " are allowed!" << endl;
        exit(1);
    }
    if (rows == 1  &&  cols == 1  &&  nScorpions > 0)
    {
        cout << "***** Cannot create Game with nowhere to place the scorpions!" << endl;
        exit(1);
    }
    
    // Create pit
    m_pit = new Pit(rows, cols);
    
    
    // Add player
    int rPlayer = randInt(1, rows);
    int cPlayer = randInt(1, cols);
    m_pit->addPlayer(rPlayer, cPlayer);
    
    // Populate with scorpions
    while (nScorpions > 0)
    {
        int r = randInt(1, rows);
        int c = randInt(1, cols);
        // Don't put a scorpion where the player is
        if (r == rPlayer  &&  c == cPlayer)
            continue;
        m_pit->addScorpion(r, c);
        nScorpions--;
    }
}

Game::~Game()
{
    delete m_pit;
}

void Game::play()
{
    m_pit->display();
    Player* player = m_pit->player();
    if (player == nullptr)
        return;
    
    while ( ! m_pit->player()->isDead()  &&  m_pit->scorpionCount() > 0)
    {
        cout << "Move (u/d/l/r//q): ";
        string action;
        getline(cin,action);
        if (action.size() == 0)
            player->stand();
        else
        {
            switch (action[0])
            {
                default:   // if bad move, nobody moves
                    cout << '\a' << endl;  // beep
                    continue;
                case 'q':
                    return;
                case 'u':
                case 'd':
                case 'l':
                case 'r':
                    player->move(decodeDirection(action[0]));
                    break;
            }
        }
        if ( ! player->isDead())
            m_pit->moveScorpions();
        m_pit->display();
    }
    if (m_pit->player()->isDead())
        cout << "You lose." << endl;
    else
        cout << "You win." << endl;
}

///////////////////////////////////////////////////////////////////////////
//  Auxiliary function implementation
///////////////////////////////////////////////////////////////////////////

// Return a uniformly distributed random int from min to max, inclusive
int randInt(int min, int max)
{
    if (max < min)
        swap(max, min);
    static random_device rd;
    static mt19937 generator(rd());
    uniform_int_distribution<> distro(min, max);
    return distro(generator);
}

int decodeDirection(char dir)
{
    switch (dir)
    {
        case 'u':  return UP;
        case 'd':  return DOWN;
        case 'l':  return LEFT;
        case 'r':  return RIGHT;
    }
    return -1;  // bad argument passed in!
}

bool directionToDeltas(int dir, int& rowDelta, int& colDelta)
{
    switch (dir)
    {
        case UP:     rowDelta = -1; colDelta =  0; break;
        case DOWN:   rowDelta =  1; colDelta =  0; break;
        case LEFT:   rowDelta =  0; colDelta = -1; break;
        case RIGHT:  rowDelta =  0; colDelta =  1; break;
        default:     return false;
    }
    return true;
}

///////////////////////////////////////////////////////////////////////////
//  main()
///////////////////////////////////////////////////////////////////////////

int main()
{
    // Create a game
    Game g(5, 10, 3);
    
    // Play the game
    g.play();

}

///////////////////////////////////////////////////////////////////////////
//  clearScreen implementation
///////////////////////////////////////////////////////////////////////////

// DO NOT MODIFY OR REMOVE ANY CODE BETWEEN HERE AND THE END OF THE FILE!!!
// THE CODE IS SUITABLE FOR VISUAL C++, XCODE, AND g++ UNDER LINUX.

// Note to Xcode users:  clearScreen() will just write a newline instead
// of clearing the window if you launch your program from within Xcode.
// That's acceptable.

#ifdef _MSC_VER  //  Microsoft Visual C++

#include <windows.h>

void clearScreen()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    DWORD dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
    COORD upperLeft = { 0, 0 };
    DWORD dwCharsWritten;
    FillConsoleOutputCharacter(hConsole, TCHAR(' '), dwConSize, upperLeft,
                               &dwCharsWritten);
    SetConsoleCursorPosition(hConsole, upperLeft);
}

#else  // not Microsoft Visual C++, so assume UNIX interface

#include <iostream>
#include <cstring>
#include <cstdlib>

void clearScreen()  // will just write a newline in an Xcode output window
{
    static const char* term = getenv("TERM");
    if (term == nullptr  ||  strcmp(term, "dumb") == 0)
        cout << endl;
    else
    {
        static const char* ESC_SEQ = "\x1B[";  // ANSI Terminal esc seq:  ESC [
        cout << ESC_SEQ << "2J" << ESC_SEQ << "H" << flush;
    }
}

#endif
