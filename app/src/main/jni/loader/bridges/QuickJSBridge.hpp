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
    static JSRuntime *globalRuntime = nullptr;
    static JSContext *globalContext = nullptr;

    static JSValue exception_val;
    static JSValue val;
    static const char *stack = nullptr;

    static JSContext *getContext()
    {
        return globalContext;
    }

    static JSRuntime *getRuntime()
    {
        return globalRuntime;
    }

    static JSValue GetException()
    {
        return exception_val;
    }

    static JSValue GetExceptionStack()
    {
        return val;
    }

    static JSContext *JS_NewCustomContext(JSRuntime *rt)
    {
        JSContext *ctx = JS_NewContextRaw(rt);
        if(!ctx)
            return nullptr;
        JS_AddIntrinsicBaseObjects(ctx);
        JS_AddIntrinsicDate(ctx);
        JS_AddIntrinsicEval(ctx);
        JS_AddIntrinsicStringNormalize(ctx);
        JS_AddIntrinsicRegExp(ctx);
        JS_AddIntrinsicJSON(ctx);
        JS_AddIntrinsicProxy(ctx);
        JS_AddIntrinsicMapSet(ctx);
        JS_AddIntrinsicTypedArrays(ctx);
        JS_AddIntrinsicPromise(ctx);
        JS_AddIntrinsicBigInt(ctx);

        js_init_module_os(ctx, "os");
        js_init_module_std(ctx, "std");
        return ctx;
    }

    static void installization()
    {
        globalRuntime = JS_NewRuntime();
        if(!globalRuntime){
            std::cerr << "Failed to create JSRuntime" << std::endl;
            return;
        }
        js_std_set_worker_new_context_func(JS_NewCustomContext);
        js_std_init_handlers(globalRuntime);
        JS_SetModuleLoaderFunc(globalRuntime, nullptr, js_module_loader, nullptr);
        globalContext = JS_NewCustomContext(globalRuntime);
        if(!globalContext){
            std::cerr << "Failed to create JSContext" << std::endl;
            JS_FreeRuntime(globalRuntime);
            return;
        }
        js_std_add_helpers(globalContext, 0, nullptr);
        const char *source = "import * as os from 'os';\n"
                             "for(let key in os){\n"
                             "globalThis[key] = os[key];"
                             "}\n";
        JSValue val1 = JS_Eval(globalContext, source, strlen(source), "<input>", JS_EVAL_TYPE_MODULE | JS_EVAL_FLAG_COMPILE_ONLY);
        if(!JS_IsException(val1)){
            js_module_set_import_meta(globalContext, val1, FALSE, TRUE);
            val1 = JS_EvalFunction(globalContext, val1);
            js_std_await(globalContext, val1);
        }
        JS_FreeValue(globalContext, val1);

        ItemBridge::installization(globalContext);
        UsefulToolBridge::installization(globalContext);
    }

    static int eval_buf(JSContext *ctx, const char *buf, int buf_len, const char *filename, int eval_flags)
    {
        JSValue val;
        int ret = 0;

        if((eval_flags & JS_EVAL_TYPE_MASK) == JS_EVAL_TYPE_MODULE){
            val = JS_Eval(ctx, buf, buf_len, filename, eval_flags | JS_EVAL_FLAG_COMPILE_ONLY);
            if(!JS_IsException(val)){
                js_module_set_import_meta(ctx, val, TRUE, TRUE);
                val = JS_EvalFunction(ctx, val);
                val = js_std_await(ctx, val);
            }
        }else {
            val = JS_Eval(ctx, buf, buf_len, filename, eval_flags);
        }

        if(JS_IsException(val)){
            val = JS_GetException(ctx);
            const char *str = JS_ToCString(ctx, val);
            if(str){
                std::cout << str << std::endl;
                JS_FreeCString(ctx, str);
            }else {
                std::cout << "未知异常" << std::endl;
            }

            if(JS_IsError(ctx, val)){
                val = JS_GetPropertyStr(ctx, val, "stack");
                if(!JS_IsUndefined(val)){
                    str = JS_ToCString(ctx, val);
                    if(str){
                        std::cout << str << std::endl;
                        JS_FreeCString(ctx, str);
                    }else {
                        std::cout << "未知异常" << std::endl;
                    }
                    JS_FreeValue(ctx, val);
                }
            }
            ret = -1;
        }

        JS_FreeValue(ctx, val);
        return ret;
    }

    static void eval(const char *input, size_t input_len, const char *filename)
    {
        int result = eval_buf(globalContext, input, input_len, filename, JS_EVAL_TYPE_MODULE);
        js_std_loop(globalContext);
        if(result != 0){
            JS_FreeContext(globalContext);
            JS_FreeRuntime(globalRuntime);
        }
    }

    static void loadModules(const char *input, size_t input_len, const char *filename)
    {
        JSValue module = JS_Eval(globalContext, input, input_len, filename, JS_EVAL_TYPE_MODULE | JS_EVAL_FLAG_COMPILE_ONLY);

        exception_val = JS_GetException(getContext());
        if(!JS_IsException(module)){
            js_module_set_import_meta(globalContext, module, FALSE, TRUE);
            module = JS_EvalFunction(globalContext, module);
            module = js_std_await(globalContext, module);
        }else {
            val = JS_GetPropertyStr(globalContext, exception_val, "stack");
            stack = JS_ToCString(globalContext, val);
            if(stack){
                std::cerr << stack << std::endl;
                JS_FreeCString(globalContext, stack);
            }
            const char *exceptionStr = JS_ToCString(globalContext, exception_val);
            if(exceptionStr){
                std::cerr << exceptionStr << std::endl;
                JS_FreeCString(globalContext, exceptionStr);
            }
            JS_FreeValue(globalContext, val);
            JS_FreeValue(globalContext, exception_val);
            JS_FreeContext(globalContext);
            JS_FreeRuntime(globalRuntime);
        }
    }
}
}
#endif //MCENGINE_QUICKJSBRIDGE_HPP
