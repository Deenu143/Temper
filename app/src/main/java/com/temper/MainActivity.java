package com.temper;

import android.app.Activity;
import android.os.Bundle;

public class MainActivity extends Activity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }
	static {
		System.loadLibrary("app-integrity-checker");
	}
	
	public native boolean checkIntegrity();
}