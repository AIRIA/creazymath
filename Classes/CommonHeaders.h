//
//  CommonHeaders.h
//  creazymath
//
//  Created by AIRIA on 14-5-5.
//
//

#ifndef creazymath_CommonHeaders_h
#define creazymath_CommonHeaders_h

#include "cocos2d.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"
#include "VisibleRect.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocos2d;
using namespace CocosDenshion;


#define SCENE_FUNC(__CLASS__) static CCScene *scene(){ \
    CCScene *wrapperScene = CCScene::create(); \
    __CLASS__ *layer = __CLASS__::create(); \
    wrapperScene->addChild(layer); \
    return wrapperScene; \
}

#define PP_DESIGN_WIDTH 480
#define PP_DESIGN_HEIGHT 800

#define PP_CENTER ccp(PP_DESIGN_WIDTH/2,PP_DESIGN_HEIGHT/2);

#define SPRITE(path) CCSprite::create(path)

#endif
