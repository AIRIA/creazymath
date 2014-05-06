//
//  GameScene.h
//  creazymath
//
//  Created by AIRIA on 14-5-5.
//
//

#ifndef __creazymath__GameScene__
#define __creazymath__GameScene__

#include "BaseLayer.h"

class GameScene:public BaseLayer
{
private:
    int score;
    int best;
    CCLabelTTF *question;
    CCLabelTTF *answer;
    CCLabelTTF *scoreLabel;
    CCProgressTimer *progressBar;
    CCLayerColor *background;
    bool isOver;
    bool result;
    
    void __answerHandler(CCObject *pSender);
    void __runProgressBar();
    void __makeQuestion();
    void __showResult();
    void __soundHandler(CCObject *pSender);
    void __createRandomColor();
    void __menuHandler(CCObject *pSender);
    void __restartHandler(CCObject *pSender);
    void __restartGame();
    
    std::vector<ccColor3B> colors;
    
public:
    GameScene():score(0),best(0),question(NULL),answer(NULL),progressBar(NULL),isOver(true){
    };
    virtual bool init();
    CREATE_FUNC(GameScene);
    SCENE_FUNC(GameScene);
};

#endif /* defined(__creazymath__GameScene__) */
