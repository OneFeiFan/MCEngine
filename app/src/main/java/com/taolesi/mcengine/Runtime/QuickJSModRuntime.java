package com.taolesi.mcengine.Runtime;


import android.content.Context;
import android.content.res.AssetManager;
import android.widget.Toast;

import com.fasterxml.jackson.core.JsonProcessingException;
import com.taolesi.mcengine.Map.ModMap;
import com.taolesi.mcengine.UsefullTools.FileTools;
import com.taolesi.mcengine.UsefullTools.Log;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.lang.ref.WeakReference;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class QuickJSModRuntime {
    private String mmodName;
    private String mmodPath;
    private String mmodInfoPath;
    private String mjavaScriptPath;

    public String getModName() {
        return mmodName;
    }

    public String getModPath() {
        return mmodPath;
    }

    public String getModInfoPath() {
        return mmodInfoPath;
    }

    public String getJavaScriptPath() {
        return mjavaScriptPath;
    }

    public static Map<String, String> mModules = new HashMap<>();

    native static public void runQuickjs(String filePath, String fileName);
    native static public void runQuickjsModule(String jsString, String fileName);

    public void installization(String modName, String modPath, String modInfoPath, String javaScriptPath) {
        mmodName = modName;
        mmodPath = modPath;
        mmodInfoPath = modInfoPath;
        mjavaScriptPath = javaScriptPath;
        for (Map.Entry<String, String> stringObjectEntry : mModules.entrySet()) {
            runQuickjsModule(stringObjectEntry.getKey(), stringObjectEntry.getValue());
        }
        runJS();
    }
    public void runJS() {
        runQuickjs(getJavaScriptPath(), "main.js");
    }
}
