//
//  PluginUtil.cpp
//  creazymath
//
//  Created by AIRIA on 14-5-6.
//
//

#include "PluginUtil.h"
#define PP_SDK_CLASS "com/giant/sdk/SdkManager"
#define PP_SDK_INSTANCE_METHOD "instance"

#if(CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
JniMethodInfo PluginUtil::minfo;
jobject PluginUtil::obj;
#endif

void PluginUtil::init() {
#if(CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
	bool isHave = JniHelper::getStaticMethodInfo(minfo, PP_SDK_CLASS,
	PP_SDK_INSTANCE_METHOD, "()Ljava/lang/Object;");
	if (isHave) {
		obj = minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);
	} else {
		obj = NULL;
	}
#endif
}

void PluginUtil::invoke(MethodType key, std::string param) {
#if(CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
	if (obj == NULL) {
		CCLog("Plugin Object is NULL");
		return;
	}
	std::string methodName;
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
    case kPPdoSdkShowSpotAds:
        methodName = "doSdkShowSpotAds";
        break;
    case kPPdoSdkShare:
    	methodName = "doSdkShare";
	default:
		break;
	}
	bool isExist = JniHelper::getMethodInfo(minfo, PP_SDK_CLASS, methodName.c_str(),
			"(Ljava/lang/String;)V");
	if (isExist == false) {
		CCLog("%s not found", methodName.c_str());
		return;
	}
	jstring paramStr = minfo.env->NewStringUTF(param.c_str());
	minfo.env->CallVoidMethod(obj, minfo.methodID, paramStr);
//	jstring res = (jstring)minfo.env->CallObjectMethod(obj,minfo.methodID);

#endif
}
