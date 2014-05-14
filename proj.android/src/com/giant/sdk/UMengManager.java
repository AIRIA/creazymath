package com.giant.sdk;

import android.app.Activity;
import android.content.Context;
import android.graphics.BitmapFactory;
import android.util.Log;

import com.umeng.socialize.bean.SHARE_MEDIA;
import com.umeng.socialize.controller.RequestType;
import com.umeng.socialize.controller.UMServiceFactory;
import com.umeng.socialize.controller.UMSocialService;
import com.umeng.socialize.media.UMImage;
import com.umeng.socialize.sso.QZoneSsoHandler;
import com.umeng.socialize.sso.TencentWBSsoHandler;
import com.umeng.socialize.sso.UMWXHandler;

public class UMengManager {

	final UMSocialService mController = UMServiceFactory.getUMSocialService("com.umeng.share", RequestType.SOCIAL);
	private static Context context;
	private static UMengManager _instance;

	public static UMengManager instance() {
		if (_instance == null) {
			_instance = new UMengManager();
		}
		return _instance;
	}

	public UMSocialService getController() {
		return mController;
	}

	public static void init(Context ctx) {
		context = ctx;
	}

	public void openShare(String path) {
		String title = "快来玩疯狂数学吧^-^";
		String content = "你是不是还在认为自己的智商很高,反应速度很快?其实你是自我感觉太良好了,不信就来试试,挑战一下~http://m.app.xiaomi.com/#page=detail&id=61484";
		
		Log.v("umeng", "OPEN INVOKE");
		mController.setShareContent(content);
		mController.setShareImage(new UMImage(context, BitmapFactory.decodeFile(path)));
		mController.getConfig().setPlatforms(SHARE_MEDIA.WEIXIN, SHARE_MEDIA.WEIXIN_CIRCLE, SHARE_MEDIA.QZONE, SHARE_MEDIA.SINA);
		String appID = "wx4c9f0be04d647903";
		// 微信图文分享必须设置一个url
		String contentUrl = "http://m.app.xiaomi.com/#page=detail&id=61484";
		// 添加微信平台，参数1为当前Activity, 参数2为用户申请的AppID, 参数3为点击分享内容跳转到的目标url
		UMWXHandler wxHandler = mController.getConfig().supportWXPlatform(context, appID, contentUrl);
		wxHandler.setWXTitle(title);
		// 支持微信朋友圈
		UMWXHandler circleHandler = mController.getConfig().supportWXCirclePlatform(context, appID, contentUrl);
		circleHandler.setCircleTitle(title);
		mController.getConfig().setSsoHandler(new QZoneSsoHandler((Activity) context, appID));
		mController.getConfig().setSsoHandler(new TencentWBSsoHandler());
		mController.openShare((Activity) context, false);
	}
}
