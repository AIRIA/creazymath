//
//  HomeScene.h
//  creazymath
//
//  Created by AIRIA on 14-5-5.
//
//

#ifndef __creazymath__HomeScene__
#define __creazymath__HomeScene__

#include <iostream>
#include "BaseLayer.h"

class HomeScene:public BaseLayer
{
private:
    void __startHandler(CCObject *pSender);
public:
    virtual bool init();
    CREATE_FUNC(HomeScene);
    SCENE_FUNC(HomeScene);
};



#endif /* defined(__creazymath__HomeScene__) */
