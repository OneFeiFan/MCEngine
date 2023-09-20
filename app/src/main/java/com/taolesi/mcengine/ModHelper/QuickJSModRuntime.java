package com.taolesi.mcengine.ModHelper;

import static com.taolesi.mcengine.UsefullTools.FileTools.JsonToObjTest;

import com.quickjs.JSContext;
import com.quickjs.JSObject;
import com.quickjs.QuickJS;
import com.taolesi.mcengine.NativeClass.NativeItem;

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

    }
    private void runJS () {
        getJSContext().executeScript(JsonToObjTest(getJavaScriptPath()), getModName() + ".js");
        getJSContext().close();
        getQuickJS().close();
    }
}
