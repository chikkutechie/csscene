
package com.chikkooos.android.viewer;

import java.io.IOException;
import java.util.ArrayList;

import android.app.Activity;
import android.app.AlarmManager;
import android.app.PendingIntent;
import android.content.Context;
import android.content.Intent;
import android.content.res.AssetManager;
import android.content.res.Configuration;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.ListView;

public class ViewerActivity extends Activity {
	
	private ViewerApplication mApp;
	private static final int restartDelay = 500;
	
    @Override protected void onCreate(Bundle b) {
        super.onCreate(b);
        
        mApp = (ViewerApplication)getApplication();

        setContentView(R.layout.main);
        
        AssetManager assetManager = getAssets();
        ArrayList<String> sceneFiles = new ArrayList<String>();
        
        try {
			String[] files = assetManager.list("data");
			for(int i=0; i<files.length; i++) {
				if (files[i].endsWith(".xml")) {
					sceneFiles.add(files[i]);
				}
			}
		} catch (IOException e) {
		}
        
        final ListView listview = (ListView) findViewById(R.id.listview);
        ArrayAdapter<String> adapter = new ArrayAdapter<String>(this, android.R.layout.simple_list_item_1, sceneFiles);
        listview.setAdapter(adapter);
        
        listview.setOnItemClickListener(new AdapterView.OnItemClickListener() {

			@Override
			public void onItemClick(AdapterView<?> parent, View view, int position,
					long id) {
				
				final String scene = (String) parent.getItemAtPosition(position);
				Intent i = new Intent(ViewerActivity.this, ViewerRendererActivity.class);
				i.putExtra("scene", "data/" + scene);
				startActivity(i);
			}
        });
    }
    
    @Override
    public void onConfigurationChanged(Configuration newConfig) {
    	super.onConfigurationChanged(newConfig);
    }
    
    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        MenuInflater inflater = getMenuInflater();
        inflater.inflate(R.layout.menu, menu);
        return true;
    }
    
    @Override
    public boolean onPrepareOptionsMenu(Menu menu) {
    	boolean res = super.onPrepareOptionsMenu(menu);
    	
    	MenuItem gles1item = (MenuItem)findViewById(R.id.gles1);
    	MenuItem gles2item = (MenuItem)findViewById(R.id.gles2);
        if (mApp.clientVersion() == 1) {
        	if (gles1item != null) {
        		gles1item.setChecked(true);
        	}
        	if (gles2item != null) {
        		gles2item.setChecked(false);
        	}
        } else {
        	if (gles2item != null) {
        		gles2item.setChecked(true);
        	}
        	if (gles1item != null) {
        		gles1item.setChecked(false);
        	}
        }
        
        return res;
    }
    
    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        switch (item.getItemId()) {
            case R.id.gles1:
            	if (mApp.setGc("gles1")) {
            		restart();
            	}
                return true;
            case R.id.gles2:
            	if (mApp.setGc("gles2")) {
            		restart();
            	}
                return true;
            default:
                return super.onOptionsItemSelected(item);
        }
    }
    
	private void restart() {
		 PendingIntent intent = PendingIntent.getActivity(this.getBaseContext(), 0, new Intent(getIntent()), getIntent().getFlags());
		 AlarmManager manager = (AlarmManager) this.getSystemService(Context.ALARM_SERVICE);
		 manager.set(AlarmManager.RTC, System.currentTimeMillis() + restartDelay, intent);
		 System.exit(2);
	}
    
}


