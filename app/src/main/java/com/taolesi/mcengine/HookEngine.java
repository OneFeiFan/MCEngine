package com.taolesi.mcengine;


import static com.taolesi.mcengine.UsefullTools.FileTools.unzip;

import android.Manifest;
import android.app.Activity;
import android.content.Context;
import android.content.pm.ApplicationInfo;
import android.content.res.AssetManager;
import android.os.Build;
import android.os.Bundle;
import android.os.Environment;
import android.widget.Toast;

import androidx.activity.result.contract.ActivityResultContracts;

import com.taolesi.mcengine.ModHelper.Loader;
import com.taolesi.mcengine.ModHelper.SoLibraryPatcher;

import java.io.File;
import java.lang.ref.WeakReference;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;

import dalvik.system.DexClassLoader;
import de.robv.android.xposed.IXposedHookLoadPackage;
import de.robv.android.xposed.XC_MethodHook;
import de.robv.android.xposed.XposedHelpers;
import de.robv.android.xposed.callbacks.XC_LoadPackage;


public class HookEngine implements IXposedHookLoadPackage {

    private static WeakReference<Context> targetActivity;
    private static Context getTargetContext() {
        return targetActivity.get();
    }

    private static void setTargetContext(Context target_activity) {
        targetActivity = new WeakReference<>(target_activity);
    }

    @Override
    public void handleLoadPackage(XC_LoadPackage.LoadPackageParam loadPackageParam) throws Throwable {
        if (!loadPackageParam.packageName.equals("com.mojang.minecraftpe")) return;
        XposedHelpers.findAndHookMethod(Activity.class, "onCreate", Bundle.class, new XC_MethodHook() {
            protected void beforeHookedMethod(MethodHookParam param) throws Throwable {
                Context ctx = (Context) param.thisObject;
                setTargetContext(ctx);
                if (Build.VERSION.SDK_INT >= 33) {
                    if (!Environment.isExternalStorageManager()) {
                        ((Activity)param.thisObject).requestPermissions(new String[] {Manifest.permission.READ_EXTERNAL_STORAGE, Manifest.permission.WRITE_EXTERNAL_STORAGE}, QUESTCODE.REQUESTPERMISSION.ordinal());
                    }
                } else {
                    ((Activity)param.thisObject).requestPermissions(new String[] {Manifest.permission.READ_EXTERNAL_STORAGE, Manifest.permission.WRITE_EXTERNAL_STORAGE}, QUESTCODE.REQUESTPERMISSION.ordinal());
                }
                AssetManager assetManager_org = ctx.getAssets();
                Method addAssetPath = AssetManager.class.getDeclaredMethod("addAssetPath", String.class);
                addAssetPath.invoke(assetManager_org, Environment.getExternalStorageDirectory() + "/games/MCEngine/assets.zip");
                super.beforeHookedMethod(param);
            }

            protected void afterHookedMethod(MethodHookParam param) throws Throwable {
                super.afterHookedMethod(param);
                setTargetContext((Activity) param.thisObject);
                //储存activity
                setTargetContext(getTargetContext());

                if (Build.VERSION.SDK_INT >= 33) {
                    if (!Environment.isExternalStorageManager()) {
                        ((Activity)param.thisObject).requestPermissions(new String[] {Manifest.permission.READ_EXTERNAL_STORAGE, Manifest.permission.WRITE_EXTERNAL_STORAGE}, QUESTCODE.REQUESTPERMISSION.ordinal());
                    }
                } else {
                    ((Activity)param.thisObject).requestPermissions(new String[] {Manifest.permission.READ_EXTERNAL_STORAGE, Manifest.permission.WRITE_EXTERNAL_STORAGE}, QUESTCODE.REQUESTPERMISSION.ordinal());
                }
                //储存Context(这样写是某种好习惯

                ApplicationInfo info = getTargetContext().getPackageManager().getApplicationInfo("com.taolesi.mcengine", 0);
                //模块的信息
                ApplicationInfo mcInfo = getTargetContext().getPackageManager().getApplicationInfo("com.mojang.minecraftpe", 0);
                //mc的信息
                String path = new File(info.sourceDir).getAbsolutePath();//模块base.apk的目录
                String entry = "com.taolesi.mcengine.ModHelper.Loader";
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
                if (architecture != null && architecture.contains("64")) {
                    newLibDir = mcFileDir + "/base/lib/arm64-v8a/";//模块的新lib路径 64位
                }
                String output = getTargetContext().getDir("cache_dex", 0).getAbsolutePath();//不懂
                try {
                    ClassLoader loader = getTargetContext().getClassLoader();
                    DexClassLoader newLoader = new DexClassLoader(path, output, newLibDir, loader);
                    SoLibraryPatcher.patchNativeLibraryDir(newLoader, mcLib);//重定向lib目录
                    Class<?> clazz = newLoader.loadClass(entry);
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
