package com.taolesi.mcengine;

import static com.taolesi.mcengine.QUESTCODE.REQUESTPERMISSION;

import android.Manifest;
import android.annotation.SuppressLint;
import android.app.Activity;
import android.content.Context;
import android.os.Build;
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
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.Reader;
import java.util.Enumeration;
import java.util.zip.ZipEntry;
import java.util.zip.ZipFile;

public class Loader {
    public static native void define();

    public static String sourceDir;
    public static String ExternalCacheDir;
    public static Context context_;
    private static final String[] PERMISSIONS = {
            Manifest.permission.WRITE_EXTERNAL_STORAGE,
            Manifest.permission.READ_EXTERNAL_STORAGE
    };
    private static final String[] PERMISSIONS_33 = {
            Manifest.permission.READ_MEDIA_AUDIO,
            Manifest.permission.READ_MEDIA_IMAGES,
            Manifest.permission.READ_MEDIA_VIDEO,
            //Manifest.permission.MANAGE_EXTERNAL_STORAGE
    };

    @RequiresApi(api = Build.VERSION_CODES.R)
    public static void requestPermissions_33(Context ctx) {
        ((Activity) ctx).requestPermissions(PERMISSIONS_33, REQUESTPERMISSION.ordinal());
    }


    public static void writeFile(InputStream inputStream, File pathFile) throws IOException {
        File parentFile = pathFile.getParentFile();
        if (parentFile != null && !parentFile.exists()) {
            parentFile.mkdirs();
        } else if (pathFile.exists()) {
            pathFile.delete();
        }
        pathFile.createNewFile();
        // 获取文件的输出流
        FileOutputStream out = new FileOutputStream(pathFile);
        int len;
        byte[] buffer = new byte[1024];
        // 读取字节到缓冲区
        while ((len = inputStream.read(buffer)) != -1) {
            // 从缓冲区位置写入字节
            out.write(buffer, 0, len);
            //刷新缓冲区
            out.flush();
        }
        //关闭输出流
        out.close();
    }

    @SuppressLint("UnsafeDynamicallyLoadedCode")
    public static boolean init(Context context, String apkPath) {

        sourceDir = apkPath;
        ExternalCacheDir = context.getExternalCacheDir().toString();
        context_ = context;
        try {
            if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.R) {
                requestPermissions_33(context);
                    /*if (!Environment.isExternalStorageManager()) {
                        Intent request = new Intent(ACTION_MANAGE_ALL_FILES_ACCESS_PERMISSION);
                        ((Activity) context).startActivityForResult(request, REQUESTPERMISSION.ordinal());
                    }*/
            } else {
                ((Activity) context).requestPermissions(PERMISSIONS, REQUESTPERMISSION.ordinal());
            }
            //System.load(apkPath+"!/lib/armeabi-v7a/lib/libmcengine.so");
        } catch (Exception e) {
            Toast.makeText(context, "error " + e.getMessage(), Toast.LENGTH_LONG).show();
        }
//        Toast.makeText(context, "file "+apkPath, Toast.LENGTH_LONG).show();
        try {
            unzip(sourceDir, context.getFilesDir() + "/base");
            //Toast.makeText(context, "success", Toast.LENGTH_LONG).show();
        } catch (Exception e) {
            Toast.makeText(context, "fail" + e.getMessage() , Toast.LENGTH_LONG).show();
        }
        try {
            System.load(apkPath+"!/lib/armeabi-v7a/libc++_shared.so");
            System.load(apkPath+"!/lib/armeabi-v7a/libdobby.so");
            System.load(apkPath+"!/lib/armeabi-v7a/libmcengine.so");
        } catch (Exception e) {
            Toast.makeText(context, "error " + e.getMessage(), Toast.LENGTH_LONG).show();
        }
        try {
            System.load(apkPath+"!/lib/armeabi-v7a/libloader.so");
        } catch (Exception e) {
            Toast.makeText(context, "error " + e.getMessage(), Toast.LENGTH_LONG).show();
        }
        return true;
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
            //Toast(e.toString());
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
    public void runCoreJS(Context context,QuickJS quickJS) {
        try {
            JSContext quickJS_context = quickJS.createContext();
            Toast.makeText(context, "jinru", Toast.LENGTH_SHORT).show();
            //quickJS_context.addJavascriptInterface(new Loader(), "Loader");
            //quickJS_context.addJavascriptInterface(new Examination(), "Examination");
            quickJS_context.addJavascriptInterface(new NativeItem(), "NativeItem");
            Toast.makeText(context, "qqqqq", Toast.LENGTH_SHORT).show();
            try {
                quickJS_context.executeScript(JsonToObjTest1(context.getFilesDir()  + "/base/assets/main.js"), "main.js");
            } catch (QuickJSScriptException e) {
                //throw new RuntimeException(e);
                Toast.makeText(context, e.toString(), Toast.LENGTH_SHORT).show();
            }
            quickJS_context.close();
            quickJS.close();
        } catch (QuickJSScriptException e) {
            Toast.makeText(context, e.toString(), Toast.LENGTH_SHORT).show();
        }

    }
    @JavascriptInterface
    public static void Toast(String str) {
        Toast.makeText(context_, str, Toast.LENGTH_SHORT).show();
    }

    public static void Log(String claz, int nummber) {

    }

    public static void Log(String claz, float nummber) {

    }

    public static void Log(String claz, String str) {

    }
}
