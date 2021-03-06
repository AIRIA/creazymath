//
//  PluginUtil.h
//  creazymath
//
//  Created by AIRIA on 14-5-6.
//
//

#ifndef __creazymath__PluginUtil__
#define __creazymath__PluginUtil__

#include "CommonHeaders.h"

enum MethodType{
    kPPdoSdkShowAds,
    kPPdoSdkHideAds,
    kPPdoSdkShowScoreWall
};

class PluginUtil
{
private:
    static JniMethodInfo minfo;
    static jobject obj;
public:
    static void init();
    static void invoke(MethodType key, std::string param="");
};


#endif /* defined(__creazymath__PluginUtil__) */
