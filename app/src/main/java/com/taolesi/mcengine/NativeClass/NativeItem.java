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

    public NativeItem() {
        define();
    }
    public NativeItem(long ItemPtr) {
        if (ItemPtr == 0) {
            Log.put("ItemPtr不存在");
        } else {
            ptr = ItemPtr;
        }
    }

    public static Map<JSObject, JSContext> getCallbacks() {
        return mCallbacks;
    }

    public static native void baseItemUseOn(long Item, long ItemStack, long Actor, int x, int y, int z, short d, float e, float f, float g);

    public static native long createItem(String name, String icon, int index, int type);//NC_ItemsPtr

    public static native long createFood(String name, String icon, int index, int type, String FoodData);//NC_ItemsPtr

    public static native long createSword(String name, String icon, int index, int type, String tier, int durability, int damage);//NC_ItemsPtr
    public static native short getId(String name);

    public static void onItemUse(long Item, long ItemStack, long Actor, int x, int y, int z, short d, float e, float f, float g) {
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
    }
}