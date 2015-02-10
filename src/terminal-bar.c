#include "myheader.h"

int term_width(void);
void program_loop(void);
void update_current_post(void);

char SIDE_CHAR = '|';
char BG_CHAR = '-';
char FG_CHAR = '#';
int NUM_OF_FG_CHARS = 20;


int TERM_WIDTH;
int CURRENT_POS;
bool MOVING_RIGHT;

int main()
{    
    TERM_WIDTH = term_width();
    CURRENT_POS = 4;

    putchar('\n');
    program_loop();
    putchar('\n');

    return EXIT_SUCCESS;
}

int term_width(void)
{
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return w.ws_col;
}

void program_loop(void)
{
    int i;

    for (;;)
    {
        //move up one line
        printf("\033[%dA", 1);
 
        putchar(SIDE_CHAR);
        for (i = 2; i <= CURRENT_POS; i++)
        {
            putchar(BG_CHAR);
        }
        for (i = 0; i <= NUM_OF_FG_CHARS; i++)
        {
            putchar(FG_CHAR);
        }
        for (i = CURRENT_POS; i <= TERM_WIDTH - (3 + NUM_OF_FG_CHARS); i++)
        {
            putchar(BG_CHAR);
        }
        putchar(SIDE_CHAR);

        putchar('\n');
        usleep(30*1000);
        update_current_post();
    }
}

void update_current_post(void)
{
    if (MOVING_RIGHT == true)
        CURRENT_POS++;
    else
      CURRENT_POS--;


    if (CURRENT_POS < 2)
        MOVING_RIGHT = true;

    if (CURRENT_POS >= TERM_WIDTH - (2 + NUM_OF_FG_CHARS))
        MOVING_RIGHT = false;
}
