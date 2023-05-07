#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#define NDEBUG

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <cctype>
#include <sstream>

using namespace std;
namespace ForestSpace
{
    // for declaring errors
    enum Errors
    {
        Err_argc,
        Err_conv,
        success
    };

    // for declaring my features
    enum My_Features
    {
        Empty_space,
        player,
        map_piece,
        trees,
        tower,
        tree_map
    };

    enum status
    {
        running,
        quit,
        win,
        lose
    };

    //for declaring my movements
    enum Movements
    {
        move_left,
        move_right,
        move_up,
        move_down,
        move_top_right,
        move_top_left,
        move_bottom_right,
        move_bottom_left
    };

    const char Feature[] = {'.', 'P', '#', 'X', 'T', 'X'};

    typedef int* OneArray;
    typedef int** TwoArray;

    struct My_Game
    {
        TwoArray gameArr; // this is my 2d array
        int rows; // my rows
        int cols; // my columns
        int PRow; // player row
        int Pcols; // player columns
        int Total_Map_piece; // total map pieces to be collected
        int Battery; // battery level
        int Number_of_pieces;
        status tstatus;
    };


    int convert(string word);
    void pause();
    void De_allocate_Memory(TwoArray& gameArr, int rows);
    void Update_game(My_Game& stcGame);
    My_Game Initialize(int rows,int cols,int Map_p_numb);
    void scan_for_Pieces(My_Game& stcGame);
    void Place_player(My_Game& stcGame,int rows,int cols, int number);
    void place_map_piece(My_Game& stcGame,int rows,int cols, int number_s);
    int Random_Generator(int lower, int upper);
    void Printing_game(My_Game stcGame);
    void Moving_drone(My_Game& stcGame, int intMovement,  int Des_tower);
    bool We_are_Still_in_world(int rows,int cols, int intRow,int intCol);
    void tower_destroy(My_Game& stcGame, int destroy);

}



#endif // GAME_H_INCLUDED
