package com.dhh.jnifirst;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    int a;
    static int aIntS;
    final int b = 50;

    Son son1 = new Son ();

    int[] iArray = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary ( "native-lib" );
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate ( savedInstanceState );
        setContentView ( R.layout.activity_main );

        // Example of a call to a native method
        TextView tv = (TextView) findViewById ( R.id.sample_text );
        tv.setText ( stringFromJNI () );
        Log.e ( "FromJni", "输出--》  " + a );

        //访问java基本类型数组
        //作为参数传入
        arrayFromJava ( iArray );
        for (int i = 0; i < iArray.length; i++) {
            Log.e ( "FromJava", "" + iArray[i] );
        }
    }

    public void kong() {
        Log.e ( "JNI", "java中没有调用哦！" );
    }

    public int getInt(int a, String str) {
        Log.e ( "JNI", "java中没有调用getInt()方法哦！" + "str = " + str + "，a = " + a );
        return a;
    }

    public static void skong(int a) {
        Log.e ( "JNIStatic", "java中没有调用这个静态方法哦！  " + "a=" + a );
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();

    public native void test();

    //访问java基本类型数组
    //作为参数传入
    public native void arrayFromJava(int[] iArray);

    public native void arrayFromJavaNoParam();
}
