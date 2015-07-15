
package com.chikkooos.android.common;

import android.content.Context;
import android.graphics.PixelFormat;
import android.opengl.GLSurfaceView;
import android.util.Log;
import android.view.GestureDetector;
import android.view.KeyEvent;
import android.view.GestureDetector.OnGestureListener;
import android.view.MotionEvent;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class GL2JNIView extends GLSurfaceView implements OnGestureListener, GestureDetector.OnDoubleTapListener, GLSurfaceView.Renderer {
	
	private static class NativeEvent
	{
		static final int Reshape      = 1 << 0;
		static final int TouchUp      = 1 << 1;
		static final int TouchDown    = 1 << 2;
		static final int SwipeLeft    = 1 << 3;
		static final int SwipeRight   = 1 << 4;
		static final int SwipeTop     = 1 << 5;
		static final int SwipeBottom  = 1 << 6;
		static final int Scroll       = 1 << 7;
		static final int LongPress    = 1 << 8;
		static final int SingleTap    = 1 << 9;
		static final int DoubleTap    = 1 << 10;
		static final int KeyPressed   = 1 << 11;

		int mType = 0;
		int mKey;
		int mX;
		int mY;
		
		void fire() {
			if ((mType & Reshape) != 0) {
				// TODO
			}
			
			if ((mType & SwipeRight) != 0) {
				GL2JNILib.swipeLeftToRight();
			}
			
			if ((mType & SwipeLeft) != 0) {
				GL2JNILib.swipeRightToLeft();
			}
			
			if ((mType & SwipeBottom) != 0) {
				GL2JNILib.swipeTopToBottom();
			}
			
			if ((mType & SwipeTop) != 0) {
				GL2JNILib.swipeBottomToTop();
			}
		    
			if ((mType & SingleTap) != 0) {
				GL2JNILib.singleTap(mX, mY);
			}
			
			if ((mType & DoubleTap) != 0) {
				GL2JNILib.doubleTap(mX, mY);
			}

			if ((mType & TouchDown) != 0) {
				GL2JNILib.touchDown(mX, mY);
			}
			
			if ((mType & TouchUp) != 0) {
				GL2JNILib.touchUp(mX, mY);
			}
		     
			if ((mType & NativeEvent.Scroll) != 0) {
				GL2JNILib.touchScroll(mX, mY);
			}
			
			if ((mType & KeyPressed) != 0) {
				GL2JNILib.keyEvent(mKey, 0, 0);
			}
			
			mType = 0;
		}
	}
	
    protected static String TAG = "chikkooos";
    
    protected static final int SWIPE_MIN_DISTANCE = 120;
    protected static final int SWIPE_THRESHOLD_VELOCITY = 200;
    
    protected GestureDetector mDetector;
    
    protected boolean mCalledMain = false;
    protected boolean mCallResume = false;

    protected int mRenderMode = RENDERMODE_CONTINUOUSLY;
    
    protected int mClientVersion = 2;

    protected NativeEvent mEventPasser = new NativeEvent();
    
    public GL2JNIView(Context context) {
        super(context);
        mDetector = new GestureDetector(context, this);
    }

    @Override
	public void onPause() {
        super.onPause();
        GL2JNILib.pause();        
    }

    @Override
	public void onResume() {
        super.onResume();
        mCallResume = true;
    }

    public void setClientVersion(int cv) {
    	mClientVersion = cv;
    }
    
    public int clientVersion() {
    	return mClientVersion;
    }
    
    public void drawScene() {
    	requestRender();
    }
    
    public int sceneRenderMode() {
    	return mRenderMode;
    }
    
    public void setSceneRenderMode(int rm) {
    	mRenderMode = rm;
    }
    
    public void startRendering() {        
        Log.d(TAG, "GLSurfaceView::startRendering");

        setEGLConfigChooser(8, 8, 8, 8, 8, 0);
        setEGLContextClientVersion(mClientVersion);
        
        getHolder().setFormat(PixelFormat.TRANSLUCENT);
        
        setRenderer(this);

        setRenderMode(mRenderMode);

        requestFocus();        
    }

    public void onDrawFrame(GL10 gl) {
    	if (mCalledMain) {
    		if (mCallResume) {
                mCallResume = false;
                GL2JNILib.resume();
        	}

    		synchronized (mEventPasser) {
        		mEventPasser.fire();			
			}
    		
            GL2JNILib.step();
    	}
    }

    public void onSurfaceChanged(GL10 gl, int width, int height) {
    	if (!mCalledMain) {
    		mCalledMain = true;
    		GL2JNILib.main();
    	}
        GL2JNILib.init(width, height);
        if (mCallResume) {
            mCallResume = false;
            GL2JNILib.resume();
    	}        
    }

    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
    }
        
    @Override
    public boolean onTouchEvent(MotionEvent event) {
    	
    	switch (event.getAction()) {
    	case MotionEvent.ACTION_DOWN:
    		synchronized (mEventPasser) {
	    		mEventPasser.mX = (int)event.getX();
	    		mEventPasser.mY = (int)event.getY();
	    		mEventPasser.mType |= NativeEvent.TouchDown;
    		}
    		break;
    	case MotionEvent.ACTION_UP:
    		synchronized (mEventPasser) {
	    		mEventPasser.mX = (int)event.getX();
	    		mEventPasser.mY = (int)event.getY();
	    		mEventPasser.mType |= NativeEvent.TouchUp;
    		}
    		break;
    	}

    	
    	if (mDetector.onTouchEvent(event)) {
            return false;
        }
        return true;
    }
    
	@Override
	public boolean onDown(MotionEvent arg0) {
		return false;
	}

	@Override
	public boolean onFling(MotionEvent event1, MotionEvent event2, float velocityX,
			               float velocityY) {
		if((event1.getX() - event2.getX()) > SWIPE_MIN_DISTANCE &&
		   Math.abs(velocityX) > SWIPE_THRESHOLD_VELOCITY) {
			synchronized (mEventPasser) {
				mEventPasser.mType |= NativeEvent.SwipeLeft;
			}
            return true;
        }  else if ((event2.getX() - event1.getX()) > SWIPE_MIN_DISTANCE &&
                    Math.abs(velocityX) > SWIPE_THRESHOLD_VELOCITY) {
        	synchronized (mEventPasser) {
				mEventPasser.mType |= NativeEvent.SwipeRight;
			}
            return true;
        }

        if((event1.getY() - event2.getY()) > SWIPE_MIN_DISTANCE &&
           Math.abs(velocityY) > SWIPE_THRESHOLD_VELOCITY) {
        	synchronized (mEventPasser) {
				mEventPasser.mType |= NativeEvent.SwipeTop;
			}
            return true;
        }  else if ((event2.getY() - event1.getY()) > SWIPE_MIN_DISTANCE &&
                    Math.abs(velocityY) > SWIPE_THRESHOLD_VELOCITY) {
        	synchronized (mEventPasser) {
				mEventPasser.mType |= NativeEvent.SwipeBottom;
			}
            return true;
        }
        return false;
	}

	@Override
	public void onLongPress(MotionEvent event) {
	} 

	@Override
	public boolean onScroll(MotionEvent event1, MotionEvent event2, float distanceX,
			float distanceY) {
	
		synchronized (mEventPasser) {
			mEventPasser.mType |= NativeEvent.Scroll;
    		mEventPasser.mX = (int)event2.getX();
    		mEventPasser.mY = (int)event2.getY();
		}
		return true;
	}

	@Override
	public void onShowPress(MotionEvent event) {		
	}  

	@Override
	public boolean onSingleTapUp(MotionEvent event) {
		synchronized (mEventPasser) {
    		mEventPasser.mX = (int)event.getX();
    		mEventPasser.mY = (int)event.getY();
    		mEventPasser.mType |= NativeEvent.SingleTap;
		}
		return true;
	}

	@Override
	public boolean onDoubleTap(MotionEvent event) {
		synchronized (mEventPasser) {
    		mEventPasser.mX = (int)event.getX();
    		mEventPasser.mY = (int)event.getY();
    		mEventPasser.mType |= NativeEvent.DoubleTap;
		}
		return false;
	}

	@Override
	public boolean onDoubleTapEvent(MotionEvent event) {
		return false;
	}

	@Override
	public boolean onSingleTapConfirmed(MotionEvent event) {
		return false;
	}
	
	public void onKeyEvent(int keyCode) {
		synchronized (mEventPasser) {
    		mEventPasser.mKey = keyCode;
    		mEventPasser.mType |= NativeEvent.KeyPressed;
		}
	}
}

