package com.giant.sdk;

import net.youmi.android.AdManager;
import android.content.Context;
import android.util.Log;

public class SdkManager implements ISdkManager {

	private final static String TAG = "cocos2d-x";
	private static SdkManager _instance;
	private static Context mContext;

	public static Object instance() {
		if (_instance == null) {
			_instance = new SdkManager();
			Log.v(TAG, "instance init success");
			mContext = PluginWrapper.getContext();
			AdManager.getInstance(mContext).init("66792aaa9d9fa1ed", "c3694ea5cc8085e9", false);
		}
		return _instance;
	}

	@Override
	public void doSdkShowAds(String params) {
		Log.v(TAG, "invoke show ads method");
		PluginWrapper.runOnMainThread(new Runnable() {
			@Override
			public void run() {
				YouMiSdk.showAds(mContext);
			}
		});

	}

	@Override
	public void doSdkHideAds(String params) {
		// TODO Auto-generated method stub
		Log.v(TAG, "invoke hide ads method");
	}

	@Override
	public void doSdkShowScoreWall(String params) {
		// TODO Auto-generated method stub
		Log.v(TAG, "invoke show wall method");
		PluginWrapper.runOnMainThread(new Runnable() {

			@Override
			public void run() {
				YouMiSdk.showWall(mContext);
			}
		});
	}

	@Override
	public void doSdkShowSpotAds(String params) {
		PluginWrapper.runOnMainThread(new Runnable() {
			@Override
			public void run() {
				YouMiSdk.showSoptAds(mContext);
			}
		});
	}
}
