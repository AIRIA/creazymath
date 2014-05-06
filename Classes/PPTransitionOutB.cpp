//
//  PPTransitionOutB.cpp
//  creazymath
//
//  Created by AIRIA on 14-5-6.
//
//

#include "PPTransitionOutB.h"

void PPTransitionOutB::initScenes()
{
    m_pInScene->setPosition(ccp(0,0));
}

PPTransitionOutB *PPTransitionOutB::create(float duration, cocos2d::CCScene *scene)
{
    PPTransitionOutB* pScene = new PPTransitionOutB();
    if(pScene && pScene->initWithDuration(duration, scene))
    {
        pScene->autorelease();
        return pScene;
    }
    CC_SAFE_DELETE(pScene);
    return NULL;
}

void PPTransitionOutB::onEnter()
{
    CCTransitionScene::onEnter();
    this->initScenes();
    CCActionInterval *a = this->action();
    
    m_pOutScene->runAction
    (
        CCSequence::create
        (
            this->easeActionWithAction(a),
            CCCallFunc::create(this, callfunc_selector(CCTransitionScene::finish)),
            NULL
        )
    );
}

CCActionInterval *PPTransitionOutB::action()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    return CCMoveTo::create(m_fDuration, ccp(0,-s.height));
}

CCActionInterval *PPTransitionOutB::easeActionWithAction(cocos2d::CCActionInterval *action)
{
    return CCEaseOut::create(action, 2.0f);
}

void PPTransitionOutB::sceneOrder()
{
    m_bIsInSceneOnTop = false;
}