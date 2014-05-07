#include "AppDelegate.h"
#include "HomeScene.h"
#include "AppConfig.h"
#include "PluginUtil.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    srand(time(NULL));
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();
    pDirector->setOpenGLView(pEGLView);
    pDirector->setDisplayStats(false);
    pDirector->setAnimationInterval(1.0 / 60);
    CCScene *pScene = HomeScene::scene();
    pDirector->runWithScene(pScene);
    AppConfig::init();
    PluginUtil::init();
    PluginUtil::invoke(kPPdoSdkShowAds);
    PluginUtil::invoke(kPPdoSdkHideAds);
    PluginUtil::invoke(kPPdoSdkShowScoreWall);
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    CCDirector::sharedDirector()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    CCDirector::sharedDirector()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
