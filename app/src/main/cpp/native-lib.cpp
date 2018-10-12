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

//分割文件
extern "C"
JNIEXPORT jstring JNICALL
Java_com_dengzm_ndkdemo_ndk_DzNDK_fileSplit(JNIEnv *env, jclass type, jstring splitFilePath_,
                                            jstring suffix_, jint fileNum) {
    const char *splitFilePath = env->GetStringUTFChars(splitFilePath_, 0);
    const char *suffix = env->GetStringUTFChars(suffix_, 0);

    //分割文件的路径列表
    char** split_path_list = new char*[sizeof(char*) * fileNum];

    FILE *frp = fopen(splitFilePath, "rb");
    if (frp == NULL) {
        return env->NewStringUTF("文件不存在");
    }
    //获取文件大小
    fseek(frp, 0L, SEEK_END);
    int file_size = ftell(frp);
    //获取文件名称长度
    int file_path_str_len = strlen(splitFilePath);
    //组合路径
    char file_path[file_path_str_len + 5];
    strcpy(file_path, splitFilePath);
    strtok(file_path, ".");
    strcat(file_path, "_%d");
    strcat(file_path, suffix);

    //拼接文件名
    int i = 0;
    for (; i < fileNum; ++i) {
        split_path_list[i] = new char[128];
        sprintf(split_path_list[i], file_path, (i + 1));
    }
    //可以平均分割时，平均分割；不能时，-1分割，剩余为最后一个
    if (file_size % fileNum) {
        int part_file_size = file_size / fileNum;
        i = 0;
        for (; i < fileNum; ++i) {
            FILE *fwp = fopen(split_path_list[i], "wb");
            if (fwp == NULL) {
                return env->NewStringUTF("没有写入权限");
            }
            int j = 0;
            for (; j < part_file_size; j ++) {
                fputc(fgetc(frp), fwp);
            }
            fclose(fwp);
        }
    } else {
        int part_file_size = file_size / (fileNum - 1);
        i = 0;
        for (; i < fileNum - 1; i ++) {
            FILE *fwp = fopen(split_path_list[i], "wb");
            if (fwp == NULL) {
                return env->NewStringUTF("没有写入权限");
            }
            int j = 0;
            for (; j < part_file_size; j ++) {
                fputc(fgetc(frp), fwp);
            }
            fclose(fwp);
        }
        //最后一个，保存剩余数据
        FILE *fwp = fopen(split_path_list[fileNum - 1], "wb");
        for (int j = 0; j < file_size % (fileNum - 1); ++j) {
            fputc(fgetc(frp), fwp);
        }
        fclose(fwp);
    }

    fclose(frp);

    env->ReleaseStringUTFChars(splitFilePath_, splitFilePath);
    env->ReleaseStringUTFChars(suffix_, suffix);

    return env->NewStringUTF("文件分割完成!");
}

//合并文件
extern "C"
JNIEXPORT jstring JNICALL
Java_com_dengzm_ndkdemo_ndk_DzNDK_fileMerge(JNIEnv *env, jclass type, jstring splitFilePath_,jstring newFilePath_,
                                            jstring splitSuffix_, jstring mergeSuffix_,
                                            jint fileNum) {
    const char *splitFilePath = env->GetStringUTFChars(splitFilePath_, 0);
    const char *newFilePath = env->GetStringUTFChars(newFilePath_, 0);
    const char *splitSuffix = env->GetStringUTFChars(splitSuffix_, 0);
    const char *mergeSuffix = env->GetStringUTFChars(mergeSuffix_, 0);

    //分割文件的路径列表
    char** split_path_list = new char*[sizeof(char*) * fileNum];

    FILE *fwp = fopen(newFilePath, "wb");
    if (fwp == NULL) {
        return env->NewStringUTF("没有写入权限!");
    }

    //获取文件名称长度
    int file_path_str_len = strlen(splitFilePath);
    //组合路径
    char file_path[file_path_str_len + 5];
    strcpy(file_path, splitFilePath);
    strtok(file_path, ".");
    strcat(file_path, "_%d");
    strcat(file_path, splitSuffix);

    //拼接文件名
    int i = 0;
    for (; i < fileNum; ++i) {
        split_path_list[i] = new char[128];
        sprintf(split_path_list[i], file_path, (i + 1));
    }

    //合并文件
    for (i = 0; i < fileNum; ++i) {
        FILE *frp = fopen(split_path_list[i], "rb");
        if (frp == NULL) {
            return env->NewStringUTF("没有找到dz文件！");
        }
        fseek(frp, 0L, SEEK_END);
        int split_file_size = ftell(frp);
        for (int j = 0; j < split_file_size; ++j) {
            fputc(fgetc(frp), fwp);
        }
        fclose(frp);
    }

    fclose(fwp);

    env->ReleaseStringUTFChars(splitFilePath_, splitFilePath);
    env->ReleaseStringUTFChars(newFilePath_, newFilePath);
    env->ReleaseStringUTFChars(splitSuffix_, splitSuffix);
    env->ReleaseStringUTFChars(mergeSuffix_, mergeSuffix);

    return env->NewStringUTF("文件合并完成!");
}