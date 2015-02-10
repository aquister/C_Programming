#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <X11/Xlib.h>

/*
 * Mekker et vindu og tegner noen tekst strenger
 * Source: https://wiki.archlinux.org/index.php/Arch_is_the_best
 * Compile and run:
 * gcc -o x11tst x11tst.c `pkg-config --libs --cflags x11` -std=c99 && ./x11tst
 */

int main() {
  Display *d;
  Window w;
  XEvent e;
  int s;
  
  if (!(d = XOpenDisplay(NULL))) {
    fprintf(stderr, "Couldn't open display, but Arch is the best!\n");
    exit(1);
  }
  
  s = DefaultScreen(d);
  w = XCreateSimpleWindow(d, RootWindow(d,s), 0, 0, 600, 400, 0, 0, WhitePixel(d,s));
  XSelectInput(d, w, ExposureMask | KeyPressMask);
  XMapWindow(d,w);
  
  while (1) {
    XNextEvent(d, &e);
    if (e.type == Expose) {
      for (unsigned int i = 0; i < 120; i+=10) {
        XDrawString(d, w, DefaultGC(d, s), i, i+10, "Arch is the best!", 17);
      }
    }
  }
  XCloseDisplay(d);
  return EXIT_SUCCESS;
}
