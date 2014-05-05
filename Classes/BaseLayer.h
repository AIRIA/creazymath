//
//  BaseLayer.h
//  creazymath
//
//  Created by AIRIA on 14-5-5.
//
//

#ifndef __creazymath__BaseLayer__
#define __creazymath__BaseLayer__

#include <iostream>
#include "CommonHeaders.h"

class BaseLayer:public CCLayer
{
private:
    CCLayer *__getScaleLayer();
protected:
    /* 缩放因子 以宽度为准 */
    float m_fScaleFactor;
    /* 设备实际的分辨率 */
    CCSize m_winSize;
    /* 设备分辨率按照三部分进行适配 */
    CCLayer *m_pHeader;
    CCLayer *m_pBody;
    CCLayer *m_pFooter;
public:
    virtual bool init();
};

#endif /* defined(__creazymath__BaseLayer__) */
