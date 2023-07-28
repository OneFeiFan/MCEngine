package com.taolesi.mcengine;

import android.webkit.JavascriptInterface;

public class NativeItem {
    @JavascriptInterface
    public static native void createItem(String name, String icon, int index, boolean addToCategory, int type);
    @JavascriptInterface
    public static native void createFood(String name, String icon, int index, boolean addToCategory, int type, String FoodData);
    @JavascriptInterface
    public static void createFoodItem(String name, String icon, int index, boolean addToCategory, int type, int use_duration, int nutrition) {
        createFood(name, icon, index, addToCategory, type, "{components: {minecraft:use_duration:" + use_duration + ",minecraft:food: {nutrition: " + nutrition + ",saturation_modifier: low}}}");
    }
}