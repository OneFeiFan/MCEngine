package com.taolesi.mcengine.ModHelper.ModClassDefine;

import com.quickjs.JSContext;
import com.quickjs.JSObject;

public class Base {
    private final JSObject mBase;
    private final JSContext mContext;

    public JSObject getJSObject() {
        return mBase;
    }

    public JSContext getContext() {
        return mContext;
    }

    public Base(JSContext context) {
        mBase = new JSObject(context);
        mContext = context;
    }
}
