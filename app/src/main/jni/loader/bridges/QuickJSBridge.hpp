//
// Created by 25843 on 2024/7/23.
//

#ifndef MCENGINE_QUICKJSBRIDGE_HPP
#define MCENGINE_QUICKJSBRIDGE_HPP

#include "ItemBridge.hpp"
#include "UsefulToolBridge.hpp"

extern "C" {
#include "../includes/tools/quickjs/quickjs-libc.h"

namespace QuickJSBridge
{
    static JSRuntime* globalRuntime;
    static JSContext* globalContext;

    static JSValue exception_val;
    static JSValue val;
    static bool is_error;
    static const char *stack;

    static JSContext* getContext() {
        return globalContext;
    }
    static JSRuntime* getRuntime() {
        return globalRuntime;
    }
    static JSValue GetException() {
        return exception_val;
    }
    static JSValue GetExceptionStack () {
        return val;
    }

    static void installization() {
        globalRuntime = JS_NewRuntime();
        js_std_init_handlers(globalRuntime);
        globalContext = JS_NewContext(globalRuntime);

        ItemBridge::installization(globalContext);
        UsefulToolBridge::installization(globalContext);

        js_std_add_helpers(globalContext, 0, nullptr);
        js_init_module_std(globalContext, "std");
        js_init_module_os(globalContext, "os");

    }
    static void eval(const char *input, size_t input_len, const char *filename) {
        JSValue main = JS_Eval(globalContext, input, input_len, filename, JS_EVAL_TYPE_MODULE | JS_EVAL_FLAG_COMPILE_ONLY);

        exception_val = JS_GetException(getContext());
        is_error = JS_IsError(globalContext, exception_val);
        if (!JS_IsException(main)) {
            js_module_set_import_meta(globalContext, main, FALSE, TRUE);
            main = JS_EvalFunction(globalContext, main);
        } else {
            val = JS_GetPropertyStr(globalContext, exception_val, "stack");
            stack = JS_ToCString(globalContext, val);
            printf("%s\n", stack);
            printf("%s\n", JS_ToCString(globalContext, exception_val));
            JS_FreeCString(globalContext, stack);
            JS_FreeValue(globalContext, val);
            JS_FreeValue(globalContext, exception_val);
            JS_FreeContext(globalContext);
            JS_FreeRuntime(globalRuntime);
        }
    }
    static void loadModules(const char *input, size_t input_len, const char *filename) {
        JSValue module = JS_Eval(globalContext, input, input_len, filename, JS_EVAL_TYPE_MODULE | JS_EVAL_FLAG_COMPILE_ONLY);

        exception_val = JS_GetException(getContext());
        if (!JS_IsException(module)) {
            js_module_set_import_meta(globalContext, module, FALSE, TRUE);
            module = JS_EvalFunction(globalContext, module);
        } else {
            val = JS_GetPropertyStr(globalContext, exception_val, "stack");
            stack = JS_ToCString(globalContext, val);
            printf("%s\n", stack);
            printf("%s\n", JS_ToCString(globalContext, exception_val));
            JS_FreeCString(globalContext, stack);
            JS_FreeValue(globalContext, val);
            JS_FreeValue(globalContext, exception_val);
            JS_FreeContext(globalContext);
            JS_FreeRuntime(globalRuntime);
        }
        module = js_std_await(globalContext, module);
    }

}

}

#endif //MCENGINE_QUICKJSBRIDGE_HPP
