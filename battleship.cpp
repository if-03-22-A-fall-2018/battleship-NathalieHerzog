/*-----------------------------------------------------------------------------
 *				HTBLA-Leonding / Class: <your class name here>
 *-----------------------------------------------------------------------------
 * Exercise Number: #exercise_number#
 * File:			battleship.c
 * Author(s):		Peter Bauer
 * Due Date:		#due#
 *-----------------------------------------------------------------------------
 * Description:
 * <your description here>
 *-----------------------------------------------------------------------------
*/
#include <stdio.h>
#include "battleship.h"

CellContent arrMy[FIELDSIZE][FIELDSIZE];
CellContent arrOp[FIELDSIZE][FIELDSIZE];
CellContent arrGuess[FIELDSIZE][FIELDSIZE];

/**
*** Loads the two files battleship.my and battleship.op which hold the fields
*** of the players. The files hold a stream of 10 times 10 values of type
*** CellContent.
*/
void load_game()
{
    FILE* fd_op = fopen("battleship.op", "r");
    FILE* fd_my = fopen("battleship.my", "r");

    for(int i = 0; i < FIELDSIZE; i++)
    {
      for(int u = 0; u < FIELDSIZE; u++)
      {
        fread(&arrMy[i][u], sizeof(CellContent), 1, fd_my);
        fread(&arrOp[i][u], sizeof(CellContent), 1, fd_op);
        arrGuess[i][u] = Unknown;
      }
    }
}

/**
*** @param row The row where we get the shot.
*** @param col The col where we get the shot.
*** @return The value of cell indicated by row and column of the own field (filled
*** with the values of battleship.my). If row/col point outside the field the
*** value OutOfRange is returned.
*/
CellContent get_shot(int row, int col)
{
  if(!is_outofrange(row, col))
  {
    return arrMy[row][col];
  }

  return OutOfRange;
}

bool is_outofrange(int row, int col)
{
  if(row >= 0 && col >= 0 && row != FIELDSIZE && col != FIELDSIZE)
  {
    return false;
  }

  return true;
}

/**
*** Sets the row and column of the my guesses table to the value held in the
*** opponents field. If this is a boat all surrounding cells are marked as water.
*** @param row The row where we place the shot
*** @param col The column where we place the shot.
*** @return True if target field is valid, i.e., inside the field, False otherwise.
*/
bool shoot(int row, int col)
{
  if(!is_outofrange(row, col))
  {
    if(arrOp[row][col] == Boat)
    {
      for(int i = row - 1; i <= row + 1; i++)     
      {
        for(int u = col - 1; u <= col + 1; u++)
        {
          if(!is_outofrange(i, u) && arrOp[i][u] != Boat)
          {
            arrGuess[i][u] = Water;
          }
        }
      }
    }
    arrGuess[row][col] = arrOp[row][col];

    return true;
  }

  return false;
}

/**
*** @param row The row where we want to get our own guess.
*** @param col The column where we want to get our own guess.
*** @return The value of the table with my guesses at row and column. If row/col
*** is outside the field OutOfRange is returned.
*/
CellContent get_my_guess(int row, int col)
{
  if(!is_outofrange(row, col))
  {
    return arrGuess[row][col];
  }

  return OutOfRange;
}
