package com.taolesi.mcengine.Map;

import static com.taolesi.mcengine.UsefullTools.FileTools.copyFile;

import android.content.Context;
import android.os.Environment;

import java.io.File;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class ModuleMap extends BaseMap {
    private List<String> modules = new ArrayList<>();
    public void installization(Context context) {
        setContext(context);
    }

    public List<String> getModules() {
        return modules;
    }
    public void addModule(String path) {
        modules.add(path);
    }
}
