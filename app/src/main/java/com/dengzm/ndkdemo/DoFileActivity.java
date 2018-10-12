package com.dengzm.ndkdemo;

import android.os.Bundle;
import android.os.Environment;
import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.View;
import android.widget.TextView;

import com.dengzm.ndkdemo.ndk.DzNDK;
import com.dengzm.ndkdemo.util.PermissionUtil;

import java.io.File;

/**
 * @Description operate file
 * Created by deng on 2018/10/11.
 */
public class DoFileActivity extends AppCompatActivity implements View.OnClickListener {
    private static final String TAG = "DoFileActivity";
    private static final String sdCardPath = Environment.getExternalStorageDirectory().getAbsolutePath();

    private TextView mTvShowMsg;

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_do_file);

        mTvShowMsg = findViewById(R.id.tv_show);
        findViewById(R.id.btn_file_encrypt).setOnClickListener(this);
        findViewById(R.id.btn_file_decrypt).setOnClickListener(this);
        findViewById(R.id.btn_file_segment).setOnClickListener(this);
        findViewById(R.id.btn_file_combine).setOnClickListener(this);
    }

    /**
     * 文件加密
     */
    private void fileEncrypt() {
        String normalPath = sdCardPath + File.separatorChar + "lbxx.png";
        String encryptPath = sdCardPath + File.separatorChar + "lbxx_encrypt.png";
        Log.d(TAG, "fileEncrypt: normalPath = " + normalPath + ", encryptPath = " + encryptPath);

        try {
            String msg = DzNDK.encryptFile(normalPath, encryptPath, "dz");
            mTvShowMsg.setText(msg);
        } catch (Exception e) {
            e.printStackTrace();
            Log.e(TAG, "fileEncrypt: sth is wrong in Java_com_dengzm_ndkdemo_ndk_DzNDK_encryptFile");
        }
    }

    /**
     * 文件解密
     */
    private void fileDecrypt() {
        String encryptPath = sdCardPath + File.separatorChar + "lbxx_encrypt.png";
        String decryptPath = sdCardPath + File.separatorChar + "lbxx_decrypt.png";
        Log.d(TAG, "fileEncrypt: encryptPath = " + encryptPath + ", decryptPath = " + decryptPath);

        try {
            String msg = DzNDK.decryptFile(encryptPath, decryptPath, "dz");
            mTvShowMsg.setText(msg);
        } catch (Exception e) {
            e.printStackTrace();
            Log.e(TAG, "fileDecrypt: sth is wrong in Java_com_dengzm_ndkdemo_ndk_DzNDK_decryptFile");
        }

    }

    /**
     * 文件分割
     */
    private void fileSegment() {
        String splitFilePath = sdCardPath + File.separatorChar + "my_doc.docx";
        String suffix = ".dz";
        Log.d(TAG, "fileSegment: splitFilePath = " + splitFilePath + ", suffix = " + suffix);

        try {
            String msg = DzNDK.fileSplit(splitFilePath, suffix, 4);
            mTvShowMsg.setText(msg);
        } catch (Exception e) {
            e.printStackTrace();
            Log.e(TAG, "fileSegment: sth is wrong in Java_com_dengzm_ndkdemo_ndk_DzNDK_fileSplit");
        }
    }

    /**
     * 文件合并
     */
    private void fileCombine() {
        String splitFilePath = sdCardPath + File.separatorChar + "my_doc.docx";
        String newFilePath = sdCardPath + File.separatorChar + "my_doccc.docx";
        String splitSuffix = ".dz";
        String mergeSuffix = ".png";
        Log.d(TAG, "fileCombine: splitFilePath = " + splitFilePath + ", suffix = " + splitSuffix + ", mergeSuffix = " + mergeSuffix);

        try {
            String msg = DzNDK.fileMerge(splitFilePath, newFilePath, splitSuffix, mergeSuffix, 4);
            mTvShowMsg.setText(msg);
        } catch (Exception e) {
            e.printStackTrace();
            Log.e(TAG, "fileCombine: sth is wrong in Java_com_dengzm_ndkdemo_ndk_DzNDK_fileMerge");
        }
    }

    @Override
    public void onClick(View v) {
        if (PermissionUtil.getPermission(this, 101, PermissionUtil.GET_READ_WRITE)) {
            switch (v.getId()) {
                case R.id.btn_file_encrypt:
                    fileEncrypt();
                    break;
                case R.id.btn_file_decrypt:
                    fileDecrypt();
                    break;
                case R.id.btn_file_segment:
                    fileSegment();
                    break;
                case R.id.btn_file_combine:
                    fileCombine();
                    break;
            }
        }
    }
}
