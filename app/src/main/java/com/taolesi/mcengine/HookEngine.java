package com.taolesi.mcengine;


import static com.taolesi.mcengine.FileTools.JsonToObjTest;
import static com.taolesi.mcengine.FileTools.unzip;

import android.Manifest;
import android.annotation.SuppressLint;
import android.app.Activity;
import android.app.Application;
import android.content.Context;
import android.content.pm.ApplicationInfo;
import android.content.pm.PackageManager;
import android.content.res.AssetManager;
import android.os.Build;
import android.os.Bundle;
import android.os.Environment;
import android.widget.Toast;

import androidx.core.app.ActivityCompat;

import com.fasterxml.jackson.core.type.TypeReference;
import com.fasterxml.jackson.databind.ObjectMapper;
import com.quickjs.JSContext;
import com.quickjs.QuickJS;
import com.quickjs.QuickJSScriptException;

import java.io.File;
import java.io.IOException;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Map;

import dalvik.system.DexClassLoader;
import de.robv.android.xposed.IXposedHookLoadPackage;
import de.robv.android.xposed.XC_MethodHook;
import de.robv.android.xposed.XC_MethodReplacement;
import de.robv.android.xposed.XposedHelpers;
import de.robv.android.xposed.callbacks.XC_LoadPackage;


public class HookEngine implements IXposedHookLoadPackage {

    public static Activity getTargetActivity() {
        return targetActivity;
    }

    public static void setTargetActivity(Activity target_activity) {
        HookEngine.targetActivity = target_activity;
    }

    public static Activity targetActivity;

    public static Context getTargetContext() {
        return targetContext;
    }

    public static void setTargetContext(Context targetContext) {
        HookEngine.targetContext = targetContext;
    }

    public static Context targetContext;

    @Override
    public void handleLoadPackage(XC_LoadPackage.LoadPackageParam loadPackageParam) throws Throwable {
        if (!loadPackageParam.packageName.equals("com.mojang.minecraftpe")) return;
        XposedHelpers.findAndHookMethod(Activity.class, "onCreate", Bundle.class, new XC_MethodHook() {
            protected void beforeHookedMethod(MethodHookParam param) throws Throwable {
                Context ctx = (Context) param.thisObject;
                setTargetActivity((Activity) param.thisObject);
                AssetManager assetManager_org = ctx.getAssets();
                Method addAssetPath = AssetManager.class.getDeclaredMethod("addAssetPath", String.class);
                addAssetPath.invoke(assetManager_org, Environment.getExternalStorageDirectory() + "/games/MCEngine/assets.zip");
                //Toast.makeText(ctx, Arrays.toString(assetManager_org.list("")), Toast.LENGTH_SHORT).show();
                super.beforeHookedMethod(param);
            }

            protected void afterHookedMethod(MethodHookParam param) throws Throwable {
                super.afterHookedMethod(param);
                boolean isOwnPermission = true;
                setTargetActivity((Activity) param.thisObject);
                //储存activity
                setTargetContext(getTargetActivity());
                //储存Context(这样写是某种好习惯
                if (Build.VERSION.SDK_INT >= 30) {
                    String[] permissions = {
                            Manifest.permission.READ_MEDIA_AUDIO,
                            Manifest.permission.READ_MEDIA_IMAGES,
                            Manifest.permission.READ_MEDIA_VIDEO,
                    };
                    //验证是否许可权限
                    for (String str : permissions) {
                        if (ActivityCompat.checkSelfPermission(getTargetContext(), str) != PackageManager.PERMISSION_GRANTED) {
                            //申请权限
                            ActivityCompat.requestPermissions(getTargetActivity(), permissions, 101);
                            isOwnPermission = false;
                        }
                    }
                } else {
                    String[] permissions = {
                            Manifest.permission.READ_EXTERNAL_STORAGE,
                            Manifest.permission.WRITE_EXTERNAL_STORAGE,
                    };
                    //验证是否许可权限
                    for (String str : permissions) {
                        if (ActivityCompat.checkSelfPermission(getTargetContext(), str) != PackageManager.PERMISSION_GRANTED) {
                            //申请权限
                            ActivityCompat.requestPermissions(getTargetActivity(), permissions, 101);
                            isOwnPermission = false;
                        }
                    }
                }

                ApplicationInfo info = getTargetContext().getPackageManager().getApplicationInfo("com.taolesi.mcengine", 0);
                //模块的信息
                ApplicationInfo mcInfo = getTargetContext().getPackageManager().getApplicationInfo("com.mojang.minecraftpe", 0);
                //mc的信息
                String path = new File(info.sourceDir).getAbsolutePath();//模块base.apk的目录
                String entry = "com.taolesi.mcengine.Loader";
                String fun = "init";
                // 重定向lib目录 让load找到正确的加载
                String mcLib = mcInfo.nativeLibraryDir;//mc的lib路径
                String mcFileDir = getTargetContext().getFilesDir().getAbsolutePath();

                try {
                    unzip(getTargetContext(), path, mcFileDir + "/base");//将base.apk解压到mc的data的files下面
                } catch (Exception e) {
                    Toast.makeText(getTargetContext(), e.toString(), Toast.LENGTH_SHORT).show();
                }
                String newLibDir = mcFileDir + "/base/lib/armeabi-v7a/";//模块的新lib路径 32位
                String architecture = System.getProperty("os.arch");
                if (architecture.contains("64")) {
                    newLibDir = mcFileDir + "/base/lib/arm64-v8a/";//模块的新lib路径 64位
                }
                String output = getTargetContext().getDir("cache_dex", 0).getAbsolutePath();//不懂
                boolean isOpen = false;
                try {
                    ClassLoader loader = getTargetContext().getClassLoader();
                    DexClassLoader newLoader = new DexClassLoader(path, output, newLibDir, loader);
                    SoLibraryPatcher.patchNativeLibraryDir(newLoader, mcLib);//重定向lib目录
                    Class clazz = newLoader.loadClass(entry);
                    Method method = clazz.getDeclaredMethod(fun, Context.class, String.class, String.class);
                    method.invoke(null, getTargetContext(), path, mcLib);//调用
                } catch (ClassNotFoundException | NoSuchFieldException | IllegalAccessException |
                         NoSuchMethodException | InvocationTargetException |
                         InstantiationException | SecurityException | IllegalArgumentException e) {
                    Toast.makeText(getTargetContext(), e.toString(), Toast.LENGTH_SHORT).show();
                }
            }
        });
    }
}
