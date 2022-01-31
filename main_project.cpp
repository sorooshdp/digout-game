#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <fstream>
#include <string>

/// global variables,so we don't have to use pointers for
/// passing the variables between functions.
char GameField[5][10],
    Action;
int InitialLifeAmount,
    LifeAmount,
    Score,
    Rocks,
    RocksAmount,
    Coins,
    CoinsAmount,
    Elixir,
    ElixirAmount,
    Bombs,
    BombsAmount,
    Player_x,
    Player_y;
bool Run_Game;

using namespace std;

// declaring all the functions.
bool CheckLife_Score();
void RunGame();
void SetGlobalValues();
void BuildGameField();
void PrintGameField();
void GetInput();
void DoAction();
void PrintResult();
void ApplyGravity();
void MainMenu();
void PrintRules();
void SetInitialAmount();
void SetAmount();
void OpenFile();
void WriteRecord();
void WriteName();

int main()
{

  SetInitialAmount();
  MainMenu();

  return 0;
}

/// prints the menu for the game until user
/// selects number 4.
void MainMenu()
{
  char MenuNumber;

  do
  {
    system("cls");
    cout << "1.start game\n"
         << "2.settings\n"
         << "3.records\n"
         << "4.exit\n\n"
         << "select a number";
    MenuNumber = getch();
    switch (MenuNumber)
    {

    case '1':
      system("cls");
      RunGame();

      break;

    case '2':
      system("cls");
      SetAmount();

      break;

    case '3':
      system("cls");
      OpenFile();
      break;

    case '4':
    exit(0);
      break;
    }

  } while (true);

}

void RunGame()
{
  SetGlobalValues();
  PrintRules();
  BuildGameField();
  WriteName();

  do
  {
    PrintGameField(); /// prints information for user.
    GetInput();       /// gets input form user.
    DoAction();       /// receives the input and updates the information.
    system("cls");    /// clears the screen for the next outputs.
  } while (Run_Game); /// the function does this steps until player wins.

  PrintResult();

  getch(); /// to hold the output from the "PrintResult" function
           /// so user can see the result.
}

/// the game board is made in the "BuildGameField" from the information in this function
/// we can change this information in the "SetAmount" function.
void SetInitialAmount()
{
  InitialLifeAmount = 2;
  CoinsAmount = 1,
  BombsAmount = 2,
  RocksAmount = 3,
  ElixirAmount = 1;
}

/// These values ​​change once we play the game.
/// So we have to return them to the right amount for the next game.
void SetGlobalValues()
{
  LifeAmount = InitialLifeAmount;
  Score = 0,
  Rocks = 0,
  Coins = 0,
  Elixir = 0,
  Bombs = 0,
  Player_x = 0,
  Player_y = 0;
  Run_Game = 1;
}

/// randomly puts characters in the 2D array(GameField[5][10]).
void BuildGameField()
{
  srand(time(NULL));

  for (int y = 0; y < 5; y++)
  {
    for (int x = 0; x < 10; x++)
    {
      if ((x == 0) && (y == 0))
      {
        GameField[y][x] = '!';
      }
      else if ((x < (rand() % 10)) && ((y > (rand() % 5)) && Rocks < RocksAmount))
      {
        GameField[y][x] = '@';
        Rocks++;
      }
      else if ((x > (rand() % 10)) && ((y > (rand() % 5)) && Coins < CoinsAmount))
      {
        GameField[y][x] = '$';
        Coins++;
      }
      else if ((x > (rand() % 10)) && ((y > (rand() % 5)) && Elixir < ElixirAmount))
      {
        GameField[y][x] = '+';
        Elixir++;
      }
      else if ((x > (rand() % 10)) && ((y < (rand() % 5)) && Bombs < BombsAmount))
      {
        GameField[y][x] = 'O';
        Bombs++;
      }
      else
      {
        GameField[y][x] = '#';
      }
    }
  }
}

void PrintGameField()
{
  for (int y = 0; y < 5; y++)
  {
    cout << '\t';
    for (int x = 0; x < 10; x++)
    {
      cout << GameField[y][x] << " ";
    }
    cout << '\n';
  }
  cout << '\n';
}

void GetInput()
{
  cout << "(press q to leave.)\n\n"
       << "life=>" << LifeAmount << '\n'
       << "dig/move=>";
  Action = getch();
}

/// updates the game field beside the input taken in the "GetInput" function.
void DoAction()
{
  if (Action == 'i')
  {
    /// player can only dig through "#" blocks.
    if (GameField[Player_y - 1][Player_x] == '#')
    {
      GameField[Player_y - 1][Player_x] = '_';
    }
  }
  if (Action == 'k')
  {
    if (GameField[Player_y + 1][Player_x] == '#')
    {
      GameField[Player_y + 1][Player_x] = '_';
    }
  }
  if (Action == 'j')
  {
    if (GameField[Player_y][Player_x - 1] == '#')
    {
      GameField[Player_y][Player_x - 1] = '_';
    }
  }
  if (Action == 'l')
  {
    if (GameField[Player_y][Player_x + 1] == '#')
    {
      GameField[Player_y][Player_x + 1] = '_';
    }
  }

  /// when player moves through a block we have to check if there is any
  /// rocks coins elixir or bombs in that block and update the board according to that.
  /// and we also have to update the player location with each move (the "Player_x" and
  ///"Player_y" global variables).
  if (Action == 'w')
  {
    if (GameField[Player_y - 1][Player_x] == '_')
    {
      GameField[Player_y][Player_x] = '_';
      GameField[Player_y - 1][Player_x] = '!';
      Player_y--;
    }
    else if (GameField[Player_y - 1][Player_x] == '$')
    {
      GameField[Player_y][Player_x] = '_';
      GameField[Player_y - 1][Player_x] = '!';
      Player_y--;
      Score++;
    }
    else if (GameField[Player_y - 1][Player_x] == '+')
    {
      GameField[Player_y][Player_x] = '_';
      GameField[Player_y - 1][Player_x] = '!';
      Player_y--;
      LifeAmount++;
    }
    else if (GameField[Player_y - 1][Player_x] == 'O')
    {
      GameField[Player_y][Player_x] = '_';
      GameField[Player_y - 1][Player_x] = '!';
      Player_y--;
      LifeAmount--;
    }
  }
  if (Action == 'a')
  {
    if (GameField[Player_y][Player_x - 1] == '_')
    {
      GameField[Player_y][Player_x] = '_';
      GameField[Player_y][Player_x - 1] = '!';
      Player_x--;
    }
    else if (GameField[Player_y][Player_x - 1] == '$')
    {
      GameField[Player_y][Player_x] = '_';
      GameField[Player_y][Player_x - 1] = '!';
      Player_x--;
      Score++;
    }
    else if (GameField[Player_y][Player_x - 1] == '+')
    {
      GameField[Player_y][Player_x] = '_';
      GameField[Player_y][Player_x - 1] = '!';
      Player_x--;
      LifeAmount++;
    }
    else if (GameField[Player_y][Player_x - 1] == 'O')
    {
      GameField[Player_y][Player_x] = '_';
      GameField[Player_y][Player_x - 1] = '!';
      Player_x--;
      LifeAmount--;
    }
  }
  if (Action == 's')
  {
    if (GameField[Player_y + 1][Player_x] == '_')
    {
      GameField[Player_y][Player_x] = '_';
      GameField[Player_y + 1][Player_x] = '!';
      Player_y++;
    }
    else if (GameField[Player_y + 1][Player_x] == '$')
    {
      GameField[Player_y][Player_x] = '_';
      GameField[Player_y + 1][Player_x] = '!';
      Player_y++;
      Score++;
    }
    else if (GameField[Player_y + 1][Player_x] == '+')
    {
      GameField[Player_y][Player_x] = '_';
      GameField[Player_y + 1][Player_x] = '!';
      Player_y++;
      LifeAmount++;
    }
    else if (GameField[Player_y + 1][Player_x] == 'O')
    {
      GameField[Player_y][Player_x] = '_';
      GameField[Player_y + 1][Player_x] = '!';
      Player_y++;
      LifeAmount--;
    }
  }
  if (Action == 'd')
  {
    if (GameField[Player_y][Player_x + 1] == '_')
    {
      GameField[Player_y][Player_x] = '_';
      GameField[Player_y][Player_x + 1] = '!';
      Player_x++;
    }
    else if (GameField[Player_y][Player_x + 1] == '$')
    {
      GameField[Player_y][Player_x] = '_';
      GameField[Player_y][Player_x + 1] = '!';
      Player_x++;
      Score++;
    }
    else if (GameField[Player_y][Player_x + 1] == '+')
    {
      GameField[Player_y][Player_x] = '_';
      GameField[Player_y][Player_x + 1] = '!';
      Player_x++;
      LifeAmount++;
    }
    else if (GameField[Player_y][Player_x + 1] == 'O')
    {
      GameField[Player_y][Player_x] = '_';
      GameField[Player_y][Player_x + 1] = '!';
      Player_x++;
      LifeAmount--;
    }
  }
  if (Action == 'q') /// for going back to the main menu.
  {
    MainMenu();
  }
  ApplyGravity();
}

void ApplyGravity()
{
  while (true)
  {
    int Falls = 0;///for counting falls each time loop starts.
    for (int y = 0; y < 5; y++)
    {
      for (int x = 0; x < 10; x++)
      {
        if (GameField[y][x] == '@')
        {
          if ((GameField[y + 2][x] == '!') && (GameField[y + 1][x] == '_'))/// to check if a rock falls on player
          {
            Falls++;
            LifeAmount = 0; /// stops the main loop by turning "Run_Game" to zero in "CheckLife_Score" function.
            GameField[y][x] = '_';
            GameField[y + 2][x] = '@';
          }
          else if (GameField[y + 1][x] == '_')///to update rock's place if there is free space under it.
          {
            Falls++;
            GameField[y][x] = '_';
            GameField[y + 1][x] = '@';
          }
        }
        else if (GameField[y][x] == '$')
        {
          if ((GameField[y + 2][x] == '!') && (GameField[y + 1][x] == '_'))
          {
            Falls++;
            GameField[y][x] = '_';
            GameField[y + 2][x] = '!';
            Score++;
          }
          else if (GameField[y + 1][x] == '_')
          {
            Falls++;
            GameField[y][x] = '_';
            GameField[y + 1][x] = '$';
          }
        }
        else if (GameField[y][x] == '+')
        {
          if ((GameField[y + 2][x] == '!') && (GameField[y + 1][x] == '_'))
          {
            Falls++;
            GameField[y][x] = '_';
            GameField[y + 2][x] = '!';
            LifeAmount++;
          }
          else if (GameField[y + 1][x] == '_')
          {
            Falls++;
            GameField[y][x] = '_';
            GameField[y + 1][x] = '+';
          }
        }
        else if (GameField[y][x] == 'O')
        {
          if ((GameField[y + 2][x] == '!') && (GameField[y + 1][x] == '_'))
          {
            Falls++;
            GameField[y][x] = '_';
            GameField[y + 2][x] = '!';
            LifeAmount--;
          }
          else if (GameField[y + 1][x] == '_')
          {
            Falls++;
            GameField[y][x] = '_';
            GameField[y + 1][x] = 'O';
          }
        }
      }
    }
    if (Falls == 0) /// stops the loop if there is no falls.
    {
      break;
    }
  }
  CheckLife_Score();
}

///to break from the "RunGame" function if player has win or lose the game.
bool CheckLife_Score()
{
  if (LifeAmount == 0 || Score == CoinsAmount)
  {
    Run_Game = 0;
  }
  else
  {
    Run_Game = 1;
  }
  return Run_Game;
}

void PrintResult()
{
  WriteRecord();

  if (LifeAmount == 0)
  {
    cout
        << '\n'
        << "game over!press any key. ";
  }
  else if (CoinsAmount == Score)
  {
    cout
        << '\n'
        << "well done!you have collected all the coins.press any key.";
  }
}

void PrintRules()
{
  cout << "hi!welcome to dig out."
       << '\n'
       << "the goal is to collect all the coins with digging"
       << "=>"
       << "(i=up,k=down,j=left,l=right)"
       << '\n'
       << "and moving"
       << "=>"
       << "(w=up,s=down,a=right,d=left)"
       << '\n'
       << "you can get one life by getting elixir(+).\n\n";
}


void SetAmount()
{
  char Element, Amount;

  cout << "select the element you want to change.\n"
       << "1.life\n"
       << "2.rock\n"
       << "3.elixir\n"
       << "4.bombs\n"
       << "5.coins\n\n"
       << "select a number(press q to leave).";

  Element = getch();

  system("cls");

  switch (Element)
  {
  case '1':
    cout << "set your amount and press enter==>";
    cin >> InitialLifeAmount;

    break;

  case '2':
    cout << "set your amount and press enter==>";
    cin >> RocksAmount;

    break;

  case '3':
    cout << "set your amount and press enter==>";
    cin >> ElixirAmount;

    break;

  case '4':
    cout << "set your amount and press enter==>";
    cin >> BombsAmount;

    break;

  case '5':
    cout << "set your amount and press enter==>";
    cin >> CoinsAmount;

    break;

  case 'q':
    system("cls");
    MainMenu();

    break;
  }
}

///for opening the file and reading the information in it.
void OpenFile()
{

  fstream records;
  string name;

  records.open("records.txt", ios::in);
  if (records.is_open())
  {
    string line;
    while (getline(records, line))
    {
      cout << line << "\n\n";
    }
    records.close();
  }

  cout << "press any key to leave.";

  getch();
}

///this function append the name of the user in existing file.
void WriteName()
{
  fstream records;
  string name;

  cout << "please enter your name first\n";

  records.open("records.txt", ios::app);

  if (records.is_open())
  {
    cin >> name;
    records << name;
    records.close();
  }
}

///this function appends player record in existing file after each game.
void WriteRecord()
{
  fstream records;
  records.open("records.txt", ios::app);

  if (records.is_open())
  {
    records << "  |  " << Score << '\n';
    records.close();
  }
}