package com.taolesi.mcengine;

import android.Manifest;
import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.content.pm.ApplicationInfo;
import android.content.pm.PackageManager;
import android.os.Build;
import android.os.Bundle;
import android.os.Environment;
import android.provider.Settings;
import android.widget.Toast;

import de.robv.android.xposed.IXposedHookLoadPackage;
import de.robv.android.xposed.XC_MethodHook;
import de.robv.android.xposed.XposedHelpers;
import de.robv.android.xposed.callbacks.XC_LoadPackage;

public class HookEngine implements IXposedHookLoadPackage {
    public static Context context;
    public static native void setDL(String DLPath);
    public static native void define();
    private final String innerPackageName = "com.taolesi.mcengine";
    private String[] PERMISSIONS = {
            Manifest.permission.WRITE_EXTERNAL_STORAGE,
            Manifest.permission.READ_EXTERNAL_STORAGE,
            Manifest.permission.MANAGE_EXTERNAL_STORAGE
    };
    @Override
    public void handleLoadPackage(XC_LoadPackage.LoadPackageParam loadPackageParam) throws Throwable {
        if (!loadPackageParam.packageName.equals("com.mojang.minecraftpe")) return;

        //XposedBridge.log("Loaded app: " + loadPackageParam.packageName);
        XposedHelpers.findAndHookMethod(Activity.class,"onCreate", Bundle.class, new XC_MethodHook() {
            @Override
            protected void afterHookedMethod(MethodHookParam param) throws Throwable {
                super.afterHookedMethod(param);
                context = (Context) param.thisObject;
                //Toast.makeText(context, "已取得Context", Toast.LENGTH_SHORT).show();
                //Toast.makeText(context, "正在加载so文件", Toast.LENGTH_SHORT).show();
                try{
                    System.loadLibrary("mcengine");
                    //Toast.makeText(context, "mcengine.so加载完毕", Toast.LENGTH_SHORT).show();
                } catch (Exception e) {
                    Toast.makeText(context, e.toString(), Toast.LENGTH_SHORT).show();
                }
//                try {
//                    System.loadLibrary("substrate");
//                    Toast.makeText(context, "substrate.so加载完毕", Toast.LENGTH_SHORT).show();
//                } catch (UnsatisfiedLinkError e) {
//                    Toast.makeText(context, e.toString(), Toast.LENGTH_LONG).show();
//                }
                try {
                    System.loadLibrary("loader");
                    //Toast("loader.so加载完毕");
                    //Toast.makeText(context, "loader.so加载完毕", Toast.LENGTH_SHORT).show();
                } catch (UnsatisfiedLinkError e) {
                    Toast.makeText(context, e.toString(), Toast.LENGTH_LONG).show();
                }
                PackageManager packageManager = null;
                try {
                    packageManager = context.getPackageManager();
                    Toast.makeText(context, packageManager.toString(), Toast.LENGTH_SHORT).show();
                } catch (Exception e) {
                    Toast.makeText(context, e.toString(), Toast.LENGTH_SHORT).show();
                }
                ApplicationInfo applicationInfo = null;
                try {
                    //Toast.makeText(context, "测试", Toast.LENGTH_SHORT).show();
                    if (packageManager != null) {
                        //Toast.makeText(context, "开始", Toast.LENGTH_SHORT).show();
                        applicationInfo = packageManager.getApplicationInfo("com.taolesi.mcengine", 0);
                        try {
                            ApplicationInfo finalApplicationInfo = applicationInfo;
                            ((Activity)context).runOnUiThread(new Runnable() {
                                @Override
                                public void run() {
                                    setDL(finalApplicationInfo.sourceDir);
                                    define();
                                }
                            });
                        } catch (Exception e) {
                            Toast.makeText(context, e.toString(), Toast.LENGTH_SHORT).show();
                        }
                        //Toast.makeText(context, "结束", Toast.LENGTH_SHORT).show();
                    }
                } catch (PackageManager.NameNotFoundException e) {
                    throw new RuntimeException(e);
                }
            }
        });
    }
    public static void Toast(String str) {
        Toast.makeText(context, str, Toast.LENGTH_SHORT).show();
    }
    public static void Log(String claz, int nummber) {

    }
    public static void Log(String claz, float nummber) {

    }
    public static void Log(String claz, String str) {

    }
}
