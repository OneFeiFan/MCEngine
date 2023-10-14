package com.taolesi.mcengine.mod;

import com.taolesi.mcengine.UsefullTools.Log;

public class ItemInstance {
    public long ptr;
    public ItemInstance(long ItemInstancePtr) {
        if (ItemInstancePtr == 0) {
            Log.put("ItemInstancePtr不存在");
        } else {
            ptr = ItemInstancePtr;
        }
    }
    public static native long get(long ItemPtr);
}
