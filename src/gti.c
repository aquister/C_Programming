#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <string.h>

int  term_width(void);
void init_space(void);
void move_to_top(void);
void line_at(int start_x, const char *s);
void draw_car(int x);
void clear_car(int x);

int TERM_WIDTH;

int main(int argc, char **argv)
{
    int i;
    TERM_WIDTH = term_width();
    init_space();
    for (i = -20; i < TERM_WIDTH; i++) {
        draw_car(i);
        usleep(20*1000);
        clear_car(i);
    }
    
    return 1;
}

int term_width(void)
{
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return w.ws_col;
}

void init_space(void)
{
    puts("\n\n\n\n\n\n"); /* 7 lines */
}

void move_to_top(void)
{
    printf("\033[%dA", 7);
}

void line_at(int start_x, const char *s)
{
    int x;
    size_t i;
    if (start_x > 1)
        printf("\033[%dC", start_x);
    for (x = start_x, i = 0; i < strlen(s); x++, i++) {
        if (x > 0 && x < TERM_WIDTH)
            putchar(s[i]);
    }
    putchar('\n');
}

void draw_car(int x)
{
    move_to_top();
    line_at(x, "   ,---------------.");
    line_at(x, "  /  /``````|``````\\\\");
    line_at(x, " /  /_______|_______\\\\________");
    line_at(x, "|]      GTI |'       |        |]");
    if (x % 2) {
    line_at(x, "=  .-:-.    |________|  .-:-.  =");
    line_at(x, " `  -+-  --------------  -+-  '");
    line_at(x, "   '-:-'                '-:-'  ");
    } else {
    line_at(x, "=  .:-:.    |________|  .:-:.  =");
    line_at(x, " `   X   --------------   X   '");
    line_at(x, "   ':-:'                ':-:'  ");
    }
}

void clear_car(int x)
{
    move_to_top();
    line_at(x, "  ");
    line_at(x, "  ");
    line_at(x, "  ");
    line_at(x, "  ");
    line_at(x, "  ");
    line_at(x, "  ");
    line_at(x, "  ");
}

