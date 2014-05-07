package com.giant.sdk;

import android.util.Log;

public class SdkManager implements ISdkManager{

	private final static String TAG = "cocos2d-x";
	private static SdkManager _instance;
	
	public static Object instance(){
		if(_instance==null){
			_instance = new SdkManager();
			Log.v(TAG,"instance init success");
		}
		return _instance;
	}

	@Override
	public void doSdkShowAds(String params) {
		// TODO Auto-generated method stub
		Log.v(TAG, "invoke show ads method");
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
	}
}
