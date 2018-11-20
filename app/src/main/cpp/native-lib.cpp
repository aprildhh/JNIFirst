#include <jni.h>
#include <string>
#include <android/log.h>

extern "C" JNIEXPORT jstring

JNICALL
Java_com_dhh_jnifirst_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject jobj) {

    JavaVM *jvm ;
    env->GetJavaVM(&jvm);

    //set 值的时候调用的是obj
    jclass jcl = env->GetObjectClass(jobj);
    jfieldID jid = env->GetFieldID(jcl, "a", "I");
    env->SetIntField(jobj, jid, 8);

    //static set值的时候调用的是类
    jfieldID jintSid = env->GetStaticFieldID(jcl, "aIntS", "I");
    env->GetStaticIntField(jcl, jintSid);
    env->SetStaticIntField(jcl, jintSid, 60);

    //final 的时候set值被忽略
    jfieldID jfinalId = env->GetFieldID(jcl, "b", "I");
    env->GetIntField(jobj, jfinalId);
//    env->SetIntField(jobj, jfinalId, 22);

    //jni调用没有返回值，没有参数的方法
    jmethodID jmid = env->GetMethodID(jcl,"kong","()V");
    env->CallVoidMethod(jobj,jmid);

    //jni调用有返回值，参数(int,string)的方法
    jmethodID jmIntId = env->GetMethodID(jcl,"getInt","(ILjava/lang/String;)I");
    jstring str = env->NewStringUTF("从JNI中来");
    env->CallIntMethod(jobj,jmIntId,50,str);

    //jni调用没有返回值，没有参数的静态方法
    jmethodID jmsid = env->GetStaticMethodID(jcl,"skong","(I)V");
    env->CallStaticVoidMethod(jcl,jmsid,5);

    //jni调用子类中的方法
    jfieldID jsonid = env->GetFieldID(jcl,"son1","Lcom/dhh/jnifirst/Son;");
    jobject son1 = env->GetObjectField(jobj, jsonid);
    jclass son_cls = env->GetObjectClass(son1);
    jmethodID jsonmid = env->GetMethodID(son_cls, "ride", "()V");
    env->CallVoidMethod(son1, jsonmid);

    //jni通过子类调用父类
    jclass jfcls = env->GetSuperclass(son_cls);
    jmethodID jfmid = env->GetMethodID(jfcls, "car", "()V");
    env->CallNonvirtualVoidMethod(son1, jfcls, jfmid);

    jmethodID father_init = env->GetMethodID(jfcls,"<init>","()V");
    env->NewObject(jfcls, father_init);

    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

extern "C"
JNIEXPORT void JNICALL
Java_com_dhh_jnifirst_MainActivity_test(JNIEnv *env, jobject instance) {

    // TODO

}

extern "C"
JNIEXPORT void JNICALL
Java_com_dhh_jnifirst_MainActivity_arrayFromJava(JNIEnv *env, jobject instance, jintArray iArray) {
    //作为参数传入
    //接收到的Java数组-关联数组--获取指针
    jint* _iArray = env->GetIntArrayElements(iArray, NULL);
    //获取数组长度
    jsize iArraySize = env->GetArrayLength(iArray);
    for (int i = 0; i < iArraySize; ++i) {
        __android_log_print(ANDROID_LOG_ERROR,"JNIArray","%d",_iArray[i]);
    }

    // 释放资源
    env->ReleaseIntArrayElements(iArray, _iArray, 0);

    //复制数组
    //定义数组
    jint b[iArraySize];
    env->GetIntArrayRegion(iArray,0,iArraySize,b);
    for (int i = 0; i < iArraySize; ++i) {
        __android_log_print(ANDROID_LOG_ERROR,"JNIArrayB","%d",b[i]);
    }
}

extern "C"
JNIEXPORT void JNICALL
Java_com_dhh_jnifirst_MainActivity_arrayFromJavaNoParam(JNIEnv *env, jobject jobj) {

    //未作为参数传入
    jclass cls = env->GetObjectClass(jobj);
    jfieldID jarrayId = env->GetFieldID(cls,"iArray","[I");
    jintArray jiArray = static_cast<jintArray>(env->GetObjectField(jobj, jarrayId));

    jsize arrSize = env->GetArrayLength(jiArray);
    jint* _iArray = env->GetIntArrayElements(jiArray,NULL);

    env->ReleaseIntArrayElements(jiArray,_iArray,0);

    jint b[arrSize];
    env->GetIntArrayRegion(jiArray,0,arrSize,b);

}