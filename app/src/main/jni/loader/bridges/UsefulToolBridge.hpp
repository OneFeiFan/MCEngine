//
// Created by 25843 on 2024/7/21.
//

#ifndef MCENGINE_USEFULTOOLBRIDGE_HPP
#define MCENGINE_USEFULTOOLBRIDGE_HPP

#include "../tester/android.hpp"

extern "C" {
#include "../includes/tools/quickjs/quickjs-libc.h"

namespace UsefulToolBridge {
    static JSValue JS_alert(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
        const char *str;
        if(argc > 0){
            str = JS_ToCString(ctx, argv[0]);
            android::showToast(android::getJNIEnv(), android::charArrToJstring(android::getJNIEnv(), str));
            printf("%s\n", str);
        }
        JS_FreeCString(ctx, str);
        return JS_UNDEFINED;
    }

    static void installization(JSContext *context) {
        JSValue global_obj;
        global_obj = JS_GetGlobalObject(context);
        JSValue alert = JS_NewCFunction(context, JS_alert, "alert", 1);
        JS_SetPropertyStr(context, global_obj, "alert", alert);
    }
}

}
#endif //MCENGINE_USEFULTOOLBRIDGE_HPP
