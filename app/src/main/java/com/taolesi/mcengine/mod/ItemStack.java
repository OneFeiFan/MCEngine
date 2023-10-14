package com.taolesi.mcengine.mod;

import com.taolesi.mcengine.UsefullTools.Log;

public class ItemStack {
    public long ptr;
    public ItemStack(long ItemStackPtr) {
        if (ItemStackPtr == 0) {
            Log.put("ItemStackPtr不存在");
        } else {
            ptr = ItemStackPtr;
        }
    }
}
