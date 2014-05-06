//
//  PluginUtil.cpp
//  creazymath
//
//  Created by AIRIA on 14-5-6.
//
//

#include "PluginUtil.h"

void PluginUtil::init() {
	bool isHave = JniHelper::getStaticMethodInfo(minfo, "", "",
			"()Ljava/lang/Object;");
	if (isHave) {
		obj = minfo.env->CallStaticObjectMethod(minfo.classID,minfo.methodID);
	}else{
		obj = NULL;
	}
}

void PluginUtil::invoke(MethodType key, std::string param) {
	std::string methodName = NULL;
	switch (key) {
	case kPPdoSdkShowAds:
		methodName = "doSdkShowAds";
		break;
	case kPPdoSdkHideAds:
		methodName = "doSdkHideAds";
		break;
	case kPPdoSdkShowScoreWall:
		methodName = "doSdkShowScoreWall";
		break;
	default:
		break;
	}

}
