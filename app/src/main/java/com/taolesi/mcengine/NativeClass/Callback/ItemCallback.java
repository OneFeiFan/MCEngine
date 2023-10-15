package com.taolesi.mcengine.NativeClass.Callback;

import static com.taolesi.mcengine.NativeClass.NativeItem.baseItemUseOn;

import android.os.Environment;

import com.fasterxml.jackson.databind.ObjectMapper;
import com.quickjs.JSArray;
import com.quickjs.JSContext;
import com.quickjs.JSFunction;
import com.quickjs.JSObject;
import com.quickjs.JSValue;
import com.quickjs.JavaCallback;
import com.quickjs.JavaConstructorCallback;
import com.taolesi.mcengine.UsefullTools.Log;
import com.taolesi.mcengine.mod.Item;

import java.io.File;
import java.io.IOException;
import java.util.Arrays;
import java.util.HashMap;
import java.util.Map;

public class ItemCallback {
    public static native void define();
    public ItemCallback() {
        define();
    }
    public static Map<JSObject, JSContext> mOnItemUsedCallbacks = new HashMap<>();
    public static Map<JSObject, JSContext> getOnItemUsedCallbacks() {
        return mOnItemUsedCallbacks;
    }
    public static void onItemUse(long item, long ItemStack, long Actor, int x, int y, int z, short d, float e, float f, float g) throws IOException {
        for (Map.Entry<JSObject, JSContext> entry : getOnItemUsedCallbacks().entrySet()) {
            JSFunction function = (JSFunction) entry.getKey();
            JSContext context = entry.getValue();
            JSObject returned = new JSObject(context);

            try {
                function.call(JSValue.TYPE.JS_FUNCTION, returned, new JSArray(context).push(String.valueOf(item)).push(String.valueOf(ItemStack)).push(String.valueOf(Actor)).push(x).push(y).push(z).push(d).push(e).push(f).push(g));
                Log.put("物品调用");
            } catch (Exception exception) {
                Log.put(exception.toString());
            }
        }
        baseItemUseOn(item, ItemStack, Actor, x, y, z, d, e, f, g);
    }
}
