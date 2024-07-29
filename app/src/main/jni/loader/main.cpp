//#include "includes/NC_HookFR/NCHookFR.h"
#include <iostream>
#include <cstring>

#include <cstdio>
#include <string>
#include <iostream>
#include <jni.h>
#include <unistd.h>
#include <dlfcn.h>
#include <sstream>
#include "tester/android.hpp"
#include "tester/log.hpp"
#include "includes/dobby.h"
#include "includes/tools/lua/lua.hpp"
#include "includes/tools/quickjs/cutils.h"
#include "includes/HookFactory/HookFactory.hpp"
#include "includes/ItemFactory//ItemFactory.hpp"
#include "includes/ItemFactory/FoodItemFactory.hpp"
#include "includes/ItemFactory/SwordItemFactory.hpp"
#include "BlockFactory.hpp"
#include "IDPool.hpp"
#include "headers/feifan/ItemRegistryFaker.hpp"

#include "./bridges/ItemBridge.hpp"
#include "./bridges/UsefulToolBridge.hpp"
#include "./bridges/QuickJSBridge.hpp"

#define JniExport(type, Class, args...) JNIEXPORT type JNICALL Java_com_taolesi_mcengine_##Class(JNIEnv *env, jclass clazz, ##args)

std::vector<BlockFactory*> BlockFactory::blocksPoolArray;
std::vector<FoodItemFactory*> FoodItemFactory::foodItemsPoolArray;
std::vector<ItemFactory*> ItemFactory::normalItemsPoolArray;
std::map<const char *,Item::Tier*,cmp_str> SwordItemFactory::tiersPool;
std::vector<SwordItemFactory*> SwordItemFactory::swordItemsPoolArray;

extern "C" {
int add(lua_State *L)
{
    int a = lua_tointeger(L, 1);
    int b = lua_tointeger(L, 2);
    int result = a + b;
    lua_pushinteger(L, result);
    return 1;
}

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved)
{
    freopen("/storage/emulated/0/tmp/log1.txt", "w", stdout);
    android::setJavaVM(vm);
    JNIEnv *env = android::getJNIEnv();
//    const char *a = android::getExternalFilePath(android::getJNIEnv(), "", android::getApplicationContext(android::getJNIEnv()));
//    std::string b = std::string(a) + "/c01log.log";
//    Logger::instance = new Logger(b.c_str());
//
//    Logger::instance->log("log sys init success.");
//    void*ptr=dlopen("libminecraftpe.so", RTLD_LAZY);
//
//    Logger::instance->log("ptr = "+std::to_string(reinterpret_cast<uintptr_t>(ptr)));
//// 这边留一个log的使用例子
    void *mcHandleFake = DobbySymbolResolver("libminecraftpe.so", "_ZNK5Actor9getRegionEv");
    //android::showToast(env, android::charArrToJstring(env, std::to_string(reinterpret_cast<uintptr_t>(mcHandleFake)).c_str()));
    if(mcHandleFake){
//            lua_State *L = luaL_newstate();
//            luaL_openlibs(L);
//            lua_pushcfunction(L, add);
//            lua_setglobal(L, "add");
//
////            加载并执行
////            Lua 脚本文件
//            if(luaL_dofile(L, "/storage/emulated/0/tmp/script.lua") != LUA_OK){
//                printf("Failed to load and execute script.lua: %s\n", lua_tostring(L, -1));
//                lua_close(L);
//            }else {
//                printf("成功");
//            }
//            lua_close(L);
        android::showToast(env, android::charArrToJstring(env, "成功加载native核心"));
        HookFactory::jvm = vm;
        HookFactory::init();
        QuickJSBridge::installization();
        //}
    } else {
        android::showToast(env, android::charArrToJstring(env, "未能加载native核心"));
    }
    return JNI_VERSION_1_6;
}
JniExport(void, NativeClass_NativeBlock_createBlock, jstring jname, jstring jTextureName, jint jTextureData, jint jtype, jstring jMaterial)
{
    const char *name = android::jstringToCharArr(env, jname);
    const char *textureName = android::jstringToCharArr(env, jTextureName);
    const char *material = android::jstringToCharArr(env, jMaterial);
    BlockFactory::createObj(name, textureName, jTextureData, (CreativeItemCategory) jtype, material);
}
JniExport(jshort, NativeClass_IDPool_getId, jstring jname)
{
    return IDPool::getId(android::jstringToCharArr(env, jname));
}
JniExport(void, NativeClass_IDPool_setMap, jstring jname)
{
    IDPool::setMap(android::jstringToCharArr(env, jname));
}
}
extern "C" {
#include "includes/tools/quickjs/quickjs-libc.h"


JNIEXPORT void JNICALL
Java_com_taolesi_mcengine_Runtime_QuickJSModRuntime_runQuickjs(JNIEnv *env, jclass clazz, jstring js_filepath, jstring file_name)
{
    const char *js = android::jstringToCharArr(env, js_filepath);
    const char *file = android::jstringToCharArr(env, file_name);

    std::ifstream in(js);
    std::ostringstream sin;
    sin << in.rdbuf();
    std::string script_text = sin.str();

    QuickJSBridge::eval(script_text.c_str(), script_text.length(), file);

}

JNIEXPORT void JNICALL
Java_com_taolesi_mcengine_Runtime_QuickJSModRuntime_runQuickjsModule(JNIEnv *env, jclass clazz, jstring js_str, jstring file_name)
{
    const char *js = android::jstringToCharArr(env, js_str);
    const char *file = android::jstringToCharArr(env, file_name);

    QuickJSBridge::loadModules(js, strlen(js), std::string(std::string(file)+".js").c_str());
    js_module_loader(QuickJSBridge::globalContext, file, nullptr);
}

}