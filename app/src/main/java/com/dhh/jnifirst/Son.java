package com.dhh.jnifirst;

import android.util.Log;

/**
 * Created by DHH on 2018/11/10.
 * 页面：
 */
public class Son extends Father {
    public Son() {
    }

    public void ride(){
        Log.e ( "JNI","我是子类，我会骑车！" );
    }
}
