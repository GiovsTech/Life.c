#include <stdio.h>
#include <unistd.h>
#define ROWS 25
#define COLS 25
#define ALIVE '*'
#define DEAD '.'
#define GRID_CELLS (ROWS*COLS)





// UTIL FUNCTION TO TURN X,Y CARTESIAN COORDINATES INTO INDEX FOR ARRAYS
int cartesian_to_index(int x, int y)
{
    x %= COLS;
    y %= ROWS;
    return y * COLS + x;


}


// This function sets a specific grid point to two possible states: ALIVE OR DEAD
void setcell(char * grid, int x, int y, char s)
{
        grid[cartesian_to_index(x,y)] = s;
}


char cellstate(char *grid, int x, int y)
{
    return grid[cartesian_to_index(x,y)];

}



void printgrid(char *grid)
{
    int x,y;
    printf("\033[0;0H\033[0;0f");
    for(y = 0; y < ROWS; y++){
        for(x = 0; x < COLS; x++)
        {
            printf(" %c", cellstate(grid, x, y));
        }
        printf("\n");
    }
}



void set_grid( char * grid, char state)
{

    int x,y;
    for(y = 0; y < ROWS; y++){
        for(x = 0; x < COLS; x++)
        {
            setcell(grid, x, y, state);
        }
    }


}

// count the number of living cells in the neighboorhood of a given cell
int count_nc(char *grid, int x , int y)
{
    return
        (cellstate(grid, x - 1 , y) == ALIVE) /* LEFT SAME Y*/ +
        (cellstate(grid, x + 1 , y) == ALIVE) /* RIGHT SAME Y */ +
        (cellstate(grid, x - 1 , y - 1) == ALIVE) /* LEFT ON THE TOP */ +
        (cellstate(grid, x + 1 , y - 1 ) == ALIVE) /*  RIGHT ON THE TOP */ +
        (cellstate(grid, x - 1 , y + 1) == ALIVE) /* LEFT ON THE BOTTOM */ +
        (cellstate(grid, x + 1 , y + 1 ) == ALIVE) /*  RIGHT ON THE BOTTOM */ +
        (cellstate(grid, x , y - 1 ) == ALIVE) /*  SAME X ON THE TOP */ +
        (cellstate(grid, x , y + 1 ) == ALIVE); /* SAME X ON THE BOTTOM */

}




void new_generation(char * old, char * new)
{
    int x,y;
    for(y = 0; y < ROWS; y++){
        for(x = 0; x < COLS; x++)
        {
            char new_state = DEAD;
            int n_alive = count_nc(old,x ,y);

            if (cellstate(old, x , y ) == ALIVE)
            {
                if (n_alive == 2 || n_alive == 3)
                    new_state = ALIVE;

             }
            else {
                if (n_alive == 3) new_state = ALIVE; // REPRODUCTION
            }

            setcell(new, x, y , new_state);


        }
    }
}






int main()
{

    char old_grid[GRID_CELLS];
    char new_grid[GRID_CELLS];

    // FIRST DEBUG
    // set_grid(grid, DEAD);
    //
    // setcell(grid, -1, 1, ALIVE);
    //
    // printgrid(grid);

// TODO: IMPLEMENT A PATTERN BY INPUT FILE

    set_grid(old_grid, DEAD);
    setcell(old_grid, 12, 12, ALIVE);
    setcell(old_grid, 13, 13, ALIVE);
    setcell(old_grid, 14, 11, ALIVE);
    setcell(old_grid, 14, 12, ALIVE);
    setcell(old_grid, 14, 13, ALIVE);

    while (1)
    {
        new_generation(old_grid,new_grid);
        printgrid(new_grid);
        usleep(1000000);
        new_generation(new_grid, old_grid );
        printgrid(old_grid);
        usleep(1000000);
    }





    return 0;



}

