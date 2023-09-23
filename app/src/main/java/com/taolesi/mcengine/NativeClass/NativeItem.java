package com.taolesi.mcengine.NativeClass;

import android.webkit.JavascriptInterface;

import com.quickjs.JSArray;
import com.quickjs.JSContext;
import com.quickjs.JSFunction;
import com.quickjs.JSObject;
import com.quickjs.JSValue;
import com.taolesi.mcengine.ModHelper.Loader;
import com.taolesi.mcengine.UsefullTools.Log;

import java.util.HashMap;
import java.util.Map;

public class NativeItem {
    private long ptr;

    public static native void define();

    public static Map<JSObject, JSContext> mCallbacks = new HashMap<>();

//    public NativeItem(long NC_ItemsPtr) {
//        ptr = NC_ItemsPtr;
//        //define();
//    }

    public NativeItem() {
        define();
    }

    public static Map<JSObject, JSContext> getCallbacks() {
        return mCallbacks;
    }

    public static native void baseItemUseOn(long Item, long ItemStack, long Actor, int x, int y, int z, short d, float e, float f, float g);

    public static native long createItem(String name, String icon, int index, int type);//NC_ItemsPtr

    public static native long createFood(String name, String icon, int index, int type, String FoodData);//NC_ItemsPtr

    public static native long createSword(String name, String icon, int index, int type, String tier, int durability, int damage);//NC_ItemsPtr

//    public static void createBaseItem(String name, String icon, int index, int type) {
//        createItem(name, icon, index, type);
//    }
//    public static JSObject createBaseItem(JSObject itemData) {
//        long ptr = createItem(itemData.getString("name"), itemData.getString("icon"), itemData.getInteger("index"), itemData.getInteger("type"));
//        itemData.set("ItemPtr", ptr);
//        return itemData;
//    }


//    @JavascriptInterface
//    public static void createFoodItem(String name, String icon, int index, int type, JSObject foodData) {
//        String saturation = "normal";
//        try {//此处的try是为了防止foodData里面get不到键
//            switch (foodData.getInteger("saturationLevel")) {
//                case 1:
//                    saturation = "poor";
//                    break;
//                case 2:
//                    saturation = "low";
//                    break;
//                case 4:
//                    saturation = "good";
//                    break;
//                case 5:
//                    saturation = "max";
//                    break;
//                case 6:
//                    saturation = "supernatural";
//                    break;
//                default:
//                    saturation = "normal";
//                    break;
//            }
//        } catch (Exception e) {
//            Loader.Toast(String.valueOf(e));
//        }
//        createFood(name, icon, index, type, "{\"components\": {\"minecraft:food\": {\"nutrition\": " + (foodData.contains("nutrition") ? foodData.getString("nutrition") : "2") + ",\"saturation_modifier\": \"" + saturation + "\"}," + "\"minecraft:use_duration\":" + (foodData.contains("useDuration") ? foodData.getString("useDuration") : "32") + "}}");
//    }//NC_ItemsPtr

//    @JavascriptInterface
//    public static void createSwordItem(String name, String icon, int index, int type, JSObject extraData) {
//        String tier = "Wood";
//        try {
//            switch (extraData.getString("base")) {
//                case "Iron":
//                    tier = "Iron";
//                    break;
//                case "Stone":
//                    tier = "Stone";
//                    break;
//                case "Gold":
//                    tier = "Gold";
//                    break;
//                case "Diamond":
//                    tier = "Diamond";
//                    break;
//                case "Netherite":
//                    tier = "Netherite";
//                    break;
//                default:
//                    tier = "Wood";
//                    break;
//            }
//        } catch (Exception e) {
//            Loader.Toast(String.valueOf(e));
//        }
//
//        createSword(name, icon, index, type, tier, extraData.contains("durability") ? extraData.getInteger("durability") : 0, extraData.contains("damage") ? extraData.getInteger("damage") : 0);
//    }//NC_ItemsPtr

    @JavascriptInterface
    public static void onItemUse(long Item, long ItemStack, long Actor, int x, int y, int z, short d, float e, float f, float g) {
        boolean blacked = false;
        for (Map.Entry<JSObject, JSContext> entry : getCallbacks().entrySet()) {
            JSFunction function = (JSFunction) entry.getKey();
            JSContext context = entry.getValue();
            JSObject returned = new JSObject(context);
            try {
                function.call(JSValue.TYPE.JS_FUNCTION, returned, new JSArray(context).push(Item).push(ItemStack).push(Actor).push(x).push(y).push(z).push(d).push(e).push(f).push(g));
                Log.put("物品调用");

            } catch (Exception exception) {
                Log.put(exception.toString());
            }
        }
        baseItemUseOn(Item, ItemStack, Actor, x, y, z, d, e, f, g);
        //Log.put("物品调用");
    }
}