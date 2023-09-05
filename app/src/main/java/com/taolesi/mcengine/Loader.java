package com.taolesi.mcengine;

import static com.taolesi.mcengine.FileTools.JsonToObjTest;

import android.annotation.SuppressLint;
import android.content.Context;
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
import com.quickjs.JavaVoidCallback;
import com.quickjs.QuickJS;

import java.lang.reflect.InvocationTargetException;
import java.util.Map;
import java.util.concurrent.atomic.AtomicReference;


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
                quickJS_context_.addJavascriptInterface(new NativeItem(null), "NativeItem");
                quickJS_context_.registerClass((thisObj, args) -> {
                    JSObject item = (JSObject) args.get(0);
                    NativeItem nativeItem = new NativeItem(item.getInteger("ItemPtr"));
                    //thisObj.set("this", nativeItem);
                    thisObj.set("name", item.getString("name"));
                    thisObj.set("icon", item.getString("icon"));
                    thisObj.set("index", item.getInteger("index"));
                    thisObj.set("type", item.getInteger("type"));
                    //JSFunction callback = null;
                    //thisObj.set("onItemUse", "");
                    /*thisObj.registerJavaMethod((receiver, args1) -> {
                        JSFunction callback = ((JSFunction) args1.get(0));
                        nativeItem.addOnItemUseCallback(thisObj, callback);
                    }, "addOnItemUseCallback");*/

                    /*thisObj.registerJavaMethod((receiver, args1) -> {
                        //JSFunction callback = (JSFunction) args1.get(0);
                        Toast.makeText(context, "回调", Toast.LENGTH_SHORT).show();
                        //Log.put(receiver.toJSONObject().toString());
                        //nativeItem.addOnItemUseCallback(thisObj, callback);
                    }, "__OnItemUse");*/
                    //Toast.makeText(context, thisObj.toJSONObject().toString(), Toast.LENGTH_SHORT).show();
                    //quickJS_context_.addJavascriptInterface(new NativeItem(ptr), "Item");
                }, "Item");
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
