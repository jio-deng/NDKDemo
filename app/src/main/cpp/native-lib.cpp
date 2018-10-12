#include <jni.h>
#include <string>

extern "C"
JNIEXPORT jstring JNICALL
Java_com_dengzm_ndkdemo_ndk_DzNDK_sayHelloNDK(JNIEnv *env, jclass type) {
    return env->NewStringUTF("DZ : hello NDK!");
}

//对文件进行加密
extern "C"
JNIEXPORT jstring JNICALL
Java_com_dengzm_ndkdemo_ndk_DzNDK_encryptFile(JNIEnv *env, jclass type, jstring normalPath_,
                                              jstring encryptPath_, jstring password_) {
    const char *normalPath = env->GetStringUTFChars(normalPath_, 0);
    const char *encryptPath = env->GetStringUTFChars(encryptPath_, 0);
    const char *password = env->GetStringUTFChars(password_, 0);

    int passwordLen = strlen(password);
    FILE *frp = fopen(normalPath, "rb");
    FILE *fwp = fopen(encryptPath, "wb");
    if (frp == NULL) {
        return env->NewStringUTF("文件不存在");
    }
    if (fwp == NULL) {
        return env->NewStringUTF("没有写权限");
    }
    int buffer;
    int index = 0;
    while ((buffer = fgetc(frp)) != EOF) {
        fputc(buffer ^ *(password + (index % passwordLen)), fwp);
        index ++;
    }

    fclose(fwp);
    fclose(frp);

    env->ReleaseStringUTFChars(normalPath_, normalPath);
    env->ReleaseStringUTFChars(encryptPath_, encryptPath);
    env->ReleaseStringUTFChars(password_, password);

    return env->NewStringUTF("加密完成！");
}

//对文件进行解密
extern "C"
JNIEXPORT jstring JNICALL
Java_com_dengzm_ndkdemo_ndk_DzNDK_decryptFile(JNIEnv *env, jclass type, jstring encryptPath_,
                                              jstring decryptPath_, jstring password_) {
    const char *encryptPath = env->GetStringUTFChars(encryptPath_, 0);
    const char *decryptPath = env->GetStringUTFChars(decryptPath_, 0);
    const char *password = env->GetStringUTFChars(password_, 0);

    // TODO
    int passwordLen = strlen(password);
    FILE *frp = fopen(encryptPath, "rb");
    FILE *fwp = fopen(decryptPath, "wb");
    if (frp == NULL) {
        return env->NewStringUTF("文件不存在");
    }
    if (fwp == NULL) {
        return env->NewStringUTF("没有写权限");
    }
    int buffer;
    int index = 0;
    while ((buffer = fgetc(frp)) != EOF) {
        fputc(buffer ^ *(password + (index % passwordLen)), fwp);
        index ++;
    }

    fclose(fwp);
    fclose(frp);

    env->ReleaseStringUTFChars(encryptPath_, encryptPath);
    env->ReleaseStringUTFChars(decryptPath_, decryptPath);
    env->ReleaseStringUTFChars(password_, password);

    return env->NewStringUTF("解密完成！");
}