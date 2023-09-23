package com.taolesi.mcengine.NativeClass;

import android.webkit.JavascriptInterface;


public class NativeBlock {
    public static native void createBlock(String name, String textureName, int index, int category, String material);

//    @JavascriptInterface
//    public static void createBaseBlock(String name, String textureName, int index, int category, String rawMaterial) {
//        String material;
//        switch (rawMaterial) {
//            case "Wood":
//                material = "Wood";
//                break;
//            case "Dirt":
//                material = "Dirt";
//                break;
//            default:
//                material = "Stone";
//                break;
//        }
//        createBlock(name, textureName, index, category, material);
//    }

}
