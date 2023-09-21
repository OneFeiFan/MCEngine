package com.taolesi.mcengine.ModHelper;

import static com.taolesi.mcengine.UsefullTools.FileTools.JsonToObjTest;

import com.quickjs.JSArray;
import com.quickjs.JSContext;
import com.quickjs.JSFunction;
import com.quickjs.JSObject;
import com.quickjs.JavaCallback;
import com.quickjs.JavaVoidCallback;
import com.quickjs.QuickJS;
import com.taolesi.mcengine.NativeClass.NativeItem;
import com.taolesi.mcengine.UsefullTools.Examination;

public class QuickJSModRuntime {
    private QuickJS qjs;
    private JSContext context;



    private String mmodName;
    private String mmodPath;
    private String mmodInfoPath;
    private String mjavaScriptPath;

    public QuickJS getQuickJS() {
        return qjs;
    }
    public JSContext getJSContext() {
        return context;
    }
    public String getModName() {
        return mmodName;
    }
    public String getModPath() {
        return mmodPath;
    }
    public String getModInfoPath() {
        return mmodInfoPath;
    }
    public String getJavaScriptPath() {
        return mjavaScriptPath;
    }
    public QuickJSModRuntime (String modName, String modPath, String modInfoPath, String javaScriptPath) {
        mmodName = modName;
        mmodPath = modPath;
        mmodInfoPath = modInfoPath;
        mjavaScriptPath = javaScriptPath;
    }

    public void create() {
        qjs = QuickJS.createRuntimeWithEventQueue();
        context = qjs.createContext();
        addInterfaces();
        defineClass();
        runJS();
    }
    private void addInterfaces() {
        getJSContext().addJavascriptInterface(new Loader(), "Loader");
        getJSContext().addJavascriptInterface(new NativeItem(), "NativeItem");
        getJSContext().addJavascriptInterface(new Examination(), "Examination");

    }
    private void defineClass() {
        getJSContext().registerClass((thisObj, args) -> {
            JSObject item = (JSObject) args.get(0);
            NativeItem nativeItem = new NativeItem(item.getInteger("ItemPtr"));
            //thisObj.set("this", nativeItem);
            thisObj.set("name", item.getString("name"));
            thisObj.set("icon", item.getString("icon"));
            thisObj.set("index", item.getInteger("index"));
            thisObj.set("type", item.getInteger("type"));

            JSFunction OnItemUsed = new JSFunction(getJSContext(), (receiver, temp) -> {
                NativeItem.getCallbacks().put((JSFunction) temp.get(0), getJSContext());
            });
            thisObj.set("addOnItemUsedCallback", OnItemUsed);

        }, "Item");


    }
    private void runJS () {
        getJSContext().executeScript(JsonToObjTest(getJavaScriptPath()), getModName() + ".js");
        //getJSContext().close();
        //getQuickJS().close();
    }
}
