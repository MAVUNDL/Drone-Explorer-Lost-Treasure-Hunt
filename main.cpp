#include "Game.h"
#include <iostream>

using namespace std;
using namespace ForestSpace;

int main(int argc, char** argv)
{
    if(argc !=5)
    {
        cerr << "The number of arguments is either greater or less than the expected number, check the programm arguements" << endl;
        exit(Err_argc);
    }
    //my variables
    int Rows = convert(argv[1]);
    int columns = convert(argv[2]);
    int Tower_Destroy = convert(argv[3]);
    int No_map_piece = convert(argv[4]);

    My_Game stcGame = Initialize(Rows,columns,No_map_piece);
    char chInput = '\0';
    bool blnContinue = true;
    do
    {
        // printing the game
        Printing_game(stcGame);
        //get input
        cout << "Selection: ";
        cin >> chInput;

        //handle movement
        switch(chInput)
        {
        case 'w':
            Moving_drone(stcGame, move_up,Tower_Destroy);
            break;
        case 's':
            Moving_drone(stcGame, move_down,Tower_Destroy);
            break;
        case 'a':
            Moving_drone(stcGame, move_left,Tower_Destroy);
            break;
        case 'd':
            Moving_drone(stcGame, move_right,Tower_Destroy);
            break;
        case 'q':
            Moving_drone(stcGame, move_top_left,Tower_Destroy);
            break;
        case 'e':
            Moving_drone(stcGame, move_top_right,Tower_Destroy);
            break;
        case 'z':
            Moving_drone(stcGame, move_bottom_left,Tower_Destroy);
            break;
        case 'c':
            Moving_drone(stcGame, move_bottom_right,Tower_Destroy);
            break;
        case 'r':
            if(stcGame.Battery > 2)
            {
                scan_for_Pieces(stcGame);
                stcGame.Battery-=2;
            }
            else
            {
                cout << "The is not enough battery to scan" << endl;
                pause();
            }
            break;
        case 'x':
            blnContinue = false;
            break;
        default:
            cerr << "Incorrect option. Please try again" << endl;
            pause();

        }
        Update_game(stcGame);
    }
    while(blnContinue);
    //deleting memory associated with the 2d array
    De_allocate_Memory(stcGame.gameArr,Rows);

    return success;
}
