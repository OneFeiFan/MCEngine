package com.taolesi.mcengine;

import android.Manifest;
import android.annotation.SuppressLint;
import android.app.Activity;
import android.content.Context;
import android.content.pm.ApplicationInfo;
import android.content.pm.PackageManager;
import android.os.Build;
import android.os.Bundle;
import android.webkit.JavascriptInterface;
import android.widget.Toast;

import androidx.annotation.RequiresApi;

import com.quickjs.JSContext;
import com.quickjs.QuickJS;
import com.quickjs.QuickJSScriptException;

import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.Reader;
import java.util.Enumeration;
import java.util.zip.ZipEntry;
import java.util.zip.ZipFile;

import de.robv.android.xposed.IXposedHookLoadPackage;
import de.robv.android.xposed.XC_MethodHook;
import de.robv.android.xposed.XposedHelpers;
import de.robv.android.xposed.callbacks.XC_LoadPackage;


public class HookEngine implements IXposedHookLoadPackage {
    public static Context context;
    public static String sourceDir;
    public static String ExternalCacheDir;

    public native void setDL(String DLPath);

    public static native void define();

    public static native void copyToEx(String res, String output);

    private final String innerPackageName = "com.taolesi.mcengine";
    private final String[] PERMISSIONS = {
            Manifest.permission.WRITE_EXTERNAL_STORAGE,
            Manifest.permission.READ_EXTERNAL_STORAGE
    };
    private final String[] PERMISSIONS_33 = {
            Manifest.permission.WRITE_EXTERNAL_STORAGE,
            Manifest.permission.READ_EXTERNAL_STORAGE,
            Manifest.permission.MANAGE_EXTERNAL_STORAGE
    };

    @RequiresApi(api = Build.VERSION_CODES.R)
    public void requestPermissions_33(Context ctx) {
        ((Activity) ctx).requestPermissions(PERMISSIONS_33, 20);
    }

    @Override
    public void handleLoadPackage(XC_LoadPackage.LoadPackageParam loadPackageParam) throws Throwable {
        if (!loadPackageParam.packageName.equals("com.mojang.minecraftpe")) return;
        XposedHelpers.findAndHookMethod(Activity.class, "onCreate", Bundle.class, new XC_MethodHook() {
            @SuppressLint("UnsafeDynamicallyLoadedCode")
            @Override
            protected void afterHookedMethod(MethodHookParam param) throws Throwable {
                super.afterHookedMethod(param);
                context = (Context) param.thisObject;
                if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.R) {
                    requestPermissions_33(context);
                } else {
                    ((Activity) context).requestPermissions(PERMISSIONS, 20);
                }
                /*try {
                    System.loadLibrary("mcengine");
                } catch (Exception e) {
                    Toast.makeText(context, e.toString(), Toast.LENGTH_SHORT).show();
                }
                try {
                    System.loadLibrary("loader");
                } catch (UnsatisfiedLinkError e) {
                    Toast.makeText(context, e.toString(), Toast.LENGTH_LONG).show();
                }*/
                PackageManager packageManager = null;
                try {
                    packageManager = context.getPackageManager();
                } catch (Exception e) {
                    Toast.makeText(context, e.toString(), Toast.LENGTH_SHORT).show();
                }
                ApplicationInfo applicationInfo = null;
                try {
                    if (packageManager != null) {
                        applicationInfo = packageManager.getApplicationInfo("com.taolesi.mcengine", 0);
                        try {
                            sourceDir = applicationInfo.sourceDir;
                            ExternalCacheDir = context.getExternalCacheDir().toString();
                            System.load(sourceDir + "!/lib/armeabi-v7a/libmcengine.so");
                            System.load(sourceDir + "!/lib/armeabi-v7a/libloader.so");

                            //Toast(sourceDir + "!/lib/armeabi-v7a/libmcengine.so");
                            define();
                            setDL(applicationInfo.sourceDir);
                            //runCoreJS();
                        } catch (Exception e) {
                            Toast.makeText(context, e.toString(), Toast.LENGTH_SHORT).show();
                        }
                    }
                } catch (PackageManager.NameNotFoundException e) {
                    throw new RuntimeException(e);
                }
            }
        });
    }

    public void runCoreJS() {
        try {
            copyToEx(sourceDir, ExternalCacheDir + "/base.apk");
            unzip(ExternalCacheDir + "/base.apk", ExternalCacheDir + "/base");
            //runQuickJS(JsonToObjTest1(ExternalCacheDir + "/base/assets/main.js"));
            QuickJS quickJS = QuickJS.createRuntimeWithEventQueue();
            JSContext quickJS_context = quickJS.createContext();
            quickJS_context.addJavascriptInterface(this, "HookEngine");
            quickJS_context.addJavascriptInterface(new Examination(), "Examination");
            quickJS_context.addJavascriptInterface(new NativeItem(), "NativeItem");
            try {
                quickJS_context.executeScript(JsonToObjTest1(ExternalCacheDir + "/base/assets/main.js"), "main.js");
            } catch (QuickJSScriptException e) {
                throw new RuntimeException(e);
            }
            quickJS_context.close();
            quickJS.close();
        } catch (QuickJSScriptException e) {
            Toast(e.toString());
        }

    }

    public static void unzip(String res, String output) {
        //targetPath输出文件路径
        File targetFile = new File(output);
        // 如果目录不存在，则创建
        if (!targetFile.exists()) {
            targetFile.mkdirs();
        } else {
            targetFile.delete();
            targetFile.mkdirs();
        }
        //sourcePath压缩包文件路径
        try (ZipFile zipFile = new ZipFile(new File(res))) {
            System.out.println("file nums:" + zipFile.size());
            Enumeration enumeration = zipFile.entries();
            while (enumeration.hasMoreElements()) {
                ZipEntry entry = (ZipEntry) enumeration.nextElement();
                System.out.println("this file size:" + entry.getSize());
                String name = entry.getName();
                if (entry.isDirectory()) {
                    continue;
                }
                try (BufferedInputStream inputStream = new BufferedInputStream(zipFile.getInputStream(entry))) {
                    String outName = output + "/" + name;
                    File outFile = new File(outName);
                    File tempFile = new File(outName.substring(0, outName.lastIndexOf("/")));
                    if (!tempFile.exists()) {
                        tempFile.mkdirs();
                    }
                    try (BufferedOutputStream outputStream = new BufferedOutputStream(new FileOutputStream(outFile))) {
                        int len;
                        byte[] buffer = new byte[1024];
                        while ((len = inputStream.read(buffer)) > 0) {
                            outputStream.write(buffer, 0, len);
                        }
                    }

                }

            }

        } catch (Exception e) {
            Toast(e.toString());
        }
    }

    public static String JsonToObjTest1(String src) {
        try {
            File jsonFile = new File(src);
            FileReader fileReader = new FileReader(jsonFile);
            Reader reader = new InputStreamReader(new FileInputStream(jsonFile), "utf-8");
            StringBuffer sb = new StringBuffer();
            while (true) {
                int ch = reader.read();
                if (ch != -1) {
                    sb.append((char) ch);
                } else {
                    fileReader.close();
                    reader.close();
                    String jsonStr = sb.toString();
                    return jsonStr;
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
            return e.toString();
        }
    }

    @JavascriptInterface
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
