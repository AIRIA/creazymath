//
//  BaseLayer.cpp
//  creazymath
//
//  Created by AIRIA on 14-5-5.
//
//

#include "BaseLayer.h"

bool BaseLayer::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    m_winSize = CCDirector::sharedDirector()->getWinSize();
    m_fScaleFactor = m_winSize.width/PP_DESIGN_WIDTH;
    
    m_pHeader = __getScaleLayer();
    m_pHeader->setAnchorPoint(ccp(0, 1));
    m_pHeader->setPosition(VisibleRect::leftTop());
    
    m_pBody = __getScaleLayer();
    m_pBody->setAnchorPoint(ccp(0.5f, 0.5f));
    m_pBody->setPosition(VisibleRect::center());
    
    m_pFooter = __getScaleLayer();
    m_pFooter->setAnchorPoint(CCPointZero);
    m_pFooter->setPosition(CCPointZero);
    
    addChild(m_pBody);
    addChild(m_pHeader);
    addChild(m_pFooter);
    
    return true;
}

CCLayer *BaseLayer::__getScaleLayer()
{
    CCLayer *pLayer = CCLayer::create();
    pLayer->ignoreAnchorPointForPosition(false);
    pLayer->setContentSize(CCSizeMake(PP_DESIGN_WIDTH, PP_DESIGN_HEIGHT));
    pLayer->setScale(m_fScaleFactor);
    return pLayer;
}