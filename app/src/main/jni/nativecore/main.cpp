#include <iostream>
#include <jni.h>
#include <dlfcn.h>

static void *(*NC_DobbySymbolResolver)(const char *image_name, const char *symbol_name);

static int (*NC_DobbyHook)(void *, void *, void *);

extern "C" {
    [[maybe_unused]] void NativeCoreLoad(void **ptr) {
        freopen("/storage/emulated/0/tmp/loglog.txt", "w", stdout);
        void *handle = dlopen("libminecraftpe.so", RTLD_NOW | RTLD_NOLOAD); // RTLD_DEFAULT;
        if (ptr) {
            *ptr = handle;
        }
    }

    [[maybe_unused]] void setDobbySymbolResolver(void *symbol) {
        NC_DobbySymbolResolver = (void *(*)(const char *, const char *)) symbol;
    }

    [[maybe_unused]] void setDobbyHook(void *symbol) {
        NC_DobbyHook = (int (*)(void *, void *, void *)) symbol;
    }

    [[maybe_unused]] void InLineHook(void *hook, void *original, const char *symbol_name) {
        void *ptr = NC_DobbySymbolResolver("libminecraftpe.so", symbol_name);
        if (ptr != nullptr) {
            printf("成功获取符号：%s的地址\n", symbol_name);
            if (NC_DobbyHook(ptr, hook, original) == 0) {
                printf("hook成功\n");
            } else {
                printf("hook失败\n");
            }
        } else {
            printf("无法获取符号：%s的地址\n", symbol_name);
        }
    }

    [[maybe_unused]] void FakeNative(void **fake_fun, const char *symbol_name) {
        if (fake_fun) {
            void *symbol = NC_DobbySymbolResolver("libminecraftpe.so", symbol_name);
            if (symbol != nullptr) {
                printf("成功获取符号：%s的地址\n", symbol_name);
                *fake_fun = symbol;
                printf("fake成功\n");
            } else {
                printf("未能获取符号：%s的地址\n", symbol_name);
                printf("fake失败\n");
            }
        }
    }

}

//class [[maybe_unused]] IconData
//{
//private:
//    const char *name = " ";
//    int data = 0;
//
//public:
//    [[maybe_unused]] IconData(const char *name, int data);
//
//    [[maybe_unused]] const char *getName();
//
//    [[maybe_unused]] [[nodiscard]] int getData() const;
//};
//
//[[maybe_unused]] IconData::IconData(const char *name, int data) : name(name), data(data){}
//
//[[maybe_unused]] const char *IconData::getName()
//{
//    return this->name;
//}
//
//[[maybe_unused]] [[maybe_unused]] int IconData::getData() const
//{
//    return this->data;
//}



// void (*base_ItemStackBase)(void *, Item const &, int, int);
// void EX_ItemStackBase(void *ptr, Item const &obj, int a, int b)
// {
//     return base_ItemStackBase(ptr, obj, a, b);
// }
// class ResourceLocation
// {
// };
// void (*base_TextureUVCoordinateSet_TextureUVCoordinateSet)(void *, float, float, float, float, unsigned short, unsigned short, ResourceLocation, float, unsigned short);
// void EX_TextureUVCoordinateSet_TextureUVCoordinateSet(void *ptr, float a, float b, float c, float d, unsigned short e, unsigned short f, ResourceLocation g, float h, unsigned short i)
// {
//     base_TextureUVCoordinateSet_TextureUVCoordinateSet(ptr, a, b, c, d, e, f, g, h, i);
// }



//char *jstringToChar(JNIEnv *env, jstring jstr)
//{
//    char *rtn = nullptr;
//    jclass class_string = env->FindClass("java/lang/String");
//    jstring strencode = env->NewStringUTF("utf-8");
//    jmethodID mid = env->GetMethodID(class_string, "getBytes", "(Ljava/lang/String;)[B");
//    auto barr = (jbyteArray) env->CallObjectMethod(jstr, mid, strencode);
//    jsize alen = env->GetArrayLength(barr);
//    jbyte *ba = env->GetByteArrayElements(barr, JNI_FALSE);
//    if(alen > 0){
//        rtn = (char *) malloc(alen + 1);
//        memcpy(rtn, ba, alen);
//        rtn[alen] = 0;
//    }
//    env->ReleaseByteArrayElements(barr, ba, 0);
//    return rtn;
//}

//extern "C"
//JNIEXPORT void JNICALL
//Java_com_taolesi_mcengine_NativeItem_createItem(JNIEnv *env, jclass clazz, jstring name, jstring icon, jint index, jboolean add_to_category, jint type)
//{
//    try{
//        NC_Items *itemObj = new NC_Items(jstringToChar(env, name), jstringToChar(env, icon), index, add_to_category, (CreativeItemCategory) type);
//        itemsPoolArray.push_back(itemObj);
//
//    }catch(const std::exception &e){
//        std::cerr << e.what() << '\n';
//    }
//}