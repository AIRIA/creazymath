//
//  GameScene.cpp
//  creazymath
//
//  Created by AIRIA on 14-5-5.
//
//

#include "GameScene.h"
#include "AudioUtil.h"
#include "AppConfig.h"
#include "HomeScene.h"

enum{
    kRightMenu,
    kWrongMenu,
    kProgressSeq,
    kAnswerMenu,
    kOverBackgroundLayer,
    kGameOverPanel
};

#define PP_GAME_OVER_TIME 1.0f
#define PP_LABEL_TIME 0.3f

void GameScene::onEnter()
{
    BaseLayer::onEnter();
    __makeQuestion();
}

bool GameScene::init()
{
    if (!BaseLayer::init()) {
        return false;
    }
    colors.push_back(ccc3(255,174,64));
    colors.push_back(ccc3(50,150,205));
    colors.push_back(ccc3(103,62,128));
    colors.push_back(ccc3(124,103,88));
    colors.push_back(ccc3(207,215,240));
    colors.push_back(ccc3(235,222,158));
    colors.push_back(ccc3(153,152,153));
    colors.push_back(ccc3(48,159,64));
    
    /* 背景颜色层 */
    background = CCLayerColor::create(ccc4(212,212,212,255),m_winSize.width,m_winSize.height);
    background->setColor(ccc3(255, 0, 0));
    addChild(background,-1);
    /* 正确和错误的菜单 以及声音开关 */
    CCMenuItemSprite *right = CCMenuItemSprite::create(SPRITE("images/true.png"), SPRITE("images/true_select.png"),this,menu_selector(GameScene::__answerHandler));
    CCMenuItemSprite *wrong = CCMenuItemSprite::create(SPRITE("images/false.png"), SPRITE("images/false_select.png"),this,menu_selector(GameScene::__answerHandler));
    right->setTag(kRightMenu);
    wrong->setTag(kWrongMenu);
    
    CCMenuItemSprite *soundOn = CCMenuItemSprite::create(SPRITE("images/sound_on.png"), SPRITE("images/sound_on.png"));
    CCMenuItemSprite *soundOff = CCMenuItemSprite::create(SPRITE("images/sound_off.png"), SPRITE("images/sound_off.png"));
    CCMenuItemToggle *sound = CCMenuItemToggle::createWithTarget(this, menu_selector(GameScene::__soundHandler), soundOn,soundOff,NULL);
    
    CCMenu *answerMenu = CCMenu::create(right,wrong,sound,NULL);
    answerMenu->setAnchorPoint(CCPointZero);
    answerMenu->setPosition(CCPointZero);
    answerMenu->setTag(kAnswerMenu);
    sound->setPosition(ccp(20,PP_DESIGN_HEIGHT-100));
    
    right->setPosition(ccp(PP_DESIGN_WIDTH/4, 100));
    wrong->setPosition(ccp(PP_DESIGN_WIDTH/4*3, 100));
    m_pFooter->addChild(answerMenu);
    /* 顶部的title */
    CCLabelTTF *title = CCLabelTTF::create("疯狂数学", "Arial", 35);
    title->setColor(ccc3(49,65,80));
    title->setPosition(ccp(PP_DESIGN_WIDTH/2, PP_DESIGN_HEIGHT-38));
    m_pHeader->addChild(title);
    
    question = CCLabelTTF::create("3+2", "fonts/relay-black.ttf", 90);
    
    m_pBody->addChild(question);
    question->setPosition(ccp(PP_DESIGN_WIDTH/2, PP_DESIGN_HEIGHT/2+50));
    answer = CCLabelTTF::create("=5", "fonts/relay-black.ttf", 90);
    answer->setPosition(question->getPosition()-ccp(0, 80));
    m_pBody->addChild(answer);
    /* 当前的得分 */
    scoreLabel = CCLabelTTF::create("0", "fonts/relay-black.ttf", 40);
    scoreLabel->setAnchorPoint(ccp(1.0f, 0.5f));
    scoreLabel->setColor(ccORANGE);
    scoreLabel->setPosition(ccp(PP_DESIGN_WIDTH-20,PP_DESIGN_HEIGHT-100));
    m_pFooter->addChild(scoreLabel);
    /* 时间进度条 提示倒计时 */
    CCSprite *timeBar = CCSprite::create("images/whiteBlock.png");
    timeBar->setColor(ccc3(126,187,248));
    progressBar = CCProgressTimer::create(timeBar);
    progressBar->setAnchorPoint(ccp(0.0f,1.0f));
    progressBar->setType(kCCProgressTimerTypeBar);
    progressBar->setMidpoint(ccp(0,0));
    progressBar->setBarChangeRate(ccp(1,0));
    progressBar->setPercentage(100);
    progressBar->setScaleX(PP_DESIGN_WIDTH/progressBar->getContentSize().width);
    progressBar->setScaleY(7/progressBar->getContentSize().height);
    progressBar->setPosition(sound->getPosition()-ccp(20, -30));
    m_pFooter->addChild(progressBar);
    /* 生成一个问题 并且计算出结果 */
    __createRandomColor();
    return true;
}

void GameScene::__createRandomColor()
{
    int idx = rand()%colors.size();
    background->setColor(colors[idx]);
}

void GameScene::__runProgressBar()
{
    if (isOver) {
        score = 0;
        scoreLabel->setString("0");
        isOver = false;
        return;
    }
    progressBar->setPercentage(100);
    CCProgressFromTo *progressAct = CCProgressFromTo::create(1, 100, 0);
    CCCallFunc *progressHandler = CCCallFunc::create(this, callfunc_selector(GameScene::__showResult));
    CCSequence *seq = CCSequence::create(progressAct,progressHandler,NULL);
    seq->setTag(kProgressSeq);
    progressBar->runAction(seq);
}

void GameScene::__answerHandler(cocos2d::CCObject *pSender)
{
    
    progressBar->stopActionByTag(kProgressSeq);
    CCNode *item = (CCNode*)pSender;
    if( ( result == true && item->getTag() == kRightMenu ) || (result==false&&item->getTag()==kWrongMenu) ){
        /* 移动问题的位置 */
        CCActionInterval *moveQ = CCMoveTo::create(PP_LABEL_TIME,ccp(-PP_DESIGN_WIDTH/2, PP_DESIGN_HEIGHT/2+50));
        CCActionInterval *moveA = CCMoveTo::create(PP_LABEL_TIME,ccp(-PP_DESIGN_WIDTH/2, PP_DESIGN_HEIGHT/2-30));
        question->runAction(CCEaseBackInOut::create(moveQ));
        answer->runAction(CCSequence::create(
                            CCEaseBackInOut::create(moveA),
                            CCCallFunc::create(this, callfunc_selector(GameScene::__makeQuestion)),
                            NULL
                            ));
        score += 1;
        progressBar->setPercentage(100);
        char scoreStr[10];
        sprintf(scoreStr, "%d",score);
        scoreLabel->setString(scoreStr);
        AudioUtil::playEffect("sound/scored.ogg");
        
    }else{
        __showResult();
    }
}

void GameScene::__showResult()
{
    /* 背景层 */
    CCLayerColor *bg = CCLayerColor::create(ccc4(0, 0, 0, 0));
    bg->setTag(kOverBackgroundLayer);
    addChild(bg);
    bg->runAction(
                  CCFadeTo::create(PP_GAME_OVER_TIME, 128)
    );
    CCMenu *answerMenu = (CCMenu*)m_pFooter->getChildByTag(kAnswerMenu);
    answerMenu->setTouchEnabled(false);
    
    /* 播放音乐重置数据 */
    AudioUtil::playEffect("sound/fail.ogg");
    progressBar->setPercentage(100);
    isOver = true;
    /* 显示结果面板 */
    CCNode *resultNode = CCNode::create();
    resultNode->setScale(m_fScaleFactor);
    CCSprite *resultPanel = CCSprite::create("images/game_over_bg.png");
    resultNode->addChild(resultPanel);
    char topStoreStr[10];
    sprintf(topStoreStr, "%d",AppConfig::getTopScore());
    CCLabelTTF *pScoreLabel = CCLabelTTF::create(scoreLabel->getString(), "fonts/relay-black.ttf", 30);
    CCLabelTTF *topScoreLabel = CCLabelTTF::create(topStoreStr, "fonts/relay-black.ttf", 30);
    pScoreLabel->setPosition(ccp(20, 5));
    topScoreLabel->setPosition(ccp(20, -40));
    resultNode->addChild(pScoreLabel);
    resultNode->addChild(topScoreLabel);
    CCMenuItemSprite *restartItem = CCMenuItemSprite::create(SPRITE("images/play.png"), SPRITE("images/play_select.png"),this,menu_selector(GameScene::__restartHandler));
    CCMenuItemSprite *menuItem = CCMenuItemSprite::create(SPRITE("images/menu.png"), SPRITE("images/menu_select.png"),this,menu_selector(GameScene::__menuHandler));
    CCMenu *menu = CCMenu::create(restartItem,menuItem,NULL);
    menu->ignoreAnchorPointForPosition(false);
    menu->setAnchorPoint(ccp(0.5f,0.5f));
    menu->alignItemsHorizontallyWithPadding(30);
    menu->setPosition(ccp(VisibleRect::center().x, VisibleRect::center().y-90));
    resultNode->addChild(menu);
    addChild(resultNode);
    resultNode->setPosition(VisibleRect::top()+ccp(0, 300));
    /* resultnode action */
    resultNode->runAction(
            CCEaseBackInOut::create(
                CCMoveTo::create(PP_GAME_OVER_TIME, VisibleRect::center())
            )
    );
    resultNode->setTag(kGameOverPanel);
}

void GameScene::__makeQuestion()
{
    
    /* */
    int a,b,right,wrong;
    std::vector<int> answers;
    if(score<10){
        a = rand()%10+1;
        b = rand()%10+1;
    }else{
        a = rand()%score+1;
        b = rand()%score+1;
    }
    right = a + b;
    wrong = right+rand()%4;
    result = right==wrong;
    
    char str[20];
    sprintf(str, "%d+%d",a,b);
    question->setString(str);
    sprintf(str, "=%d",wrong);
    answer->setString(str);
    question->setPosition(ccp(PP_DESIGN_WIDTH+200, PP_DESIGN_HEIGHT/2+50));
    answer->setPosition(question->getPosition()-ccp(0, 80));
    
    CCActionInterval *moveQ = CCMoveTo::create(PP_LABEL_TIME,ccp(PP_DESIGN_WIDTH/2, PP_DESIGN_HEIGHT/2+50));
    CCActionInterval *moveA = CCMoveTo::create(PP_LABEL_TIME,ccp(PP_DESIGN_WIDTH/2, PP_DESIGN_HEIGHT/2-30));
    question->runAction(CCEaseBackInOut::create(moveQ));
    answer->runAction(CCSequence::create(
                CCEaseBackInOut::create(moveA),
                CCCallFunc::create(this, callfunc_selector(GameScene::__runProgressBar)),
                NULL
                ));
}

void GameScene::__soundHandler(cocos2d::CCObject *pSender)
{
    CCMenuItemToggle *soundItem = (CCMenuItemToggle*)pSender;
    int idx = soundItem->getSelectedIndex();
    if(idx==0){
        AppConfig::setSoundEnabled(true);
    }else{
        AppConfig::setSoundEnabled(false);
    }
    
}

void GameScene::__menuHandler(cocos2d::CCObject *pSender)
{
    CCDirector::sharedDirector()->replaceScene(CCTransitionMoveInB::create(0.3f, HomeScene::scene()));
}

void GameScene::__restartHandler(cocos2d::CCObject *pSender)
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    CCLayerColor *pBackground = CCLayerColor::create(ccc4(49,65,80, 255),m_winSize.width,m_winSize.height);
    pBackground->setPosition(ccp(0, -s.height));
    addChild(pBackground);
    
    CCSprite *pLogo = CCSprite::create("images/logo_home.png");
    pLogo->setScale(m_fScaleFactor);
    pBackground->addChild(pLogo);
    pLogo->setPosition(VisibleRect::center()+ccp(0, 100));
    /* background action */
    pBackground->runAction(CCSequence::create(
                              CCMoveTo::create(0.5f, CCPointZero),
                              CCCallFunc::create(this, callfunc_selector(GameScene::__restartGame)),
                              CCDelayTime::create(0.5f),
                              CCMoveTo::create(0.5f, ccp(0,-s.height)),
                              CCCallFunc::create(pBackground, callfunc_selector(CCLayerColor::removeFromParent)),
                              NULL
                              )
                           );
}

void GameScene::__restartGame()
{
    if (score>AppConfig::getTopScore()) {
        AppConfig::setTopScore(score);
    }
    score=0;
    CCMenu *answerMenu = (CCMenu*)m_pFooter->getChildByTag(kAnswerMenu);
    answerMenu->setTouchEnabled(true);
    __makeQuestion();
    __createRandomColor();
    removeChildByTag(kGameOverPanel);
    removeChildByTag(kOverBackgroundLayer);
    AudioUtil::playEffect("sound/restart.ogg");
}