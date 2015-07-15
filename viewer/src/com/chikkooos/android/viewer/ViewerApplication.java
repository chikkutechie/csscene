package com.chikkooos.android.viewer;

import android.app.Application;
import android.content.SharedPreferences;
import android.widget.Toast;

public class ViewerApplication extends Application {
	
	private static final String prefName = "Unnamed";
	private String mGc = "gles2";
	private int mClientVersion = 2;
	
	@Override
	public void onCreate() {
		super.onCreate();
		
		SharedPreferences prefs = getSharedPreferences(prefName, MODE_PRIVATE);
		
		mGc = prefs.getString("gc", "gles2");
		if (mGc.compareTo("gles1") == 0) {
	        System.loadLibrary("viewergles1");
	        mClientVersion = 1;
	        Toast.makeText(getApplicationContext(), "OpenGL/ES 1.x", Toast.LENGTH_LONG).show();
		} else {
	        System.loadLibrary("viewergles2");
	        mClientVersion = 2;
	        Toast.makeText(getApplicationContext(), "OpenGL/ES 2.0", Toast.LENGTH_LONG).show();
		}
	}
	
	public boolean setGc(String v) {
		if (mGc.compareTo(v) != 0) {
			mGc = v;
			
			SharedPreferences prefs = getSharedPreferences(prefName, MODE_PRIVATE);
			SharedPreferences.Editor ed = prefs.edit();
			ed.putString("gc", mGc);
			ed.commit();
			
			if (mGc.compareTo("gles1") == 0) {
		        mClientVersion = 1;
			} else {
		        mClientVersion = 2;
			}
			return true;
		}
		return false;
	}
	
	public String gc() {
		return mGc;
	}

    public void setClientVersion(int cv) {
    	mClientVersion = cv;
    }
    
    public int clientVersion() {
    	return mClientVersion;
    }

}

