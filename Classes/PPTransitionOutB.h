//
//  PPTransitionOutB.h
//  creazymath
//
//  Created by AIRIA on 14-5-6.
//
//

#ifndef __creazymath__PPTransitionOutB__
#define __creazymath__PPTransitionOutB__


#include "CommonHeaders.h"

class PPTransitionOutB:public CCTransitionScene,public CCTransitionEaseScene
{
public:
    virtual void onEnter();
    /** returns the action that will be performed */
    virtual CCActionInterval* action(void);
    
    virtual CCActionInterval* easeActionWithAction(CCActionInterval * action);
    virtual void initScenes(void);
    static PPTransitionOutB *create(float duration,CCScene *scene);
protected:
    virtual void sceneOrder();
};

#endif /* defined(__creazymath__PPTransitionOutB__) */
