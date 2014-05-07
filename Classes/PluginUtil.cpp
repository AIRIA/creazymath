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

JniMethodInfo PluginUtil::minfo;
jobject PluginUtil::obj;

void PluginUtil::init() {
	bool isHave = JniHelper::getStaticMethodInfo(minfo, PP_SDK_CLASS,
	PP_SDK_INSTANCE_METHOD, "()Ljava/lang/Object;");
	if (isHave) {
		obj = minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);
	} else {
		obj = NULL;
	}
}

void PluginUtil::invoke(MethodType key, std::string param) {
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

}
