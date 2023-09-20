package com.taolesi.mcengine.ModHelper;

import android.annotation.SuppressLint;
import android.content.Context;
import android.os.Environment;
import android.webkit.JavascriptInterface;
import android.widget.Toast;

import com.fasterxml.jackson.core.JsonProcessingException;
import com.fasterxml.jackson.core.type.TypeReference;
import com.fasterxml.jackson.databind.ObjectMapper;
import com.taolesi.mcengine.UsefullTools.FileTools;
import com.taolesi.mcengine.UsefullTools.Log;

import java.lang.reflect.InvocationTargetException;
import java.util.Map;


public class Loader {
    public static Context context_;
    @SuppressLint("UnsafeDynamicallyLoadedCode")
    public static boolean init(Context context, String apkPath, String lib) throws NoSuchFieldException, ClassNotFoundException, InvocationTargetException, IllegalAccessException, NoSuchMethodException, InstantiationException, JsonProcessingException {
        context_ = context;
        System.loadLibrary("dobby");
        //System.loadLibrary("mcengine");
        System.loadLibrary("loader");
        //此处若是加载异常,将会停止向下运行,不用担心quickjs
        Loader loader = new Loader();
        loader.runCoreJS(context);
        return true;
    }

    public void runCoreJS(Context context) throws JsonProcessingException {
        String modListJson = Environment.getExternalStorageDirectory() + "/games/MCEngine/mods.json";
        ObjectMapper objectMapper = new ObjectMapper();
        Log.init(Environment.getExternalStorageDirectory() + "/games/MCEngine","logJS.txt");
        Map<String, Object> jsonMap = objectMapper.readValue(FileTools.readJsonFile(modListJson), new TypeReference<>() {});
        Log.put(jsonMap.toString());
        for (Map.Entry<String, Object> stringObjectEntry : jsonMap.entrySet()) {
            if (stringObjectEntry.getValue().equals("enabled")) {
                String modName = stringObjectEntry.getKey();
                String modPath = Environment.getExternalStorageDirectory() + "/games/MCEngine/mods/" + modName;
                String modInfoPath = Environment.getExternalStorageDirectory() + "/games/MCEngine/mods/" + modName + "/modInfo.json";
                String javaScriptPath = Environment.getExternalStorageDirectory() + "/games/MCEngine/mods/" + modName + "/main.js";
                try {
                    new QuickJSModRuntime(modName, modPath, modInfoPath, javaScriptPath).create();
                } catch (Exception e) {
                    Log.put(e.toString());
                }
                Log.put(stringObjectEntry.getKey() + "模组加载");
            }
        }
    }

    @JavascriptInterface
    public static void Toast(String str) {
        Toast.makeText(context_, str, Toast.LENGTH_SHORT).show();
    }
    @JavascriptInterface
    public static void log(String str) {
        Log.put(str);
    }
    /*@JavascriptInterface
    public static JSObject getNewLoader() {
        return (JSObject) new Loader();
    }*/

    public static void Log(String claz, int nummber) {

    }

    public static void Log(String claz, float nummber) {

    }

    public static void Log(String claz, String str) {

    }
}
