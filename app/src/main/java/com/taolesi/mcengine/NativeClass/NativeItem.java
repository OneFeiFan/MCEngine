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
    public NativeItem(long NC_ItemsPtr) {
        ptr = NC_ItemsPtr;
        //define();
    }

    public NativeItem() {
        define();
    }
    public static Map<JSObject, JSContext> getCallbacks() {
        return mCallbacks;
    }

    public static native void baseItemUseOn(long Item, long ItemStack, long Actor, int x, int y, int z, short d, float e, float f, float g);

    public static native long createItem(String name, String icon, int index, int type);//NC_ItemsPtr

    @JavascriptInterface
    public static JSObject createBaseItem(JSObject itemData) {
        long ptr = createItem(itemData.getString("name"), itemData.getString("icon"), itemData.getInteger("index"), itemData.getInteger("type"));
        itemData.set("ItemPtr", ptr);
        return itemData;
    }

    public static native long createFood(String name, String icon, int index, int type, String FoodData);//NC_ItemsPtr

    public static native long createSword(String name, String icon, int index, int type, int tier, int durability, int damage);//NC_ItemsPtr

    @JavascriptInterface
    public static long createFoodItem(String name, String icon, int index, int type, JSObject foodData) {
        String saturation = "normal";
        try {
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
        return createFood(name, icon, index, type, "{\"components\": {\"minecraft:food\": {\"nutrition\": " + (foodData.contains("nutrition") ? foodData.getString("nutrition") : "2") + ",\"saturation_modifier\": \"" + saturation + "\"}," + "\"minecraft:use_duration\":" + (foodData.contains("useDuration") ? foodData.getString("useDuration") : "32") + "}}");
    }//NC_ItemsPtr

    @JavascriptInterface
    public static long createSwordItem(String name, String icon, int index, int type, JSObject extraData) {
        int tier = 0;
        try {
            switch (extraData.getString("base")) {
                case "Iron":
                    tier = 1;
                    break;
                case "Stone":
                    tier = 2;
                    break;
                case "Gold":
                    tier = 3;
                    break;
                case "Diamond":
                    tier = 4;
                    break;
                case "Netherite":
                    tier = 5;
                    break;
                default:
                    tier = 0;
                    break;
            }
        } catch (Exception e) {
            Loader.Toast(String.valueOf(e));
        }

        return createSword(name, icon, index, type, tier, extraData.contains("durability") ? extraData.getInteger("durability") : 0, extraData.contains("damage") ? extraData.getInteger("damage") : 0);
    }//NC_ItemsPtr
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