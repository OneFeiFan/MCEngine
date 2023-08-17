package com.taolesi.mcengine;

import android.webkit.JavascriptInterface;

import com.quickjs.JSObject;

public class NativeItem {
    public long ptr;

    public NativeItem(long NC_ItemsPtr) {
        ptr = NC_ItemsPtr;
    }

    public NativeItem() {

    }

    @JavascriptInterface
    public static native long createItem(String name, String icon, int index,  int type);//NC_ItemsPtr

    public static native long createFood(String name, String icon, int index,  int type, String FoodData);//NC_ItemsPtr

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
}