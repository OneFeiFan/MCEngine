package com.taolesi.mcengine.ModHelper;


import static com.taolesi.mcengine.UsefullTools.FileTools.JsonToObjTest;

import android.webkit.JavascriptInterface;

import com.quickjs.JSArray;
import com.quickjs.JSContext;
import com.quickjs.JSFunction;
import com.quickjs.JSObject;
import com.quickjs.JavaCallback;
import com.quickjs.JavaVoidCallback;
import com.quickjs.QuickJS;
import com.taolesi.mcengine.ModHelper.ModClassDefine.BlockRegistry;
import com.taolesi.mcengine.ModHelper.ModClassDefine.ItemRegistry;
import com.taolesi.mcengine.NativeClass.NativeBlock;
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

    public QuickJSModRuntime(String modName, String modPath, String modInfoPath, String javaScriptPath) {
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
        getJSContext().addJavascriptInterface(new Examination(), "Examination");

    }

    private void defineClass() {
        JSObject Item = new JSObject(getJSContext());
        JSObject Block = new JSObject(getJSContext());

        ItemRegistry itemRegistry = new ItemRegistry(new JSObject(getJSContext()));
        itemRegistry.pushItemFiles(Item);
        itemRegistry.start();

        BlockRegistry blockRegistry = new BlockRegistry(new JSObject(getJSContext()));
        blockRegistry.pushBlockFiles(Block);
        blockRegistry.start();

        getJSContext().set("Block", Block);
        getJSContext().set("Item", Item);
        new NativeItem();//初始化给native提供信息
    }

    private void runJS() {
        getJSContext().executeScript(JsonToObjTest(getJavaScriptPath()), getModName() + ".js");
    }
}
