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

enum{
    kRightMenu,
    kWrongMenu,
    kProgressSeq
};

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
    
    
    background = CCLayerColor::create(ccc4(212,212,212,255),m_winSize.width,m_winSize.height);
    background->setColor(ccc3(255, 0, 0));
    addChild(background,-1);

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
    sound->setPosition(ccp(20,PP_DESIGN_HEIGHT-100));
    
    right->setPosition(ccp(PP_DESIGN_WIDTH/4, 100));
    wrong->setPosition(ccp(PP_DESIGN_WIDTH/4*3, 100));
    m_pFooter->addChild(answerMenu);
    
    CCLabelTTF *title = CCLabelTTF::create("疯狂数学", "Arial", 35);
    title->setColor(ccc3(49,65,80));
    title->setPosition(ccp(PP_DESIGN_WIDTH/2, PP_DESIGN_HEIGHT-38));
    m_pHeader->addChild(title);
    
    question = CCLabelTTF::create("3+2", "fonts/relay-black.ttf", 90);
    question->setPosition(ccp(PP_DESIGN_WIDTH/2, PP_DESIGN_HEIGHT/2+50));
    m_pBody->addChild(question);
    
    answer = CCLabelTTF::create("=5", "fonts/relay-black.ttf", 90);
    answer->setPosition(question->getPosition()-ccp(0, 80));
    m_pBody->addChild(answer);
    
    scoreLabel = CCLabelTTF::create("0", "fonts/relay-black.ttf", 40);
    scoreLabel->setAnchorPoint(ccp(1.0f, 0.5f));
    scoreLabel->setColor(ccORANGE);
    scoreLabel->setPosition(ccp(PP_DESIGN_WIDTH-20,PP_DESIGN_HEIGHT-100));
    m_pFooter->addChild(scoreLabel);
    CCSprite *timeBar = CCSprite::create("images/whiteBlock.png");
    timeBar->setColor(ccc3(126,187,248));
    progressBar = CCProgressTimer::create(timeBar);
    progressBar->setAnchorPoint(ccp(0.0f,1.0f));
    progressBar->setType(kCCProgressTimerTypeBar);
    progressBar->setMidpoint(ccp(0,0));
    progressBar->setBarChangeRate(ccp(1,0));
    progressBar->setScaleX(PP_DESIGN_WIDTH/progressBar->getContentSize().width);
    progressBar->setScaleY(7/progressBar->getContentSize().height);
    progressBar->setPosition(sound->getPosition()-ccp(20, -30));
    m_pFooter->addChild(progressBar);
    /* 生成一个问题 并且计算出结果 */
    __makeQuestion();
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
    progressBar->setPercentage(100);
    CCProgressFromTo *progressAct = CCProgressFromTo::create(1, 100, 0);
    CCCallFunc *progressHandler = CCCallFunc::create(this, callfunc_selector(GameScene::__showResult));
    CCSequence *seq = CCSequence::create(progressAct,progressHandler,NULL);
    seq->setTag(kProgressSeq);
    progressBar->runAction(seq);
}

void GameScene::__answerHandler(cocos2d::CCObject *pSender)
{
    if (isOver) {
        __runProgressBar();
        score = 0;
        scoreLabel->setString("0");
        isOver = false;
    }
    progressBar->stopActionByTag(kProgressSeq);
    CCNode *item = (CCNode*)pSender;
    if( ( result == true && item->getTag() == kRightMenu ) || (result==false&&item->getTag()==kWrongMenu) ){
        __makeQuestion();
        __runProgressBar();
        score += 1;
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
    AudioUtil::playEffect("sound/fail.ogg");
    progressBar->setPercentage(100);
    CCMessageBox("game over", "tip");
    isOver = true;
    __createRandomColor();
}

void GameScene::__makeQuestion()
{
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