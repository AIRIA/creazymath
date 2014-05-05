//
//  AppConfig.h
//  creazymath
//
//  Created by AIRIA on 14-5-5.
//
//

#ifndef __creazymath__AppConfig__
#define __creazymath__AppConfig__

#include "CommonHeaders.h"

class AppConfig
{
public:
    static void init();
    static bool getSoundEnabled();
    static void setSoundEnabled(bool val);
    static int getTopScore();
    static void setTopScore(int score);
};

#endif /* defined(__creazymath__AppConfig__) */
