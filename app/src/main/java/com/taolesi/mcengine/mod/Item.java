package com.taolesi.mcengine.mod;

import com.taolesi.mcengine.UsefullTools.Log;

public class Item {
    public long ptr;//Item*
    public Item(long ItemPtr) {
        if (ItemPtr == 0) {
            Log.put("ItemPtr不存在");
        } else {
            ptr = ItemPtr;
        }
    }
    public static native short getId(long itemPtr);
    public static native boolean isSeed(long itemPtr);
    public int getId() {
        return getId(ptr);
    }
    public boolean isSeed(){
        return isSeed(ptr);
    }
}
