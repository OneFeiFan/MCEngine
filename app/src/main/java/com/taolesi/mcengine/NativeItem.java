package com.taolesi.mcengine;

import android.webkit.JavascriptInterface;

import com.quickjs.JSObject;

public class NativeItem {
    static String saturation = " ";
    @JavascriptInterface
    public static native void createItem(String name, String icon, int index, boolean addToCategory, int type);
    @JavascriptInterface
    public static native void createFood(String name, String icon, int index, boolean addToCategory, int type, String FoodData);
    @JavascriptInterface
    public static void createFoodItem(String name, String icon, int index, boolean addToCategory, int type, JSObject foodData) {
        switch (foodData.getInteger("saturationLevel")){
            case 1 : saturation = "poor";break;
            case 2 : saturation = "low";break;
            case 3 : saturation = "normal";break;
            case 4 : saturation = "good";break;
            case 5 : saturation = "max";break;
            case 6 : saturation = "supernatural";break;
            default: saturation = "normal";break;
        }
        createFood(name, icon, index, addToCategory, type, "{\"components\": {\"minecraft:use_duration\":" + (foodData.contains("useDuration") ? foodData.getString("use_duration"):"32") + ",\"minecraft:food\": {\"nutrition\": " + (foodData.contains("nutrition") ? foodData.getString("nutrition"):"2") + ",\"saturation_modifier\": \""+saturation+"\"}}}");
    }
}