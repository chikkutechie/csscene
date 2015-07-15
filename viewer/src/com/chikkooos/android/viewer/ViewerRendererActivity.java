
package com.chikkooos.android.viewer;

import android.content.res.Configuration;
import android.os.Bundle;

import com.chikkooos.android.common.GL2JNIActivity;
import com.chikkooos.android.common.GL2JNIView;

public class ViewerRendererActivity extends GL2JNIActivity {

    @Override protected void onCreate(Bundle b) {
        super.onCreate(b);
        
        mView = new GL2JNIView(getApplication());
        setContentView(mView);
        
        ViewerJNILib.setSceneFile("data/physics.xml");
        Bundle extras = getIntent().getExtras();
        if (extras != null) {
        	if (extras.containsKey("scene")) {
        		ViewerJNILib.setSceneFile(extras.getString("scene"));
        	}
        }
        
        ViewerApplication app = (ViewerApplication)getApplication();
        setClientVersion(app.clientVersion());
        startRendering();
    }
    
    @Override
    public void onConfigurationChanged(Configuration newConfig) {
    	super.onConfigurationChanged(newConfig);
    }
    
}

