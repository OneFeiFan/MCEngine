package com.taolesi.mcengine;

import android.webkit.JavascriptInterface;

public class NativeItem {
    @JavascriptInterface
    public static native void createItem(String name, String icon, int index, boolean addToCategory, int type);
}
//new NC_Items("test", "apple", 0, true, CreativeItemCategory::Equipment);