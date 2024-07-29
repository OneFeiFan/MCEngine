package com.taolesi.mcengine.LoadCore;

import android.annotation.SuppressLint;
import android.content.Context;
import android.os.Environment;
import android.webkit.JavascriptInterface;
import android.widget.Toast;

import com.fasterxml.jackson.core.JsonProcessingException;
import com.fasterxml.jackson.core.type.TypeReference;
import com.fasterxml.jackson.databind.ObjectMapper;
import com.taolesi.mcengine.Runtime.QuickJSModRuntime;
import com.taolesi.mcengine.UsefullTools.FileTools;
import com.taolesi.mcengine.UsefullTools.Log;

import java.lang.reflect.InvocationTargetException;
import java.util.Map;


public class Core {
    public static Context context_;
    @SuppressLint("UnsafeDynamicallyLoadedCode")
    public static boolean init(Context context, String apkPath, String lib) throws NoSuchFieldException, ClassNotFoundException, InvocationTargetException, IllegalAccessException, NoSuchMethodException, InstantiationException, JsonProcessingException {
        context_ = context;
        System.loadLibrary("dobby");
        //Toast("dobby 成功加载");
        System.loadLibrary("quickjs");
        //Toast("quickjs 成功加载");
        System.loadLibrary("loader");
        //Toast("core 成功加载");
        //此处若是加载异常,将会停止向下运行,不用担心quickjs
        Core core = new Core();
        core.runCoreJS(context);
        return true;
    }

    public void runCoreJS(Context context) throws JsonProcessingException {
        String modListJson = Environment.getExternalStorageDirectory() + "/games/MCEngine/mods.json";

        ObjectMapper objectMapper = new ObjectMapper();
        Log.init(Environment.getExternalStorageDirectory() + "/games/MCEngine","logJS.txt");
        Map<String, Object> jsonMap = objectMapper.readValue(FileTools.readJsonFile(modListJson), new TypeReference<>() {});
        Log.put(jsonMap.toString());
        for (Map.Entry<String, Object> stringObjectEntry : jsonMap.entrySet()) {
            if (stringObjectEntry.getValue().equals("enabled")) {
                String modName = stringObjectEntry.getKey();
                String modPath = Environment.getExternalStorageDirectory() + "/games/MCEngine/mods/" + modName;
                String modInfoPath = Environment.getExternalStorageDirectory() + "/games/MCEngine/mods/" + modName + "/modInfo.json";
                String javaScriptPath = Environment.getExternalStorageDirectory() + "/games/MCEngine/mods/" + modName + "/main.js";
                new QuickJSModRuntime().installization(modName, modPath, modInfoPath, javaScriptPath);
                Log.put(stringObjectEntry.getKey() + "模组加载");
            }
        }
    }
}
