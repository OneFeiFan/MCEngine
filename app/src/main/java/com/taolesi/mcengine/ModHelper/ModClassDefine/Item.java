package com.taolesi.mcengine.ModHelper.ModClassDefine;

import com.quickjs.JSArray;
import com.quickjs.JSContext;
import com.quickjs.JSObject;
import com.quickjs.JavaCallback;
import com.quickjs.JavaConstructorCallback;
import com.taolesi.mcengine.UsefullTools.Log;

public class Item extends Base {
    public Item(JSContext context) {
        super(context);
    }
    public void start(){
        getContext().registerClass((thisObj, args) -> {
            com.taolesi.mcengine.mod.Item item = new com.taolesi.mcengine.mod.Item(Long.parseLong(args.getString(0)));
            thisObj.registerJavaMethod((receiver, m) -> {
                return item.getId();
            }, "getId");
            thisObj.registerJavaMethod((receiver, m) -> {
                return item.isSeed();
            }, "isSeed");
        }, "Item");
    }
}
