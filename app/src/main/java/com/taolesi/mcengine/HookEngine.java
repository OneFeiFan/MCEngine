package com.taolesi.mcengine;


import static android.provider.Settings.ACTION_MANAGE_ALL_FILES_ACCESS_PERMISSION;
import static com.taolesi.mcengine.FileTools.unzip;
import static com.taolesi.mcengine.QUESTCODE.REQUESTPERMISSION;

import android.Manifest;
import android.annotation.SuppressLint;
import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.content.pm.ApplicationInfo;
import android.content.pm.PackageManager;
import android.os.Build;
import android.os.Bundle;
import android.os.Environment;
import android.webkit.JavascriptInterface;
import android.widget.Toast;

import androidx.activity.result.contract.ActivityResultContracts;
import androidx.annotation.RequiresApi;
import androidx.core.app.ActivityCompat;

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
import java.lang.reflect.Method;
import java.util.ArrayList;
import java.util.Enumeration;
import java.util.List;
import java.util.Map;
import java.util.zip.ZipEntry;
import java.util.zip.ZipFile;

import dalvik.system.DexClassLoader;
import de.robv.android.xposed.IXposedHookLoadPackage;
import de.robv.android.xposed.XC_MethodHook;
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

    public void runCoreJS1() {
        Toast.makeText(getTargetContext(), "trse", Toast.LENGTH_SHORT).show();
//

    }

    @Override
    public void handleLoadPackage(XC_LoadPackage.LoadPackageParam loadPackageParam) throws Throwable {
        if (!loadPackageParam.packageName.equals("com.mojang.minecraftpe")) return;
        XposedHelpers.findAndHookMethod(Activity.class, "onCreate", Bundle.class, new XC_MethodHook() {
            @SuppressLint("UnsafeDynamicallyLoadedCode")
            @Override
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
//                if(!isOwnPermission){
//                    Toast.makeText(getTargetContext(), "MC没有文件读写权限,模块未成功运行,请在授权后重启MC", Toast.LENGTH_SHORT).show();
//                    Toast.makeText(getTargetContext(), "MC没有文件读写权限,模块未成功运行,请在授权后重启MC", Toast.LENGTH_SHORT).show();
//                    return;
//                }
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
                unzip(getTargetContext(), path, mcFileDir + "/base");//将base.apk解压到mc的data的files下面
                String newLibDir = mcFileDir + "/base/lib/armeabi-v7a/";//模块的新lib路径
                String output = getTargetContext().getDir("cache_dex", 0).getAbsolutePath();//不懂
                ClassLoader loader = getTargetContext().getClassLoader();
                DexClassLoader newLoader = new DexClassLoader(path, output, newLibDir, loader);
                SoLibraryPatcher.patchNativeLibraryDir(newLoader, mcLib);//重定向lib目录
                Class clazz = newLoader.loadClass(entry);
                Method method = clazz.getDeclaredMethod(fun, Context.class, String.class, String.class);
                method.invoke(null, getTargetContext(), path, mcLib);//调用
            }
        });
    }
}
