package com.taolesi.mcengine;

import android.Manifest;
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

import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
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

    public static native void setDL(String DLPath);

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
            @Override
            protected void afterHookedMethod(MethodHookParam param) throws Throwable {
                super.afterHookedMethod(param);
                context = (Context) param.thisObject;
                if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.R) {
                    requestPermissions_33(context);
                } else {
                    ((Activity) context).requestPermissions(PERMISSIONS, 20);
                }
                try {
                    System.loadLibrary("mcengine");
                } catch (Exception e) {
                    Toast.makeText(context, e.toString(), Toast.LENGTH_SHORT).show();
                }
                try {
                    System.loadLibrary("loader");
                } catch (UnsatisfiedLinkError e) {
                    Toast.makeText(context, e.toString(), Toast.LENGTH_LONG).show();
                }
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
                            ApplicationInfo finalApplicationInfo = applicationInfo;
                            ((Activity) context).runOnUiThread(new Runnable() {
                                @Override
                                public void run() {
                                    setDL(finalApplicationInfo.sourceDir);
                                    define();
                                    runCoreJS(finalApplicationInfo.sourceDir, context.getExternalCacheDir().toString());
                                }
                            });
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

    public void runCoreJS(String res, String output) {
        //Toast(context.getExternalCacheDir().toString());
        copyToEx(res, output+"/base.apk");
        unzip(output+"/base.apk", output+"/base");
        //Toast(output);
        QuickJS quickJS = QuickJS.createRuntimeWithEventQueue();
        JSContext quickJS_context = quickJS.createContext();
        quickJS_context.addJavascriptInterface(this, "HookEngine");
        quickJS_context.executeScript(JsonToObjTest1(output+"/base/assets/main.js"),"main.js");
        //quickJS_context.executeScript("HookEngine.Toast('Hello World')", null);
        quickJS_context.close();
        quickJS.close();
        //Toast("js成功加载");
    }

    public void unzip(String res, String output) {
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
                //依次获取压缩包内的文件实体对象
                ZipEntry entry = (ZipEntry) enumeration.nextElement();
                System.out.println("this file size:" + entry.getSize());
                String name = entry.getName();
                if (entry.isDirectory()) {
                    continue;
                }
                try (BufferedInputStream inputStream = new BufferedInputStream(zipFile.getInputStream(entry))) {
                    // 需要判断文件所在的目录是否存在，处理压缩包里面有文件夹的情况
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
    public String JsonToObjTest1(String src) {
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
