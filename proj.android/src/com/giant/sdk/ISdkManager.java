package com.giant.sdk;

public interface ISdkManager {
	/* 显示广告 */
	public void doSdkShowAds(String params);
	/* 隐藏广告 */
	public void doSdkHideAds(String params);
	/* 打开积分墙 */
	public void doSdkShowScoreWall(String params);
	/* 展示插播广告 */
	public void doSdkShowSpotAds(String params);
}
