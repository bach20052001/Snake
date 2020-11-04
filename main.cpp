/// Define Arrow Key
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

/// Lib
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <time.h>

using namespace std;

/// Check GameOver
bool _GameOver;

/// Map
const int width = 20;
const int height = 20;

/// Food
int _FruitX;
int _FruitY;

/// HeadOfSnake
int _HeadSnakeX;
int _HeadSnakeY;

/// TailOfSnake
int _nTailSnake; /// Length
int TailSnakeX[401];
int TailSnakeY[401];

/// Input
enum direction {
    STOP = 0,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

/// Speed
int _speed;

/// Controller
direction _Player;

/// Prevent head turning
direction _TempDirection;

/// Score
int _score;

///=========================

/// Initial Set Up
void Setup(){
    system("CLS");
    _GameOver = false;
    _score = 0;
    _speed = 1;
    _Player = STOP;
    _HeadSnakeX = width / 2;
    _HeadSnakeY = height / 2;
    _FruitX = rand() % width;
    _FruitY = rand() % height;
    _nTailSnake = 0;
}
///=========================

/// Output
void Draw(){
    system("CLS");
    for (int i = 0;i < height;i++)
    {
        cout<<"\n";
        /// Initial Map
        for (int j = 0;j < width;j++)
        {
            if ((i == _FruitX)&&(j == _FruitY))
                if (_score % 50 == 0 && _score != 0) cout<<"$";
                else
                    cout << "*";
            else
            if (i == _HeadSnakeX-1&&j == _HeadSnakeY-1) cout<<"O";
            else
            if (i==0) cout<<"X";
            else
            if (i==height-1) cout<<"X";
            else
            if (j==0) cout<<"|";
            else
            if (j==width-1) cout<<"|";
            else
            {
                bool _printTail = false;
                for (int k = 0; k < _nTailSnake; k++)
                {
                    if (TailSnakeX[k] == i && TailSnakeY[k] == j)
                    {
                        if (k != _nTailSnake - 1){
                           cout<<"o";
                        }
                        else
                        {
                            cout<<"+";
                        }
                        _printTail = true;
                    }
                }
                if (!_printTail) cout<<" ";
            }
        }
        ///============
    }
    ///Score
    cout<<"\nScore : "<<_score<<"\n";
}
///=========================

/// Get Input From Player
void Input(){
    if (_kbhit())
    {
        switch (_getch())
        {
            case 'a':
            case KEY_LEFT:
                if (_TempDirection != RIGHT){
                    _Player = LEFT;
                }
                break;
            case 'd':
            case KEY_RIGHT:
                if (_TempDirection != LEFT){
                    _Player = RIGHT;
                }
                break;
            case 'w':
            case KEY_UP:
                if (_TempDirection != DOWN){
                    _Player = UP;
            }
                break;
            case 's':
            case KEY_DOWN:
                if (_TempDirection != UP){
                    _Player = DOWN;
                }
                break;
            case 'x':
                _GameOver = true;
                break;
            default:
                break;
        }
    }
    _TempDirection = _Player;

}
///=========================

/// Solve
void Load(){

    ///Reload Snake
    int _tempX = TailSnakeX[0];
    int _tempY = TailSnakeY[0];
    TailSnakeX[0] = _HeadSnakeX - 1;
    TailSnakeY[0] = _HeadSnakeY - 1;
    for (int i=1;i<_nTailSnake;i++)
        {
            int _tempXX = TailSnakeX[i];
            int _tempYY = TailSnakeY[i];
            TailSnakeX[i] = _tempX;
            TailSnakeY[i] = _tempY;
            _tempX = _tempXX;
            _tempY = _tempYY;

    }

    /// Detect Kill Yourself
    for (int i=1;i<_nTailSnake;i++)
        {
        if (_HeadSnakeX - 1 == TailSnakeX[i]&&_HeadSnakeY - 1 == TailSnakeY[i]){
            _GameOver =  true;
        }
    }



    /// Get Direction
    switch (_Player)
    {
        case LEFT:
                _HeadSnakeY-=_speed;
            break;
        case RIGHT:
                _HeadSnakeY+=_speed;
            break;
        case UP:
                _HeadSnakeX-=_speed;
            break;
        case DOWN:
                _HeadSnakeX+=_speed;
            break;
        default:
            break;
    }


    /// Eat
    if (_HeadSnakeX - 1 == _FruitX && _HeadSnakeY - 1  == _FruitY) {
        srand(time(0));
        _FruitX = rand() % (width-1) + 1;
        _FruitY = rand() % (height-1) + 1;
        if (_score % 50 == 0 &&_score != 0){
            _score += 20;
            _nTailSnake+=2;
        }
        else{
        _score += 10;
        _nTailSnake++;
        }
    }

    /// Bump into the wall
    if (_HeadSnakeX == 1 || _HeadSnakeY == 1 || _HeadSnakeX == height || _HeadSnakeY == width){
        _GameOver = true;
    }
}

///=========================

/// GamePlay
void PlayGame(){
    Setup();
    while (!_GameOver){
        Draw();
        Input();
        Load();
        Sleep(50);
    }
    /// Do you want replay ???
    if (_GameOver)
    {
        cout<<"\nOops\nGame Over!!!\n";
        cout<<"\nREPLAY : Y/N ? : Press Y to continue or Press other key to exit !\n";
        char str;
        cin>>str;
        if (str == 'Y'||str == 'y'){
            fflush(stdin);
            PlayGame();
        }
        else {
            system("CLS");
            cout<<"THANKS FOR PLAYING MY GAMES :)";
            exit(0);
        }
    }
}


/// Main
int main()
{
    PlayGame();
    getch();
    return 0;
}
