//
//  HomeScene.cpp
//  creazymath
//
//  Created by AIRIA on 14-5-5.
//
//

#include "HomeScene.h"
#include "GameScene.h"
#include "AudioUtil.h"
#include "PPTransitionOutB.h"



bool HomeScene::init()
{
    if (!BaseLayer::init()) {
        return false;
    }
    
    CCLayerColor *pBackground = CCLayerColor::create(ccc4(49,65,80, 255),m_winSize.width,m_winSize.height);
    addChild(pBackground,-1);
    
    CCSprite *pLogo = CCSprite::create("images/logo_home.png");
    pLogo->setPosition(ccp(PP_DESIGN_WIDTH/2,PP_DESIGN_HEIGHT/2+50));
    m_pBody->addChild(pLogo);
    
    CCSprite *perfectLogo = CCSprite::create("perfect.png");
    perfectLogo->setAnchorPoint(ccp(0.5f, 1.0f));
    perfectLogo->setPosition(ccp(PP_DESIGN_WIDTH/2, PP_DESIGN_HEIGHT-30));
    m_pHeader->addChild(perfectLogo);
    
    CCMenuItemSprite *pPlayItem = CCMenuItemSprite::create(SPRITE("images/play.png"), SPRITE("images/play_select.png"),this,menu_selector(HomeScene::__startHandler));
    CCMenu *playMenu = CCMenu::create(pPlayItem,NULL);
    playMenu->setPosition(pLogo->getPosition()-ccp(0,100));
    m_pBody->addChild(playMenu);
    
    CCLabelTTF *gameRule = CCLabelTTF::create("游戏规则:\n你只有一秒钟的时间选择对与错,看看你的大脑反应究竟有多快,跟你的小伙伴们一起比试比试吧,看看谁的大脑反应更快,Come on ~", "Arial", 20,CCSizeMake(PP_DESIGN_WIDTH-40,300),kCCTextAlignmentLeft);
    gameRule->setColor(ccc3(236,240,241));
    gameRule->setPosition(playMenu->getPosition()-ccp(0, 200));
    m_pBody->addChild(gameRule);
    
    CCLabelTTF *copyRight = CCLabelTTF::create("2014-2015 完美计划版权所有", "Arial", 15);
    copyRight->setPosition(ccp(PP_DESIGN_WIDTH/2, 20));
    m_pFooter->addChild(copyRight);
    SimpleAudioEngine::sharedEngine()->preloadEffect("sound/fail.ogg");
    SimpleAudioEngine::sharedEngine()->preloadEffect("sound/restart.ogg");
    SimpleAudioEngine::sharedEngine()->preloadEffect("sound/scored.ogg");
    return true;
}

void HomeScene::__startHandler(cocos2d::CCObject *pSender)
{
    AudioUtil::playEffect("sound/restart.ogg");
    CCDirector::sharedDirector()->replaceScene(PPTransitionOutB::create(0.5f, GameScene::scene()));
}