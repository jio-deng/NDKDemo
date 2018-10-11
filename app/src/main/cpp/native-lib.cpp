#include <jni.h>
#include <string>

extern "C"
JNIEXPORT jstring

JNICALL
Java_com_dengzm_ndkdemo_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_dengzm_ndkdemo_ndk_DzNDK_sayHelloNDK(JNIEnv *env, jclass type) {
    return env->NewStringUTF("DZ : hello NDK!");
}extern "C"
JNIEXPORT jstring JNICALL
Java_com_dengzm_ndkdemo_MainActivity_sayHelloNDK(JNIEnv *env, jobject instance) {
    return env->NewStringUTF("DZ : hello NDK!");
}