//
//  AudioUtil.cpp
//  creazymath
//
//  Created by AIRIA on 14-5-5.
//
//

#include "AudioUtil.h"
#include "AppConfig.h"

void AudioUtil::playEffect(const char *path)
{
    if(AppConfig::getSoundEnabled()){
        SimpleAudioEngine::sharedEngine()->playEffect(path);
    }
}