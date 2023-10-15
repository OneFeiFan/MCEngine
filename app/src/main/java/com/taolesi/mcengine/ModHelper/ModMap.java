package com.taolesi.mcengine.ModHelper;

import static com.taolesi.mcengine.UsefullTools.FileTools.copyFile;

import android.content.Context;
import android.os.Environment;

import java.io.File;

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
        copyFile(new File(getContext().getExternalFilesDir("")+"/assets_modify/IDMap.json"), new File(Environment.getExternalStorageDirectory() + "/games/MCEngine/IDMap.json"));
    }
}
