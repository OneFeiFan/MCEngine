package com.taolesi.mcengine.ModHelper;


import static com.taolesi.mcengine.UsefullTools.FileTools.JsonToObjTest;
import static com.taolesi.mcengine.UsefullTools.FileTools.copyDir;
import static com.taolesi.mcengine.UsefullTools.FileTools.deleteFile;

import android.os.Environment;

import com.fasterxml.jackson.core.JsonProcessingException;
import com.fasterxml.jackson.core.type.TypeReference;
import com.fasterxml.jackson.databind.ObjectMapper;
import com.fasterxml.jackson.databind.SerializationFeature;
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
import com.taolesi.mcengine.UsefullTools.FileTools;
import com.taolesi.mcengine.UsefullTools.Log;

import java.io.File;
import java.util.HashMap;
import java.util.Map;

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

    public void create() throws JsonProcessingException {
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

    private void defineClass() throws JsonProcessingException {
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

        JSObject IDpool = new JSObject(getJSContext());
        try {
            ObjectMapper objectMapper = new ObjectMapper();
            Map<String, Integer> json = objectMapper.readValue(FileTools.readJsonFile(Environment.getExternalStorageDirectory() + "/games/MCEngine/IDMap.json"), new TypeReference<>() {});
            for (Map.Entry<String, Integer> stringObjectEntry : json.entrySet()) {
                IDpool.set(stringObjectEntry.getKey(), stringObjectEntry.getValue());
                Log.put(stringObjectEntry.getKey());
            }
        } catch (Exception exception){
            Log.put(exception.toString());
        }
        getJSContext().set("VanillaID", IDpool);

        new NativeItem();//初始化给native提供信息
        new ItemCallback();
    }

    private void runJS() {
        getJSContext().executeScript(JsonToObjTest(getJavaScriptPath()), getModName() + ".js");
    }
}
