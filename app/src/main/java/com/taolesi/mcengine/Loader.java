package com.taolesi.mcengine;

import static com.taolesi.mcengine.FileTools.JsonToObjTest;
import android.annotation.SuppressLint;
import android.content.Context;
import android.webkit.JavascriptInterface;
import android.widget.Toast;
import com.quickjs.JSContext;
import com.quickjs.QuickJS;
import com.quickjs.QuickJSScriptException;
import java.lang.reflect.InvocationTargetException;


public class Loader {
    public static Context context_;
    @SuppressLint("UnsafeDynamicallyLoadedCode")
    public static boolean init(Context context, String apkPath, String lib) throws NoSuchFieldException, ClassNotFoundException, InvocationTargetException, IllegalAccessException, NoSuchMethodException, InstantiationException {
        context_ = context;
        System.loadLibrary("dobby");
        System.loadLibrary("mcengine");
        System.loadLibrary("loader");
        //此处若是加载异常,将会停止向下运行,不用担心quickjs
        QuickJS quickJS = QuickJS.createRuntimeWithEventQueue();
        Loader loader = new Loader();
        loader.runCoreJS(context,quickJS);
        return true;
    }
    public void runCoreJS(Context context,QuickJS quickJS) {
        try {
            JSContext quickJS_context = quickJS.createContext();
            quickJS_context.addJavascriptInterface(new Loader(), "Loader");
            quickJS_context.addJavascriptInterface(new Examination(), "Examination");
            quickJS_context.addJavascriptInterface(new NativeItem(), "NativeItem");
            try {
                quickJS_context.executeScript(JsonToObjTest(context.getFilesDir()  + "/base/assets/main.js"), "main.js");
            } catch (QuickJSScriptException e) {
                throw new RuntimeException(e);
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
