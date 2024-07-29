//
// Created by 25843 on 2024/7/21.
//

#ifndef MCENGINE_ITEMBRIDGE_HPP
#define MCENGINE_ITEMBRIDGE_HPP
#include <vector>

extern "C" {
#include "../includes/tools/quickjs/quickjs-libc.h"


namespace ItemBridge {
    namespace Callback {
        enum {
            onItemUse = 0
        };
        /*static JSValue JS_onItemUse(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
            Item *ptr;
            ItemStack *itemstack;
            Actor *actor;
            int x;
            int y;
            int z;
            short face;
            float vecX;
            float vecY;
            float vecZ;

            if(argc > 10) {
                name = JS_ToCString(ctx, argv[0]);
                iconName = JS_ToCString(ctx, argv[1]);
                JS_ToInt32(ctx, &index, argv[2]);
                JS_ToInt32(ctx, &type, argv[3]);

            }

            return JS_UNDEFINED;
        }*/
        static JSValue JS_addCallback(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
            JSValue callbackFunction;
            if(argc > 0) {
                callbackFunction = argv[0];
            }

            return JS_UNDEFINED;
        }
    }
    static JSValue JS_createItem(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
        const char *name;
        const char *iconName;
        int index;
        int type;
        if(argc > 3) {
            name = JS_ToCString(ctx, argv[0]);
            iconName = JS_ToCString(ctx, argv[1]);
            JS_ToInt32(ctx, &index, argv[2]);
            JS_ToInt32(ctx, &type, argv[3]);
            ItemFactory::createObj(name, iconName, index, (CreativeItemCategory) type);
        }

        JS_FreeCString(ctx, name);
        JS_FreeCString(ctx, iconName);

        return JS_UNDEFINED;
    }
    static void installization(JSContext *context) {
        JSValue global_obj;
        global_obj = JS_GetGlobalObject(context);
        /*
        global_obj = JS_GetGlobalObject(ctx);
        console = JS_NewObject(ctx);
        JS_SetPropertyStr(ctx, console, "log", JS_NewCFunction(ctx, js_print, "log", 1));
        JS_SetPropertyStr(ctx, global_obj, "console", console);
        */
        IDPool::define(*fake_ItemRegistry_mMaxItemID);

        JSValue Item = JS_NewObject(context);
        JSValue createItem = JS_NewCFunction(context, JS_createItem, "createItem", 4);
        JS_SetPropertyStr(context, Item, "createItem", createItem);
        JS_SetPropertyStr(context, global_obj, "Item", Item);
    }
}

}
#endif //MCENGINE_ITEMBRIDGE_HPP
