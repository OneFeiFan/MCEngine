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
    public Context ctx;
    public String modListJson;
    public String textureListPatch;
    public TextureMap(Context context) {
        ctx = context;
    }
    public Context getContext() {
        return ctx;
    }
    public void run() throws IOException {
        modListJson = getContext().getExternalFilesDir("") + "/mods.json";
        textureListPatch = getContext().getExternalFilesDir("").getAbsolutePath();
        ObjectMapper objectMapper = new ObjectMapper();
        Map<String, Object> jsonMap = objectMapper.readValue(FileTools.readJsonFile(modListJson), new TypeReference<>() {});
        for (Map.Entry<String, Object> stringObjectEntry : jsonMap.entrySet()) {
            if(stringObjectEntry.getValue().equals("enabled")) {
                //contents.json
                String patch = textureListPatch + "/" + stringObjectEntry.getKey();
                ArrayList<String> list = mapFiles(patch, patch);
                List<Object> obj = new ArrayList<>();
                Map<String, Object> contents = objectMapper.readValue(FileTools.readJsonFile(textureListPatch + "/assets_modify/assets/resource_packs/vanilla_1.14/contents.json"), new TypeReference<>() {});
                for (Map.Entry<String, Object> stringObjectEntry_contents : contents.entrySet()) {
                    obj.addAll((List<Object>) stringObjectEntry_contents.getValue());
                }
                for (String name : list) {
                    HashMap<String, String> littleMap = new HashMap<>();
                    littleMap.put("path", name);
                    obj.add(littleMap);
                }
                objectMapper.enable(SerializationFeature.INDENT_OUTPUT);
                new File(textureListPatch + "/assets").delete();
                copyDir(new File(textureListPatch + "/assets_modify/assets"), new File(textureListPatch + "/assets"));
                copyDir(new File(textureListPatch + "/" + stringObjectEntry.getKey() + "/textures"), new File(textureListPatch + "/assets/resource_packs/vanilla_1.14/textures"));
                new File(textureListPatch + "/assets/resource_packs/vanilla_1.14/contents.json").delete();
                objectMapper.writeValue(new File(textureListPatch + "/assets/resource_packs/vanilla_1.14/contents.json"), obj);

                //item_texture.json
                patch = textureListPatch + "/" + stringObjectEntry.getKey() + "/textures/" + stringObjectEntry.getKey() + "_items";
                list = mapItems(patch, textureListPatch + "/" + stringObjectEntry.getKey() + "/");

                HashMap<String, Object> items_json = new HashMap<>();
                Map<String, Object> items = objectMapper.readValue(FileTools.readJsonFile(textureListPatch + "/assets_modify/assets/resource_packs/vanilla_1.14/textures/item_texture.json"), new TypeReference<>() {});
                items_json.putAll(items);
                HashMap<String, Object> texture_data = (HashMap<String, Object>) items_json.get("texture_data");

                for (String name : list) {
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
                        if (texture_data.get(String.valueOf(fileName)) != null){
                            HashMap<String, ArrayList<String>> littleMap = (HashMap<String, ArrayList<String>>) texture_data.get(String.valueOf(fileName));
                            ArrayList<String> list1 = littleMap.get("textures");
                            list1.add(latter);
                            texture_data.put(String.valueOf(fileName), littleMap);
                        } else {
                            HashMap<String, ArrayList<String>> littleMap = new HashMap<>();
                            littleMap.put("textures", temp);
                            texture_data.put(String.valueOf(fileName), littleMap);
                        }
                    }
                }
                items_json.put("texture_data", texture_data);
                new File(textureListPatch + "/assets/resource_packs/vanilla_1.14/textures/item_texture.json").delete();
                objectMapper.writeValue(new File(textureListPatch + "/assets/resource_packs/vanilla_1.14/textures/item_texture.json"), items_json);

                //terrain_texture.json
                patch = textureListPatch + "/" + stringObjectEntry.getKey() + "/textures/" + stringObjectEntry.getKey() + "_blocks";
                list = mapItems(patch, textureListPatch + "/" + stringObjectEntry.getKey() + "/");

                items_json = new HashMap<>();
                items = objectMapper.readValue(FileTools.readJsonFile(textureListPatch + "/assets_modify/assets/resource_packs/vanilla_1.14/textures/terrain_texture.json"), new TypeReference<>() {});
                items_json.putAll(items);
                texture_data = (HashMap<String, Object>) items_json.get("texture_data");

                for (String name : list) {
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
                        if (texture_data.get(String.valueOf(fileName)) != null){
                            HashMap<String, ArrayList<String>> littleMap = (HashMap<String, ArrayList<String>>) texture_data.get(String.valueOf(fileName));
                            ArrayList<String> list1 = littleMap.get("textures");
                            list1.add(latter);
                            texture_data.put(String.valueOf(fileName), littleMap);
                        } else {
                            HashMap<String, ArrayList<String>> littleMap = new HashMap<>();
                            littleMap.put("textures", temp);
                            texture_data.put(String.valueOf(fileName), littleMap);
                        }
                    }
                }
                items_json.put("texture_data", texture_data);
                new File(textureListPatch + "/assets/resource_packs/vanilla_1.14/textures/terrain_texture.json").delete();
                objectMapper.writeValue(new File(textureListPatch + "/assets/resource_packs/vanilla_1.14/textures/terrain_texture.json"), items_json);
                toZip(textureListPatch + "/assets", new FileOutputStream(new File(Environment.getExternalStorageDirectory() + "/games/MCEngine/assets.zip")), true);
            }
        }
    }
    public ArrayList<String> mapFiles(String patch, String blackList) {
        File file = new File(patch);
        String[] studentFilesName = file.list();
        ArrayList<String> files = new ArrayList<>();
        for (String name : studentFilesName) {
            String newPatch = patch + "/" + name;
            File newFile = new File(newPatch);
            if (newFile.isDirectory()) {
                ArrayList<String> temp = mapFiles(newPatch, blackList);
                files.addAll(temp);
            } else {
                String formal = newFile.getAbsolutePath();
                String latter = formal.replace(blackList, "");
                if(latter.startsWith("/textures")) {
                    files.add(latter.replace("/textures", "textures"));
                }
            }
        }
        return files;
    }
    public ArrayList<String> mapItems(String patch, String blackList) {
        File file = new File(patch);
        String[] studentFilesName = file.list();
        ArrayList<String> files = new ArrayList<>();
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
        return files;
    }

}
