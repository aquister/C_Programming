/*
 * Compile and run:
 * gcc -o x11tst x11tst.c `pkg-config --libs --cflags x11` -std=c99 && ./x11tst
 */

#include "myheader.h"
#include <X11/Xlib.h>
#include <X11/Xutil.h>

#define WIN_WIDTH 600
#define WIN_HEIGHT 600

#define SCANFPATTERN "%4s %lf %lf %lf %lf %lf %lf %lf"

typedef double ticktype;
ticktype oldTicks[7];


unsigned long GetColor(Display* dis, char* color_name) {
    Colormap cmap;
    XColor near_color, true_color;
    cmap = DefaultColormap(dis, 0);
    XAllocNamedColor(dis, cmap, color_name, &near_color, &true_color);
    return(near_color.pixel);
}

//Draw filled rectangle with x1 and y1 as bottom left coordinate
void DrawFilledRectangle(Display* dis, Window win, GC gc, int x1, int y1,
        int width, int height) {
     
    for (unsigned int deltaY = y1-height; deltaY < y1; deltaY++) {
        XDrawLine(dis, win, gc, x1, deltaY, (x1+width), deltaY);
    }
}

double GetCpuUtil() {

    FILE *f = fopen("/proc/stat","r");
    if (!f) {
        fprintf(stderr, "Could not open /proc/stat.\n");
        exit(EXIT_FAILURE);
    }
    
    ticktype newTicks[7];
    char label[5];
    
    fscanf(f, SCANFPATTERN, label, &newTicks[0], &newTicks[1], &newTicks[2],
            &newTicks[3], &newTicks[4], &newTicks[5], &newTicks[6]);
    
    fclose(f);
    
    ticktype tickd[7];
    ticktype total = 0;
    
    for (size_t i = 0; i < 7; i++) {
        tickd[i] = newTicks[i] - oldTicks[i];
        total += tickd[i];
    }
    for (size_t i = 0; i < 7; i++) {
        tickd[i] = (tickd[i] * 100.0) / total;
    }

    // set old ticks to new ticks. need fix
    for (size_t i = 0; i < 7; i++) {
         oldTicks[i] = newTicks[i];
    }

    return tickd[0];
}
int main() {
    Display *dis;
    Window win;
    XSetWindowAttributes att;
    GC gc; 
    XEvent ev;
    
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

    // ----------
    
    double cpuUtil = GetCpuUtil();
    sleep(1);
    double newCpuUtil = GetCpuUtil();

    unsigned long long count = 0;

    for (;;) {   
        printf("   cpuUtil: %f\n", cpuUtil);
        printf("newCpuUtil: %f\n", newCpuUtil);
        
        if (++count > 300) {
            count = 0;
            newCpuUtil = GetCpuUtil() * 10;
        }

        if (newCpuUtil > cpuUtil)
            cpuUtil++;

        if (newCpuUtil < cpuUtil)
            cpuUtil--;

        if (cpuUtil < 0)
            cpuUtil = 0;
        
        if (cpuUtil > WIN_HEIGHT)
            cpuUtil = WIN_HEIGHT;
        
    XSetForeground(dis, gc, BlackPixel(dis, 0)^GetColor(dis, "red"));
        DrawFilledRectangle(dis, win, gc, 150, WIN_HEIGHT, 50, cpuUtil);
    XSetForeground(dis, gc, BlackPixel(dis, 0)^GetColor(dis, "red"));
        usleep(10000);
        DrawFilledRectangle(dis, win, gc, 150, WIN_HEIGHT, 50, cpuUtil);
    }

    XDestroyWindow(dis, win);
    XCloseDisplay(dis);
    return EXIT_SUCCESS;
}
