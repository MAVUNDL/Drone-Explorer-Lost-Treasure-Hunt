#include "Game.h"

namespace ForestSpace
{
    int convert(string word)
    {
        int Term = 0;

        stringstream ss {word};
        ss >> Term;

        if(ss.fail())
        {
            cerr << "Could not convert " << Term << " to an integer" << endl;
            exit(Err_conv);
        }
        return Term;
    }

    int Random_Generator(int lower, int upper)
    {
        assert(upper>lower);
        int range = upper - lower + 1;
        return rand()%range+lower;
    }

    void pause()
    {
        cin.ignore(100, '\n');
        cout << "Press enter to try again" << endl;
        cin.get();
    }
     TwoArray allocate_Memory(int rows,int cols)
     {
         TwoArray gameArr;
         gameArr = new OneArray[rows];
         for(int i = 0; i < rows; i++)
         {
             gameArr[i] = new int[cols];
             for(int n = 0; n < cols; n++)
             {
                 gameArr[i][n] = Empty_space;
             }
         }
         return gameArr;
     }

     My_Game Initialize(int rows,int cols, int Map_p_numb)
     {
         My_Game stcGame;
         stcGame.gameArr = allocate_Memory(rows, cols);
         stcGame.rows = rows;
         stcGame.cols = cols;
         stcGame.Number_of_pieces = Map_p_numb;
         stcGame.Battery = 10;
         stcGame.Total_Map_piece = 0;
         stcGame.tstatus = running;

         //place the features in the 2d array
         int intRow = 0;
         int intCol = 0;

         //place map pieces
         place_map_piece(stcGame,intRow,intCol,Map_p_numb);

         //place the trees
         for(int i = 0; i < rows; i++)
         {
             for(int n = 0; n < cols; n++)
             {
                 if(stcGame.gameArr[i][n] == Empty_space)
                 {
                     stcGame.gameArr[i][n] = trees;
                 }
                 else if(stcGame.gameArr[i][n] == map_piece)
                 {

                     stcGame.gameArr[i][n]= tree_map;
                 }

             }
         }

         //place player
         Place_player(stcGame,rows,cols,1);

         //placing the tower
         for(int i = 0; i < rows; i++)
         {
            int random_col = Random_Generator(0, cols-1);
            if(stcGame.gameArr[i][random_col] != player || stcGame.gameArr[i][random_col] != map_piece)
            {
                stcGame.gameArr[i][random_col] = tower;
            }
         }

         return stcGame;
     }

     //place player
     void Place_player(My_Game& stcGame,int rows,int cols, int number)
     {
         for(int i = 0; i < number; i++)
         {
             stcGame.PRow = Random_Generator(0, stcGame.rows -1);
             stcGame.Pcols= Random_Generator(stcGame.cols -2, stcGame.cols - 1);

             if(stcGame.gameArr[stcGame.PRow][stcGame.Pcols] != map_piece)
             {
                 stcGame.gameArr[stcGame.PRow][stcGame.Pcols] = player;
             }
         }
     }
     //place the map pieces
     void place_map_piece(My_Game& stcGame,int rows,int cols, int number_s)
     {
         int counter = 0;
         srand(time(nullptr));

         while(counter <= number_s)
         {
             rows = Random_Generator(0, stcGame.rows-1);
             cols = Random_Generator(0, stcGame.cols-1);

             if(stcGame.gameArr[rows][cols] != player)
             {
                 stcGame.gameArr[rows][cols] = map_piece;
                 counter++;
             }
         }

     }

     void Printing_game(My_Game stcGame)
     {
         assert(stcGame.gameArr != nullptr);
         system("cls");

         for(int r = 0; r <stcGame.rows; r++)
         {
             for(int c = 0; c <stcGame.cols; c++)
             {
                 cout << Feature[stcGame.gameArr[r][c]] << " ";
             }
             cout << endl;
         }
         cout << "Menu Option" << endl;
         cout << "Battery: " << stcGame.Battery << endl;
         cout << "Collected Pieces: " << stcGame.Total_Map_piece << endl;
         cout << "w). Move up" << endl;
         cout << "s). Move down" << endl;
         cout << "a). Move left" << endl;
         cout << "d). Move right" << endl;
         cout << "q). Move top left" << endl;
         cout << "e). Move top right" << endl;
         cout << "z). Move bottom left" << endl;
         cout << "c). Move bottom right" << endl;
         cout << "r). Scan for map piece" << endl;
         cout << "x). Quit" << endl;
     }
     //test if we still inside our boundery
     bool We_are_Still_in_world(int rows,int cols, int intRow,int intCol)
     {
         return (intRow >= 0 && intRow < rows && intCol >= 0 && intCol < cols);
     }

     void scan_for_Pieces(My_Game& stcGame)
     {
         assert(stcGame.gameArr != nullptr);
         for(int r = stcGame.PRow-1; r <=stcGame.PRow+1; r++)
         {
             for(int c = stcGame.Pcols-1; c <=stcGame.Pcols+1; c++)
             {
                 if(We_are_Still_in_world(stcGame.rows,stcGame.cols,r,c))
                 {
                     if(stcGame.gameArr[r][c] == tree_map)
                     {
                         stcGame.gameArr[r][c] = map_piece;
                     }
                 }
             }
         }

     }

     //moving the player
     void Moving_drone(My_Game& stcGame, int intMovement,  int Des_tower)
     {
         assert(stcGame.gameArr != nullptr);

         // current location of player
         int intDrow = stcGame.PRow;
         int intDcol = stcGame.Pcols;


         // handle the movement
         switch(intMovement)
         {
         case move_up:
             intDrow--;
             stcGame.Battery--;
             tower_destroy(stcGame,Des_tower);
            break;
         case move_down:
            intDrow++;
            stcGame.Battery--;
            tower_destroy(stcGame, Des_tower);
            break;
         case move_left:
            intDcol--;
            stcGame.Battery--;
            tower_destroy(stcGame, Des_tower);
            break;
         case move_right:
            intDcol++;
            stcGame.Battery--;
            tower_destroy(stcGame, Des_tower);
            break;
         case move_top_left:
             intDrow--;
             intDcol--;
             stcGame.Battery--;
             tower_destroy(stcGame, Des_tower);
             break;
         case move_top_right:
            intDrow--;
            intDcol++;
            stcGame.Battery--;
            tower_destroy(stcGame, Des_tower);
            break;
         case move_bottom_left:
            intDrow++;
            intDcol--;
            stcGame.Battery--;
            tower_destroy(stcGame, Des_tower);
            break;
         case move_bottom_right:
            intDrow++;
            intDcol++;
            stcGame.Battery--;
            tower_destroy(stcGame, Des_tower);
            break;
         }
         if(We_are_Still_in_world(stcGame.rows,stcGame.cols,intDrow,intDcol))
         {
             int intDfeature = stcGame.gameArr[intDrow][intDcol];

             if(intDfeature == trees)
             {
                 stcGame.gameArr[intDrow][intDcol] = player;

                 stcGame.gameArr[stcGame.PRow][stcGame.Pcols] = trees;

             }
             if(intDfeature == tower)
             {
                 stcGame.gameArr[intDrow][intDcol] = player;
                 stcGame.Battery+=10;
                 stcGame.gameArr[stcGame.PRow][stcGame.Pcols] = tower;
             }
             if(intDfeature == map_piece)
             {
                 stcGame.gameArr[intDrow][intDcol] = player;
                 char input = '\0';
                 cout << "Pick: y/n: ";
                 cin >> input;
                 if(input == 'y')
                 {
                     stcGame.Total_Map_piece++;
                     stcGame.gameArr[stcGame.PRow][stcGame.Pcols] = trees;
                 }
                 else
                 {
                     stcGame.gameArr[stcGame.PRow][stcGame.Pcols] = tree_map;
                 }

             }
         }
         else
         {
             return;
             pause();
         }
         stcGame.PRow =intDrow;
         stcGame.Pcols = intDcol;
     }

     void Update_game(My_Game& stcGame)
     {
         if(stcGame.Battery < 0)
         {
             cout << "******************************************************************" << endl;
             cout << "           You ran out of battery and crashed onto the trees      " << endl;
             cout << "******************************************************************" << endl;
             stcGame.tstatus = lose;
             exit(0);
         }

        if(stcGame.Total_Map_piece == stcGame.Number_of_pieces)
        {
            cout << "******************************************************************" << endl;
            cout << "        congratulations you have collected all the map pieces     " << endl;
            cout << "******************************************************************" << endl;
            stcGame.tstatus = win;
            exit(0);
        }

     }
     // Handles tower being destroyed
     void tower_destroy(My_Game& stcGame, int destroy)
     {
         int chance = Random_Generator(0, 100);

         if(chance == destroy)
         {
             int no_tower = 0;
             for(int i = 0; i < stcGame.rows; i++)
             {
                 for(int n = 0; n < stcGame.cols; n++)
                 {
                     if(stcGame.gameArr[i][n] == tower)
                     {
                         no_tower++;
                     }
                 }
             }

             if(no_tower > 0)
             {
                 bool tower_des = false;
                 while(!tower_des)
                 {
                 int row = Random_Generator(0, stcGame.rows);
                 int col = Random_Generator(0, stcGame.cols);

                 if(stcGame.gameArr[row][col] == tower)
                 {
                     stcGame.gameArr[row][col] = Empty_space;
                     tower_des = true;
                 }
                 }
             }
         }
     }

     void De_allocate_Memory(TwoArray& gameArr, int rows)
     {
         assert(gameArr != nullptr);
         for(int i = 0; i < rows; i++)
            delete[] gameArr[i];

         delete[] gameArr;
         gameArr = nullptr;
     }


}
