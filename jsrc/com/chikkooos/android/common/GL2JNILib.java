
package com.chikkooos.android.common;

import android.content.res.AssetManager;


public class GL2JNILib {

     public static native void main();
     
     public static native void init(int width, int height);
     
     public static native void step();
     
     public static native void setAssetManager(AssetManager manager);
          
     public static native void swipeLeftToRight();
     public static native void swipeRightToLeft();
     public static native void swipeTopToBottom();
     public static native void swipeBottomToTop();
     
     public static native void singleTap(int x, int y);
     public static native void doubleTap(int x, int y);

     public static native void touchDown(int x, int y);
     public static native void touchUp(int x, int y);
     
     public static native void touchScroll(int x, int y);
     
     public static native void keyEvent(int key, int x, int y);

     public static native void pause();
     public static native void resume();
}

