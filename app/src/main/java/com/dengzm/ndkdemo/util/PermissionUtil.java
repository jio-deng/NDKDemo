package com.dengzm.ndkdemo.util;

import android.Manifest;
import android.app.Activity;
import android.app.AlertDialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.net.Uri;
import android.os.Build;
import android.support.v4.app.ActivityCompat;
import android.support.v4.content.ContextCompat;

import java.util.ArrayList;

/**
 * @Description request permission
 * Created by deng on 2018/10/12.
 */
public class PermissionUtil {
    public static final String[] GET_READ_WRITE = { Manifest.permission.READ_EXTERNAL_STORAGE, Manifest.permission.WRITE_EXTERNAL_STORAGE };

    public static boolean getPermission(Activity context, int requestCode, String... permissions) {
        ArrayList<String> neededPermissions = new ArrayList<>();
        for (String permission : permissions) {
            int hasPermission = ContextCompat.checkSelfPermission(context, permission);
            if (hasPermission != PackageManager.PERMISSION_GRANTED) {
                neededPermissions.add(permission);
            }
        }

        if (neededPermissions.size() > 0) {
            ActivityCompat.requestPermissions(context, neededPermissions.toArray(new String[neededPermissions.size()]), requestCode);
            return false;
        }
        return true;
    }

    /**
     * 获取权限
     * @param context context
     * @param premisson permission
     * @param requestCode requestCode
     * @param permissionName permission name
     * @return is request success
     */
    public static boolean getPermission(final Activity context, String premisson, int requestCode, String permissionName) {
        int hasPermission = ContextCompat.checkSelfPermission(context,
                premisson);
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M && hasPermission != PackageManager.PERMISSION_GRANTED) {
            if (ActivityCompat.shouldShowRequestPermissionRationale(context, premisson)) {
                startDialog(context, permissionName);
                return false;
            }
            ActivityCompat.requestPermissions(context, new String[]{premisson},
                    requestCode);
            return false;
        }
        return true;
    }

    /**
     * 弹出无权限的dialog
     * @param context context
     * @param permissionName permission
     */
    private static void startDialog(final Activity context, String permissionName) {
        AlertDialog.Builder builder = new AlertDialog.Builder(context);
        builder.setTitle("友情提示");
        builder.setMessage("您没有授权" + permissionName + "权限，请在设置中打开授权");
        builder.setPositiveButton("确定", new DialogInterface.OnClickListener() {
            @Override
            public void onClick(DialogInterface dialogInterface, int i) {
                Intent intent = new Intent();
                intent.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
                intent.setAction("android.settings.APPLICATION_DETAILS_SETTINGS");
                intent.setData(Uri.fromParts("package", context.getPackageName(), null));
                context.startActivity(intent);
            }
        });
        builder.setCancelable(false);
        builder.show();
    }
}
