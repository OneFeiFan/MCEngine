package com.taolesi.mcengine.ModHelper.ModClassDefine;

import com.quickjs.JSContext;
import com.quickjs.JSObject;
import com.taolesi.mcengine.NativeClass.NativeBlock;

public class BlockRegistry {
    public JSObject mBlockRegistry;
    public JSObject mBlock;
    public JSContext mContext;

    public JSObject getBlockRegistry() {
        return mBlockRegistry;
    }

    public JSContext getContext() {
        return mContext;
    }

    public BlockRegistry(JSObject itemRegistry) {
        mBlockRegistry = itemRegistry;
        mContext = itemRegistry.getContext();
    }

    public void pushBlockFiles(JSObject block) {
        mBlock = block;
    }

    public JSObject getBlock() {
        return mBlock;
    }
    public void start() {
        getBlockRegistry().registerJavaMethod((receiver, args) -> {
            String name = args.getString(0), textureName = args.getString(1), rawMaterial = args.getString(4);
            int index = args.getInteger(2), category = args.getInteger(3);
            String material;
            switch (rawMaterial) {
                case "Wood":
                    material = "Wood";
                    break;
                case "Dirt":
                    material = "Dirt";
                    break;
                default:
                    material = "Stone";
                    break;
            }
            NativeBlock.createBlock(name, textureName, index, category, material);
            getBlock().set(name, textureName);
        }, "createBaseBlock");
        getContext().set("BlockRegistry", getBlockRegistry());
    }
}
