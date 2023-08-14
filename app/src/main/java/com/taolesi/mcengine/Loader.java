package com.taolesi.mcengine;

import static com.taolesi.mcengine.FileTools.JsonToObjTest;

import android.annotation.SuppressLint;
import android.content.Context;
import android.content.res.AssetManager;
import android.os.Environment;
import android.webkit.JavascriptInterface;
import android.widget.Toast;

import com.fasterxml.jackson.core.JsonProcessingException;
import com.fasterxml.jackson.core.type.TypeReference;
import com.fasterxml.jackson.databind.ObjectMapper;
import com.quickjs.JSArray;
import com.quickjs.JSContext;
import com.quickjs.JSFunction;
import com.quickjs.JSObject;
import com.quickjs.JSValue;
import com.quickjs.JavaConstructorCallback;
import com.quickjs.JavaVoidCallback;
import com.quickjs.QuickJS;
import com.quickjs.QuickJSScriptException;

import java.io.IOException;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.List;
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
        QuickJS quickJS = QuickJS.createRuntimeWithEventQueue();
        Loader loader = new Loader();
        loader.runCoreJS(context, quickJS);
        return true;
    }

    public void runCoreJS(Context context, QuickJS quickJS) throws JsonProcessingException {
        JSContext quickJS_context = quickJS.createContext();
        quickJS_context.addJavascriptInterface(new Loader(), "Loader");
        quickJS_context.addJavascriptInterface(new NativeItem(), "NativeItem");
        quickJS_context.executeScript(JsonToObjTest(context.getFilesDir() + "/base/assets/main.js"), "main.js");
        quickJS_context.close();
        quickJS.close();

        String modListJson = Environment.getExternalStorageDirectory() + "/games/MCEngine/mods.json";
        ObjectMapper objectMapper = new ObjectMapper();
        Log.setDir(Environment.getExternalStorageDirectory() + "/games/MCEngine/log.txt");
        Log.clear();
        Map<String, Object> jsonMap = objectMapper.readValue(FileTools.readJsonFile(modListJson), new TypeReference<>() {
        });
        Log.put(jsonMap.toString());
        for (Map.Entry<String, Object> stringObjectEntry : jsonMap.entrySet()) {
            if (stringObjectEntry.getValue().equals("enabled")) {
                String modName = stringObjectEntry.getKey();
                String modPath = Environment.getExternalStorageDirectory() + "/games/MCEngine/mods/" + modName;
                String modInfoPath = Environment.getExternalStorageDirectory() + "/games/MCEngine/mods/" + modName + "/modInfo.json";
                String javaScriptPath = Environment.getExternalStorageDirectory() + "/games/MCEngine/mods/" + modName + "/main.js";
                QuickJS quickJS_ = QuickJS.createRuntimeWithEventQueue();
                JSContext quickJS_context_ = quickJS_.createContext();
                quickJS_context_.addJavascriptInterface(new Loader(), "Loader");
                quickJS_context_.addJavascriptInterface(new NativeItem(), "NativeItem");
                try {
                    quickJS_context_.executeScript(JsonToObjTest(javaScriptPath), modName + ".js");
                } catch (Exception e) {
                    Log.put(e.toString());
                }
                quickJS_context_.close();
                quickJS_.close();
                Log.put(stringObjectEntry.getKey() + "模组加载");
            }
        }
    }

    @JavascriptInterface
    public static void Toast(String str) {
        Toast.makeText(context_, str, Toast.LENGTH_SHORT).show();
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
