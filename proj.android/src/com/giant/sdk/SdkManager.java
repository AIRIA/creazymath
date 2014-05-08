package com.giant.sdk;

import com.giant.admob.AdsAdmob;
import com.giant.admob.AdsWrapper;

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
		}
		return _instance;
	}

	@Override
	public void doSdkShowAds(String params) {
		Log.v(TAG, "invoke show ads method");
		AdsAdmob.getInstance(mContext).showAds(AdsWrapper.ADS_TYPE_BANNER, AdsAdmob.ADMOB_SIZE_BANNER, AdsWrapper.POS_TOP);
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
			}
		});
	}

	@Override
	public void doSdkShowSpotAds(String params) {
		PluginWrapper.runOnMainThread(new Runnable() {
			@Override
			public void run() {
			}
		});
	}
}
