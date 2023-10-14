package com.taolesi.mcengine.ModHelper.ModClassDefine;

import com.quickjs.JSContext;
import com.quickjs.JSObject;
import com.taolesi.mcengine.ModHelper.Loader;
import com.taolesi.mcengine.NativeClass.IDPool;
import com.taolesi.mcengine.NativeClass.NativeItem;

public class ItemRegistry extends Base {
    public JSObject mItem;

    public ItemRegistry(JSContext context) {
        super(context);
    }

    public void pushItemFiles(JSObject item) {
        mItem = item;
    }

    public JSObject getItem() {
        return mItem;
    }

    public void start() {
        getJSObject().registerJavaMethod((receiver, args) -> {
            String name = args.getString(0), iconName = args.getString(1);
            int index = args.getInteger(2), category = args.getInteger(3);
            long ptr = NativeItem.createItem(name, iconName, index, category);
            getItem().set(name, IDPool.getId(name));
        }, "createBaseItem");

        getJSObject().registerJavaMethod((receiver, args) -> {
            String name = args.getString(0), iconName = args.getString(1);
            int index = args.getInteger(2), category = args.getInteger(3);
            JSObject foodData = args.getObject(4);
            String saturation = "normal";
            try {//此处的try是为了防止foodData里面get不到键
                switch (foodData.getInteger("saturationLevel")) {
                    case 1:
                        saturation = "poor";
                        break;
                    case 2:
                        saturation = "low";
                        break;
                    case 4:
                        saturation = "good";
                        break;
                    case 5:
                        saturation = "max";
                        break;
                    case 6:
                        saturation = "supernatural";
                        break;
                    default:
                        saturation = "normal";
                        break;
                }
            } catch (Exception e) {
                Loader.Toast(String.valueOf(e));
            }
            long ptr = NativeItem.createFood(name, iconName, index, category, "{\"components\": {\"minecraft:food\": {\"nutrition\": " + (foodData.contains("nutrition") ? foodData.getString("nutrition") : "2") + ",\"saturation_modifier\": \"" + saturation + "\"}," + "\"minecraft:use_duration\":" + (foodData.contains("useDuration") ? foodData.getString("useDuration") : "32") + "}}");
            getItem().set(name, IDPool.getId(name));
        }, "createFoodItem");
        getJSObject().registerJavaMethod((receiver, args) -> {
            String name = args.getString(0), iconName = args.getString(1);
            int index = args.getInteger(2), category = args.getInteger(3);
            JSObject extraData = args.getObject(4);
            String tier = "Wood";
            try {
                switch (extraData.getString("base")) {
                    case "Iron":
                        tier = "Iron";
                        break;
                    case "Stone":
                        tier = "Stone";
                        break;
                    case "Gold":
                        tier = "Gold";
                        break;
                    case "Diamond":
                        tier = "Diamond";
                        break;
                    case "Netherite":
                        tier = "Netherite";
                        break;
                    default:
                        tier = "Wood";
                        break;
                }
            } catch (Exception e) {
                Loader.Toast(String.valueOf(e));
            }
            long ptr = NativeItem.createSword(name, iconName, index, category, tier, extraData.contains("durability") ? extraData.getInteger("durability") : 0, extraData.contains("damage") ? extraData.getInteger("damage") : 0);
            getItem().set(name, IDPool.getId(name));
        }, "createSwordItem");
        getContext().set("ItemRegistry", getJSObject());
    }
}
