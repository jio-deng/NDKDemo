package com.dengzm.ndkdemo.ndk;

/**
 * @Description for ndk methods
 * Created by deng on 2018/10/11.
 */
public class DzNDK {
    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    public static native String sayHelloNDK();

    //对文件进行加密
    public static native String encryptFile(String normalPath, String encryptPath, String password);

    //对文件进行解密
    public static native String decryptFile(String encryptPath, String decryptPath, String password);
}
