package com.taolesi.mcengine.ModHelper.ModClassDefine;

import com.quickjs.JSContext;
import com.quickjs.JSFunction;
import com.taolesi.mcengine.NativeClass.Callback.ItemCallback;

public class CallbackRegistry extends Base {
    public CallbackRegistry(JSContext context) {
        super(context);
    }
    public void start() {
        getJSObject().registerJavaMethod((receiver, args) -> {
            JSFunction func = (JSFunction) args.get(0);
            ItemCallback.getOnItemUsedCallbacks().put(func, getContext());
        }, "addOnItemUsedCallback");
        getContext().set("CallbackRegistry", getJSObject());
    }
}
