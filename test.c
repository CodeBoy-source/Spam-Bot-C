#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <X11/Xlib-xcb.h>
#include <xcb/xcb.h>
#include <xcb/xcb_event.h>
#include <xcb/xtest.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <X11/extensions/XTest.h>

void Type(const char * pc, KeyCode code_a, Display *dpy, xcb_connection_t * xconn){
    if(NULL == pc){
        fprintf(stderr, "Value is null");
        return;
    }
    KeySym sym_a;
    for (; *pc != '\0'; pc++) {
        if (*pc >= (char)0x20) {
            code_a = XKeysymToKeycode(dpy, (KeySym)*pc);
            //xcb_test_fake_input(xconn, XCB_KEY_PRESS, code_a, XCB_CURRENT_TIME, XCB_NONE, 0, 0, 0);
            //xcb_test_fake_input(xconn, XCB_KEY_RELEASE, code_a, XCB_CURRENT_TIME, XCB_NONE, 0, 0, 0);
            //xcb_flush(xconn);
            XTestFakeKeyEvent(dpy, code_a, True, 0);
            XTestFakeKeyEvent(dpy, code_a, False, 0);
            XFlush(dpy);
        } else {
            fprintf(stderr, "Eeek - out-of-range character 0x%x\n", (unsigned int)*pc);
        }
    }

    XTestFakeKeyEvent(dpy, 36, True, 0);
    XTestFakeKeyEvent(dpy, 36, False, 0);
    XFlush(dpy);
}


int main (int argc, const char* argv[])
{
    xcb_connection_t *xconn;
    KeyCode code_a;
    Display *dpy = XOpenDisplay(NULL);
    xconn = XGetXCBConnection(dpy);

    if(argc <= 1){
        printf("[ERROR]: Must execute with {size} [strings...]\n");
        exit(-1);
    }

    int bydefault = -1;
    if(argc <= 2){
        bydefault = 1;
        printf("[WARNING]: Default string stablished\n");
    }

    int cont = 0,segs = 7;
    printf("[NOTE]: You have %d seconds to focus on the text app\n", segs);
    sleep(segs);

    if(bydefault==-1){
        for(unsigned int i=0; i<atoi(argv[1]); i++){
            Type(argv[2+cont++],code_a,dpy,xconn);
            if(2+cont>=argc)
                cont = 0;
        }
    }

    if(bydefault==1){
        char temp[80];
        sprintf(temp, "I want my reward");
        for(unsigned int i=0; i<atoi(argv[1]); i++){
            Type(temp,code_a,dpy,xconn);
        }
    }
    XCloseDisplay(dpy);
}

