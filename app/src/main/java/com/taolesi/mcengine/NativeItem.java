package com.taolesi.mcengine;

import android.webkit.JavascriptInterface;

import com.quickjs.JSObject;

public class NativeItem {
    static String saturation = " ";
    public long ptr;
    public NativeItem(long NC_ItemsPtr) {
        ptr = NC_ItemsPtr;
    }
    public NativeItem() {

    }
    @JavascriptInterface
    public static native long createItem(String name, String icon, int index, boolean addToCategory, int type);//NC_ItemsPtr
    @JavascriptInterface
    public static native long createFood(String name, String icon, int index, boolean addToCategory, int type, String FoodData);//NC_ItemsPtr
    @JavascriptInterface
    public static long createFoodItem(String name, String icon, int index, boolean addToCategory, int type, JSObject foodData) {
        switch (foodData.getInteger("saturationLevel")){
            case 1 : saturation = "poor";break;
            case 2 : saturation = "low";break;
            case 4 : saturation = "good";break;
            case 5 : saturation = "max";break;
            case 6 : saturation = "supernatural";break;
            case 3 :
            default: saturation = "normal";break;
        }
        return createFood(name, icon, index, addToCategory, type, "{\"components\": {\"minecraft:use_duration\":" + (foodData.contains("useDuration") ? foodData.getString("use_duration"):"32") + ",\"minecraft:food\": {\"nutrition\": " + (foodData.contains("nutrition") ? foodData.getString("nutrition"):"2") + ",\"saturation_modifier\": \""+saturation+"\"}}}");
    }//NC_ItemsPtr
}