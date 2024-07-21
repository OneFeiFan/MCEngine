package com.taolesi.mcengine.ModHelper;


import com.fasterxml.jackson.core.JsonProcessingException;
import com.taolesi.mcengine.UsefullTools.FileTools;

public class QuickJSModRuntime {
    private final String mmodName;
    private final String mmodPath;
    private final String mmodInfoPath;
    private final String mjavaScriptPath;

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

    native static public void runQuickjs(String jsString, String fileName);

    public QuickJSModRuntime(String modName, String modPath, String modInfoPath, String javaScriptPath) {
        mmodName = modName;
        mmodPath = modPath;
        mmodInfoPath = modInfoPath;
        mjavaScriptPath = javaScriptPath;
    }

    public void create() throws JsonProcessingException {
        //qjs = QuickJS.createRuntimeWithEventQueue();
        //context = qjs.createContext();
        addInterfaces();
        defineClass();
        runJS();
    }

    private void addInterfaces() {
        //getJSContext().addJavascriptInterface(new Loader(), "Loader");
        //getJSContext().addJavascriptInterface(new Examination(), "Examination");

    }

    private void defineClass() throws JsonProcessingException {

        /*JSObject IDpool = new JSObject(getJSContext());
        try {
            ObjectMapper objectMapper = new ObjectMapper();
            Map<String, Integer> json = objectMapper.readValue(FileTools.readJsonFile(Environment.getExternalStorageDirectory() + "/games/MCEngine/IDMap.json"), new TypeReference<>() {});
            for (Map.Entry<String, Integer> stringObjectEntry : json.entrySet()) {
                IDpool.set(stringObjectEntry.getKey(), stringObjectEntry.getValue());
                Log.put(stringObjectEntry.getKey());
            }
        } catch (Exception exception){
            Log.put(exception.toString());
        }
        getJSContext().set("VanillaID", IDpool);
        */
        //new NativeItem();//初始化给native提供信息
        //new ItemCallback();
    }

    private void runJS() {
        //Loader.Toast(FileTools.JsonToObjTest(getJavaScriptPath()));
        runQuickjs(FileTools.JsonToObjTest(getJavaScriptPath()), getModName() + ".js");
    }
}
