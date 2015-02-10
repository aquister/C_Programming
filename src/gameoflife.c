#include "myheader.h"
#include <X11/Xlib.h>
#include <X11/Xutil.h>

#define WIN_WIDTH 640
#define WIN_HEIGHT 640
#define CELLS 64
#define CELL_SIZE WIN_WIDTH / CELLS

Display *dis;
Window win;
XSetWindowAttributes att;
GC gc;
XEvent ev;
bool lifeData[CELLS][CELLS] = {{false}};

size_t validCellAndPopulated(size_t a, size_t b) {
    if (a >= 0 && a < CELLS && b >= 0 && b < CELLS && lifeData[a][b])
        return 1;
    else
        return 0;
}

size_t numberOfNeighbours(size_t a, size_t b) {
    size_t neighbours = 0;

    // check up
    neighbours += validCellAndPopulated(a - 1, b);
    
    // check diag up right
    neighbours += validCellAndPopulated(a - 1, b + 1);

    // check right
    neighbours += validCellAndPopulated(a, b + 1);

    // check diag down right
    neighbours += validCellAndPopulated(a + 1, b + 1);

    // check down
    neighbours += validCellAndPopulated(a + 1, b);

    // check diag down left
    neighbours += validCellAndPopulated(a + 1, b - 1);

    // check left
    neighbours += validCellAndPopulated(a, b - 1);

    // check diag up left
    neighbours += validCellAndPopulated(a - 1, b - 1);

    return neighbours;
}

void updateLifeCells() {
    bool newLifeData[CELLS][CELLS] = {{false}};
    
    for (size_t a = 0; a < CELLS; a++) {
        for (size_t b = 0; b < CELLS; b++) {
            size_t neighbours = numberOfNeighbours(a, b);

            if (neighbours < 2) newLifeData[a][b] = false;
            else if (neighbours > 3) newLifeData[a][b] = false;
            else if (neighbours == 3) newLifeData[a][b] = true;
            else if (neighbours == 2) newLifeData[a][b] = lifeData[a][b];
        }
    }
    
    for (size_t a = 0; a < CELLS; a++)
        for (size_t b = 0; b < CELLS; b++)
            lifeData[a][b] = newLifeData[a][b];
}

unsigned long GetColor(char* color_name) {
    Colormap cmap;
    XColor near_color, true_color;
    cmap = DefaultColormap(dis, 0);
    XAllocNamedColor(dis, cmap, color_name, &near_color, &true_color);
    return(near_color.pixel);
}

void DrawFilledRectangle(size_t x1, size_t y1, size_t width, size_t height) {
    XSetForeground(dis, gc, BlackPixel(dis, 0)^GetColor("red"));
    for (size_t deltaY = y1; deltaY < y1 + height; deltaY++) {
        XDrawLine(dis, win, gc, x1, deltaY, (x1+width-1), deltaY);
    }
}

void drawCells() {
    for (size_t a = 0; a < CELLS; a++)
        for (size_t b = 0; b < CELLS; b++)
            if (lifeData[a][b])
                DrawFilledRectangle(a*CELL_SIZE, b*CELL_SIZE, CELL_SIZE, CELL_SIZE);
}

void runLifeLoop() {
    for(;;) {
        drawCells();
        usleep(200000);
        drawCells();
        updateLifeCells();
    }
}

void setUpWindow() {
    dis = XOpenDisplay(NULL);
    win = XCreateSimpleWindow(dis, RootWindow(dis,0), 100, 100,
            WIN_WIDTH, WIN_HEIGHT, 5, WhitePixel(dis,0), BlackPixel(dis,0));

    att.backing_store = WhenMapped;
    XChangeWindowAttributes(dis, win, CWBackingStore, &att);
    XSelectInput(dis, win, ExposureMask);
    XMapWindow(dis, win);

    do {
        XNextEvent( dis, &ev);
    } while(ev.type != Expose);
    
    gc = XCreateGC(dis, DefaultRootWindow(dis), 0, 0);
    XSetFunction(dis, gc, GXxor);
}

void setSeed(size_t seed[], size_t seedElem) {
    for (size_t i = 0; i < seedElem; i+=2)
        lifeData[seed[i]][seed[i+1]] = true;
}

int main(int argc, char *argv[]) {
    //size_t seed[] = {16,16, 17,17, 18,15, 18,16, 18,17};
    size_t seed[] = {11,15, 12,15, 11,16, 12,16,        
                     21,15, 21,16, 21,17, 22,14, 22,18, 23,13, 23,19, 24,13, 24,19,
                     25,16, 26,14, 26,18, 27,15, 27,16, 27,17, 28,16,
                     31,13, 31,14, 31,15, 32,13, 32,14, 32,15,
                     33,12, 33,16, 35,11, 35,12, 35,16, 35,17,
                     45,13, 46,13, 45,14, 46,14};

    setSeed(seed, sizeof(seed) / sizeof(size_t));

    setUpWindow();
    runLifeLoop();
    return EXIT_SUCCESS;
}
