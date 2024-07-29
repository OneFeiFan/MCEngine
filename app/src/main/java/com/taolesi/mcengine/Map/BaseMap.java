package com.taolesi.mcengine.Map;

import android.content.Context;

import java.lang.ref.WeakReference;

public class BaseMap {
    protected static WeakReference<Context> ctx;
    public static Context getContext() {
        return ctx.get();
    }
    protected static void setContext(Context context) {
        ctx = new WeakReference<>(context);
    }
}
