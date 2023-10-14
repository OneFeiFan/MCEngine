package com.taolesi.mcengine.ModHelper.ModClassDefine;

import com.quickjs.JSContext;

public class Actor extends Base {
    public Actor(JSContext context) {
        super(context);
    }
    public void start() {
        getContext().registerClass((thisObj, args) -> {
            com.taolesi.mcengine.mod.Actor actor = new com.taolesi.mcengine.mod.Actor(Long.parseLong(args.getString(0)));
            thisObj.registerJavaMethod((receiver, m) -> {
                return actor.isSneaking();
            }, "isSneaking");
        }, "Actor");
    }
}
