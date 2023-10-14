package com.taolesi.mcengine.mod;

import com.taolesi.mcengine.UsefullTools.Log;

public class Actor {
    public long ptr;
    public Actor(long ActorPtr) {
        if (ActorPtr == 0) {
            Log.put("ActorPtr不存在");
        } else {
            ptr = ActorPtr;
        }
    }
    public static native boolean isSneaking(long ActorPtr);
    public boolean isSneaking() {
        return isSneaking(ptr);
    }
}
