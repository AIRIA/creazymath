//
//  AppConfig.cpp
//  creazymath
//
//  Created by AIRIA on 14-5-5.
//
//

#include "AppConfig.h"

void AppConfig::init()
{
    bool isExist = CCUserDefault::sharedUserDefault()->getBoolForKey("isExist", false);
    if(isExist==false)
    {
        CCUserDefault::sharedUserDefault()->setBoolForKey("isExist", true);
        CCUserDefault::sharedUserDefault()->setBoolForKey("soundEnabled", true);
        CCUserDefault::sharedUserDefault()->setIntegerForKey("topScore", 0);
        CCUserDefault::sharedUserDefault()->flush();
    }
}

bool AppConfig::getSoundEnabled()
{
    return CCUserDefault::sharedUserDefault()->getBoolForKey("soundEnabled");
}

void AppConfig::setSoundEnabled(bool val)
{
    CCUserDefault::sharedUserDefault()->setBoolForKey("soundEnabled", val);
    CCUserDefault::sharedUserDefault()->flush();
}

void AppConfig::setTopScore(int score)
{
    CCUserDefault::sharedUserDefault()->setIntegerForKey("topScore", score);
    CCUserDefault::sharedUserDefault()->flush();
}

int AppConfig::getTopScore()
{
    return CCUserDefault::sharedUserDefault()->getIntegerForKey("topScore");
}