package com.taolesi.mcengine.NativeClass;

import android.webkit.JavascriptInterface;


public class NativeBlock {
    public static native void createBlock(String name, String textureName, int index, int category, String material);

}
