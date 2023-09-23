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
        //getJSContext().addJavascriptInterface(new NativeItem(), "NativeItem");
        //getJSContext().addJavascriptInterface(new NativeBlock(), "NativeBlock");
        getJSContext().addJavascriptInterface(new Examination(), "Examination");

    }

    private void defineClass() {
        JSObject ItemRegistry = new JSObject(getJSContext());
        JSObject Item = new JSObject(getJSContext());
        JSObject BlockRegistry = new JSObject(getJSContext());
        JSObject Block = new JSObject(getJSContext());
        ItemRegistry.registerJavaMethod((receiver, args) -> {
            String name = args.getString(0), iconName = args.getString(1);
            int index = args.getInteger(2), category = args.getInteger(3);
            NativeItem.createItem(name, iconName, index, category);
            Item.set(name, iconName);
        }, "createBaseItem");

        ItemRegistry.registerJavaMethod((receiver, args) -> {
            String name = args.getString(0), iconName = args.getString(1);
            int index = args.getInteger(2), category = args.getInteger(3);
            JSObject foodData = args.getObject(4);
            String saturation = "normal";
            try {//此处的try是为了防止foodData里面get不到键
                switch (foodData.getInteger("saturationLevel")) {
                    case 1:
                        saturation = "poor";
                        break;
                    case 2:
                        saturation = "low";
                        break;
                    case 4:
                        saturation = "good";
                        break;
                    case 5:
                        saturation = "max";
                        break;
                    case 6:
                        saturation = "supernatural";
                        break;
                    default:
                        saturation = "normal";
                        break;
                }
            } catch (Exception e) {
                Loader.Toast(String.valueOf(e));
            }
            NativeItem.createFood(name, iconName, index, category, "{\"components\": {\"minecraft:food\": {\"nutrition\": " + (foodData.contains("nutrition") ? foodData.getString("nutrition") : "2") + ",\"saturation_modifier\": \"" + saturation + "\"}," + "\"minecraft:use_duration\":" + (foodData.contains("useDuration") ? foodData.getString("useDuration") : "32") + "}}");
            Item.set(name, iconName);
        }, "createFoodItem");
        ItemRegistry.registerJavaMethod((receiver, args) -> {
            String name = args.getString(0), iconName = args.getString(1);
            int index = args.getInteger(2), category = args.getInteger(3);
            JSObject extraData = args.getObject(4);
            String tier = "Wood";
            try {
                switch (extraData.getString("base")) {
                    case "Iron":
                        tier = "Iron";
                        break;
                    case "Stone":
                        tier = "Stone";
                        break;
                    case "Gold":
                        tier = "Gold";
                        break;
                    case "Diamond":
                        tier = "Diamond";
                        break;
                    case "Netherite":
                        tier = "Netherite";
                        break;
                    default:
                        tier = "Wood";
                        break;
                }
            } catch (Exception e) {
                Loader.Toast(String.valueOf(e));
            }
            NativeItem.createSword(name, iconName, index, category, tier, extraData.contains("durability") ? extraData.getInteger("durability") : 0, extraData.contains("damage") ? extraData.getInteger("damage") : 0);
            Item.set(name, iconName);
        }, "createSwordItem");

        BlockRegistry.registerJavaMethod((receiver, args) -> {
            String name = args.getString(0), textureName = args.getString(1), rawMaterial = args.getString(4);
            int index = args.getInteger(2), category = args.getInteger(3);
            String material;
            switch (rawMaterial) {
                case "Wood":
                    material = "Wood";
                    break;
                case "Dirt":
                    material = "Dirt";
                    break;
                default:
                    material = "Stone";
                    break;
            }
            NativeBlock.createBlock(name, textureName, index, category, material);
            Block.set(name, textureName);
        }, "createBaseBlock");


        getJSContext().set("ItemRegistry", ItemRegistry);
        getJSContext().set("Item", Item);
        getJSContext().set("BlockRegistry", BlockRegistry);
        getJSContext().set("Block", Block);
        new NativeItem();//初始化给native提供信息
    }

    private void runJS() {
        getJSContext().executeScript(JsonToObjTest(getJavaScriptPath()), getModName() + ".js");
        //getJSContext().close();
        //getQuickJS().close();
    }
}
