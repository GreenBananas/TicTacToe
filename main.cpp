#include "Classes/AppDelegate.h"
#include "cocos2d.h"

#include <cstddef>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string>


USING_NS_CC;

int main(int argc, char **argv)
{
    // create the application instance
    AppDelegate app;

    CCEGLView* eglView = CCEGLView::sharedOpenGLView();
    eglView->setFrameSize(600, 800);

    return CCApplication::sharedApplication()->run();
}
