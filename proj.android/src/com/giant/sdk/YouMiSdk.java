package com.giant.sdk;

import a.b.c.br.AdSize;
import a.b.c.br.AdView;
import a.b.c.br.AdViewListener;
import a.b.c.diy.DiyManager;
import a.b.c.st.SpotDialogListener;
import a.b.c.st.SpotManager;
import android.app.Activity;
import android.content.Context;
import android.util.Log;
import android.view.Gravity;
import android.widget.FrameLayout;

public class YouMiSdk {
	private final static String TAG = "cocos2d-x";

	public static void showAds(Context ctx) {
		FrameLayout.LayoutParams layoutParams = new FrameLayout.LayoutParams(FrameLayout.LayoutParams.MATCH_PARENT, FrameLayout.LayoutParams.WRAP_CONTENT);
		// 设置广告条的悬浮位置
		layoutParams.gravity = Gravity.TOP | Gravity.RIGHT; // 这里示例为右下角
		// 实例化广告条
		AdView adView = new AdView(ctx, AdSize.FIT_SCREEN);
		// 调用Activity的addContentView函数
		((Activity) ctx).addContentView(adView, layoutParams);
		// 监听广告条接口
		adView.setAdListener(new AdViewListener() {

			@Override
			public void onSwitchedAd(AdView arg0) {
				Log.i(TAG, "广告条切换");
			}

			@Override
			public void onReceivedAd(AdView arg0) {
				Log.i(TAG, "请求广告成功");

			}

			@Override
			public void onFailedToReceivedAd(AdView arg0) {
				Log.i(TAG, "请求广告失败");
			}
		});
	}

	public static void showWall(Context ctx) {
		DiyManager.showRecommendWall(ctx);
	}
	
	public static void showSoptAds(final Context ctx){
		SpotManager.getInstance(ctx).loadSpotAds();
		// 设置展示超时时间，加载超时则不展示广告，默认0，代表不设置超时时间
        SpotManager.getInstance(ctx).setSpotTimeout(5000);//设置5秒
        SpotManager.getInstance(ctx).showSpotAds(ctx, new SpotDialogListener() {
            @Override
            public void onShowSuccess() {
                Log.i(TAG, "展示成功");
            }
            @Override
            public void onShowFailed() {
                Log.i(TAG, "展示失败");
            }
        });
	}
}
