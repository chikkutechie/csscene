
package com.chikkooos.android.common;

import android.app.Activity;
import android.content.res.Configuration;
import android.os.Bundle;
import android.util.Log;
import android.view.KeyEvent;

public class GL2JNIActivity extends Activity {

    protected GL2JNIView mView;
    protected int mClientVersion = 2;
    
    @Override protected void onCreate(Bundle icicle) {
        super.onCreate(icicle);
        GL2JNILib.setAssetManager(getAssets());
    }

    @Override protected void onPause() {
        super.onPause();
        mView.onPause();
    }

    @Override protected void onResume() {
        super.onResume();
        mView.onResume();
    }
    
    protected void startRendering() {
    	mView.setClientVersion(clientVersion());
    	mView.startRendering();
    }
    
    @Override
    public void onConfigurationChanged(Configuration newConfig) {
    	super.onConfigurationChanged(newConfig);
    }

    public void setClientVersion(int cv) {
    	mClientVersion = cv;
    }
    
    public int clientVersion() {
    	return mClientVersion;
    }
    
    
    @Override
    public boolean onKeyDown(int keyCode, KeyEvent event) {
    	if (keyCode == KeyEvent.KEYCODE_BACK && event.getRepeatCount() == 0) {
    		return true;
    	}
    	
    	return super.onKeyUp(keyCode, event);
    }
    
    @Override
    public boolean onKeyUp(int keyCode, KeyEvent event) {
    	if (keyCode == KeyEvent.KEYCODE_BACK && event.getRepeatCount() == 0) {
    		mView.onKeyEvent(keyCode);
    		return true;
    	}
    	
    	return super.onKeyUp(keyCode, event);
    }

    @Override
    public void onBackPressed() {
    }
}
