package com.taolesi.mcengine.ModHelper;


import static com.taolesi.mcengine.UsefullTools.FileTools.JsonToObjTest;

import com.quickjs.JSContext;
import com.quickjs.JSObject;
import com.quickjs.QuickJS;
import com.taolesi.mcengine.ModHelper.ModClassDefine.Actor;
import com.taolesi.mcengine.ModHelper.ModClassDefine.CallbackRegistry;
import com.taolesi.mcengine.ModHelper.ModClassDefine.Item;
import com.taolesi.mcengine.ModHelper.ModClassDefine.ItemInstance;
import com.taolesi.mcengine.NativeClass.Callback.ItemCallback;
import com.taolesi.mcengine.ModHelper.ModClassDefine.BlockRegistry;
import com.taolesi.mcengine.ModHelper.ModClassDefine.ItemRegistry;
import com.taolesi.mcengine.NativeClass.NativeItem;
import com.taolesi.mcengine.UsefullTools.Examination;

public class QuickJSModRuntime {
    private QuickJS qjs;
    private JSContext context;


    private final String mmodName;
    private final String mmodPath;
    private final String mmodInfoPath;
    private final String mjavaScriptPath;

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

        ItemRegistry itemRegistry = new ItemRegistry(getJSContext());
        itemRegistry.pushItemFiles(Item);
        itemRegistry.start();

        BlockRegistry blockRegistry = new BlockRegistry(getJSContext());
        blockRegistry.pushBlockFiles(Block);
        blockRegistry.start();

        CallbackRegistry callbackRegistry = new CallbackRegistry(getJSContext());
        callbackRegistry.start();

        Item item = new Item(getJSContext());
        item.start();

        ItemInstance itemInstance = new ItemInstance(getJSContext());
        itemInstance.start();

        Actor actor = new Actor(getJSContext());
        actor.start();

        getJSContext().set("BlockID", Block);
        getJSContext().set("ItemID", Item);
        new NativeItem();//初始化给native提供信息
        new ItemCallback();
    }

    private void runJS() {
        getJSContext().executeScript(JsonToObjTest(getJavaScriptPath()), getModName() + ".js");
    }
}
