package com.taolesi.mcengine.Map;

import static com.taolesi.mcengine.UsefullTools.FileTools.copyFile;

import android.content.Context;
import android.os.Environment;

import java.io.File;
import java.lang.ref.WeakReference;

public class ModMap extends BaseMap {
    private String modListJson;
    public void installization(Context context) {
        setContext(context);
        modListJson = getContext().getExternalFilesDir("") + "/mods.json";

        copyFile(new File(modListJson), new File(Environment.getExternalStorageDirectory() + "/games/MCEngine/mods.json"));
        copyFile(new File(getContext().getExternalFilesDir("")+"/assets_modify/IDMap.json"), new File(Environment.getExternalStorageDirectory() + "/games/MCEngine/IDMap.json"));
    }
    public  String getModListJson() {
        return modListJson;
    }
}
