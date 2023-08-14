package com.taolesi.mcengine;

import static com.taolesi.mcengine.FileTools.JsonToObjTest;
import static com.taolesi.mcengine.FileTools.copyFile;

import android.content.Context;
import android.os.Environment;
import android.widget.Toast;

import com.fasterxml.jackson.core.JsonProcessingException;
import com.fasterxml.jackson.core.type.TypeReference;
import com.fasterxml.jackson.databind.ObjectMapper;
import com.quickjs.JSContext;
import com.quickjs.QuickJS;
import com.quickjs.QuickJSScriptException;

import java.io.File;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;

public class ModMap {
    private Context ctx;
    private String modListJson;
    public ModMap(Context context) {
        ctx = context;
    }
    private Context getContext() {
        return ctx;
    }
    public void run() {
        modListJson = getContext().getExternalFilesDir("") + "/mods.json";
        copyFile(new File(modListJson), new File(Environment.getExternalStorageDirectory() + "/games/MCEngine/mods.json"));
    }
}
