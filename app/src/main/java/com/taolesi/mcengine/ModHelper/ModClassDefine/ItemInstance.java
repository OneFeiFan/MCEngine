package com.taolesi.mcengine.ModHelper.ModClassDefine;

import com.quickjs.JSContext;
import com.quickjs.JSFunction;
import com.quickjs.JSObject;
import com.taolesi.mcengine.NativeClass.Callback.ItemCallback;

public class ItemInstance extends Base {
    public ItemInstance(JSContext context) {
        super(context);
    }
    public void start(){
        getJSObject().registerJavaMethod((receiver, args) -> {
            long ItemPtr = Long.parseLong(args.getString(0));
            return com.taolesi.mcengine.mod.ItemInstance.get(ItemPtr);
        }, "get");
        getContext().set("ItemInstance", getJSObject());
    }
}
