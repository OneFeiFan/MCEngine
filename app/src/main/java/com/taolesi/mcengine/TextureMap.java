package com.taolesi.mcengine;

import static com.taolesi.mcengine.FileTools.copyDir;
import static com.taolesi.mcengine.FileTools.toZip;

import android.content.Context;
import android.os.Environment;
import android.os.Parcel;
import android.widget.Toast;

import com.fasterxml.jackson.core.JsonProcessingException;
import com.fasterxml.jackson.core.type.TypeReference;
import com.fasterxml.jackson.databind.ObjectMapper;
import com.fasterxml.jackson.databind.SerializationFeature;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class TextureMap {
    private Context ctx;
    private String modListJson;
    private String textureListPatch;
    private ObjectMapper objectMapper;

    private List<Object> contentsObj;

    private HashMap<String, Object> items_json = new HashMap<>();

    private HashMap<String, Object> block_json = new HashMap<>();

    public TextureMap(Context context) {
        ctx = context;
        objectMapper = new ObjectMapper();
        contentsObj = new ArrayList<>();
    }

    private Context getContext() {
        return ctx;
    }

    private void addData(Map.Entry<String, Object> stringObjectEntry, String type) throws IOException {
        HashMap<String, Object> temp1 = null;
        HashMap<String, Object> texture_data = new HashMap<>();
        switch (type) {
            case "items":
                texture_data = (HashMap<String, Object>) items_json.get("texture_data");
                temp1 = items_json;
                break;
            case "blocks":
                texture_data = (HashMap<String, Object>) block_json.get("texture_data");
                temp1 = block_json;
                break;
        }

        String patch = textureListPatch + "/" + stringObjectEntry.getKey() + "/textures/" + stringObjectEntry.getKey() + "_" + type;
        ArrayList<String> list = mapItems(patch, textureListPatch + "/" + stringObjectEntry.getKey() + "/");
        Log.put("TextureMap: mapItems 成功");

        for (String name : list) {
            HashMap<String, String> littleMap1 = new HashMap<>();
            littleMap1.put("path", name);
            contentsObj.add(littleMap1);
            String latter = name.replace(".png", "");
            String[] f = latter.split("/");
            StringBuilder fileName = new StringBuilder(f[f.length - 1]);
            f = fileName.toString().split("_");
            try {
                Integer.parseInt(f[f.length - 1]);
                fileName = new StringBuilder();
                for (int i = 0; i < f.length - 1; i++) {
                    fileName.append(f[i]);
                }
            } catch (NumberFormatException e) {

            }
            ArrayList<String> temp = new ArrayList<>();
            temp.add(latter);
            if (texture_data != null) {
                if (texture_data.get(String.valueOf(fileName)) != null) {
                    HashMap<String, ArrayList<String>> littleMap = (HashMap<String, ArrayList<String>>) texture_data.get(String.valueOf(fileName));
                    ArrayList<String> list1 = null;
                    if (littleMap != null) {
                        list1 = littleMap.get("textures");
                    }
                    if (list1 != null) {
                        list1.add(latter);
                    }
                    texture_data.put(String.valueOf(fileName), littleMap);
                } else {
                    HashMap<String, ArrayList<String>> littleMap = new HashMap<>();
                    littleMap.put("textures", temp);
                    texture_data.put(String.valueOf(fileName), littleMap);
                }
            }
        }
        temp1.put("texture_data", texture_data);
    }

    public void run() throws IOException {
        modListJson = getContext().getExternalFilesDir("") + "/mods.json";
        textureListPatch = getContext().getExternalFilesDir("").getAbsolutePath();

        Log.put("TextureMap: mods.json 读取成功");
        Map<String, Object> contents = objectMapper.readValue(FileTools.readJsonFile(textureListPatch + "/assets_modify/assets/resource_packs/vanilla_1.14/contents.json"), new TypeReference<>() {
        });
        Log.put("TextureMap: contents.json 读取成功");
        for (Map.Entry<String, Object> stringObjectEntry_contents : contents.entrySet()) {
            contentsObj.addAll((List<Object>) stringObjectEntry_contents.getValue());
        }
        Map<String, Object> items = objectMapper.readValue(FileTools.readJsonFile(textureListPatch + "/assets_modify/assets/resource_packs/vanilla_1.14/textures/item_texture.json"), new TypeReference<>() {
        });
        items_json.putAll(items);
        Log.put("TextureMap: item_texture.json 读取成功");
        Map<String, Object> blocks = objectMapper.readValue(FileTools.readJsonFile(textureListPatch + "/assets_modify/assets/resource_packs/vanilla_1.14/textures/terrain_texture.json"), new TypeReference<>() {
        });
        block_json.putAll(blocks);
        Log.put("TextureMap: terrain_texture.json 读取成功");
        Map<String, Object> jsonMap = objectMapper.readValue(FileTools.readJsonFile(modListJson), new TypeReference<>() {
        });
        for (Map.Entry<String, Object> stringObjectEntry : jsonMap.entrySet()) {
            if (stringObjectEntry.getValue().equals("enabled")) {
                //contents.json
                objectMapper.enable(SerializationFeature.INDENT_OUTPUT);
                new File(textureListPatch + "/assets").delete();
                Log.put("TextureMap: assets 删除成功");
                copyDir(new File(textureListPatch + "/assets_modify/assets"), new File(textureListPatch + "/assets"));
                copyDir(new File(textureListPatch + "/" + stringObjectEntry.getKey() + "/textures"), new File(textureListPatch + "/assets/resource_packs/vanilla_1.14/textures"));
                new File(textureListPatch + "/assets/resource_packs/vanilla_1.14/contents.json").delete();

                //item_texture.json
                addData(stringObjectEntry, "items");
                //terrain_texture.json
                addData(stringObjectEntry, "blocks");

                ModMap modMap = new ModMap(getContext());
                modMap.run();
            }
        }
        new File(textureListPatch + "/assets/resource_packs/vanilla_1.14/textures/item_texture.json").delete();
        objectMapper.writeValue(new File(textureListPatch + "/assets/resource_packs/vanilla_1.14/textures/item_texture.json"), items_json);

        new File(textureListPatch + "/assets/resource_packs/vanilla_1.14/textures/terrain_texture.json").delete();
        objectMapper.writeValue(new File(textureListPatch + "/assets/resource_packs/vanilla_1.14/textures/terrain_texture.json"), block_json);

        objectMapper.writeValue(new File(textureListPatch + "/assets/resource_packs/vanilla_1.14/contents.json"), contentsObj);
        Log.put("TextureMap: contents.json 写入成功");

        toZip(textureListPatch + "/assets", new FileOutputStream(new File(Environment.getExternalStorageDirectory() + "/games/MCEngine/assets.zip")), true);
    }

    public ArrayList<String> mapItems(String patch, String blackList) {
        File file = new File(patch);
        String[] studentFilesName = file.list();
        ArrayList<String> files = new ArrayList<>();
        if (studentFilesName != null) {
            for (String name : studentFilesName) {
                String newPatch = patch + "/" + name;
                File newFile = new File(newPatch);
                if (newFile.isDirectory()) {
                    ArrayList<String> temp = mapItems(newPatch, blackList);
                    files.addAll(temp);
                } else {
                    String formal = newFile.getAbsolutePath();
                    String latter = formal.replace(blackList, "");
                    files.add(latter);
                }
            }
        }
        return files;
    }

}
