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
    private long ptr;//NC_ItemsPtr

    public NativeItem() {
        define();
    }
    public static native void define();
    public static native void baseItemUseOn(long Item, long ItemStack, long Actor, int x, int y, int z, short d, float e, float f, float g);

    public static native long createItem(String name, String icon, int index, int type);//NC_ItemsPtr

    public static native long createFood(String name, String icon, int index, int type, String FoodData);//NC_ItemsPtr

    public static native long createSword(String name, String icon, int index, int type, String tier, int durability, int damage);//NC_ItemsPtr

}