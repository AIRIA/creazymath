package com.giant.sdk;

import org.json.JSONException;
import org.json.JSONObject;

import a.b.c.AdManager;
import android.content.Context;
import android.util.Log;

public class SdkManager implements ISdkManager {

	private final static String TAG = "cocos2d-x";
	private static SdkManager _instance;
	private static Context mContext;
	private static boolean adsEnabled = false;

	public static Object instance() {
		if (_instance == null) {
			_instance = new SdkManager();
			Log.v(TAG, "instance init success");
			mContext = PluginWrapper.getContext();
			AdManager.getInstance(mContext).init("66792aaa9d9fa1ed", "c3694ea5cc8085e9", false);
			
			PluginWrapper.runOnMainThread(new Runnable() {
				
				@Override
				public void run() {
					String res = NetManager.sendHttpRequest("https://gist.githubusercontent.com/AIRIA/b1dfdd28c31bd4be3389/raw/ads.json");
					if(res!=null){
						try {
							JSONObject json = new JSONObject(res);
							adsEnabled = json.getBoolean("isEnable");
						} catch (JSONException e) {
							e.printStackTrace();
						}
					}
				}
			});
		}
		return _instance;
	}

	@Override
	public void doSdkShowAds(String params) {

		PluginWrapper.runOnMainThread(new Runnable() {
			@Override
			public void run() {
			//	YouMiSdk.showAds(mContext);
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
		PluginWrapper.runOnMainThread(new Runnable() {

			@Override
			public void run() {
				if(adsEnabled){
					YouMiSdk.showSoptAds(mContext);
				}	
			}
		});
	}

	@Override
	public void doSdkShowSpotAds(String params) {
		PluginWrapper.runOnMainThread(new Runnable() {
			@Override
			public void run() {
				if(adsEnabled){
					YouMiSdk.showSoptAds(mContext);
				}
			}
		});
	}

	@Override
	public void doSdkShare(final String params) {
		PluginWrapper.runOnMainThread(new Runnable() {
			
			@Override
			public void run() {
//				UMengManager.instance().openShare(params);
			}
		});
		
	}
}
