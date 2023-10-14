package com.taolesi.mcengine.mod;

import com.taolesi.mcengine.UsefullTools.Log;

public class Block {
    public long ptr;
    public Block(long BlockPtr) {
        if (BlockPtr == 0) {
            Log.put("BlockPtr不存在");
        } else {
            ptr = BlockPtr;
        }
    }
}
