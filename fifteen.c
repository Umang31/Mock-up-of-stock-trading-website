/**
 * fifteen.c
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int d;

int row, column, blank_row, blank_column;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);

void search(int tile);
bool legal_move(void);
void swap_tile(int tile);

int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log
    FILE *file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = get_int();
        
        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep thread for animation's sake
        usleep(500000);
    }
    
    // close log
    fclose(file);

    // success
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).  
 */
void init(void)
{
    // Highest number
    int n = (d * d) - 1;
    
    // Fill the 2D array with values; i for row and j for column
    for(int i = 0; i < d; i++)
    {
        for(int j = 0; j < d; j++)
        {
            // Set the value of n
            board[i][j] = n;
            
            // Decrease value of n by 1 every time loop iterates
            n--;
        }
    }
    
    // If d is even, swap numbers by 1 and 2 so that game can be won
    if((d % 2) == 0)
    {
        int temp = board[d - 1][d - 2];
        board[d - 1][d - 2] = board[d - 1][d - 3];
        board[d - 1][d - 3] = temp;
    }
    
    // Position of blank tile
    blank_row = d - 1;
    blank_column = d - 1;
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    // Iterate through row
    for(int i = 0; i < d; i++)
    {
        // Iterate through column
        for(int j = 0; j < d; j++)
        {
            // If number is greater than 0, print it on the board
            if(board[i][j] > 0)
            {
                printf("%2i ", board[i][j]);
            }
            
            // If number is equal to 0, print an underscore
            if(board[i][j] == 0)
            {
                printf(" _");
            }
        }
        
        // Each row starts with a new line
        printf("\n");
    }
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile)
{
    // Check if tile actually exists
    if(tile > (d * d) - 1 || tile < 1)
    {
        return false;
    }
    
    // Search for a tile given by user
    search(tile);
    
    // Check if the move is legal
    if(legal_move())
    {
        // Swap blank tile with tile
        swap_tile(tile);
        return true;
    }
    else
    {
        return false;
    }
    
    return false;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{
    // Initialize n to 1
    int n = 1;
    
    // Iterate through row
    for(int i = 0; i < d; i++)
    {
        // Iterate through column
        for(int j = 0; j < d; j++)
        {
            // Check if value of board equals to n
            if(board[i][j] == n)
            {
                // Increment n
                n++;
            }
        }
    }
    
    // Check if game is won
    if(n == d*d && board[d - 1][d - 1] == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Linear search for selected tile's location
void search(int tile)
{
    // Iterate through row
    for(int i = 0; i < d; i++)
    {
        // Iterate through column
        for(int j = 0; j < d; j++)
        {
            // If tile exists in the board, get the location of the tile
            if(tile == board[i][j])
            {
                row = i;
                column = j;
            }
        }
    }
}

// Check if blank tile is next to tile
bool legal_move(void)
{
    // Check if on top row, if so check up for 0
    if(row > 0 && board[row - 1][column] == 0)
    {
        return true;
    }
    
    // Bottom
    if(row < d - 1 && board[row + 1][column] == 0)
    {
        return true;
    }
    
    // Left
    if(column > 0 && board[row][column - 1] == 0)
    {
        return true;
    }
    
    // Right
    if(column < d - 1 && board[row][column + 1] == 0)
    {
        return true;
    }
    
    else
    {
        return false;
    }
}

// Swap tile with blank tile
void swap_tile(int tile)
{
    int temp = board[row][column];
    board[row][column] = board[blank_row][blank_column];
    board[blank_row][blank_column] = temp;
    
    // Chankg location of blank tile
    blank_row = row;
    blank_column = column;
}