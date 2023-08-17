package com.taolesi.mcengine;

import static com.taolesi.mcengine.FileTools.copyDir;
import static com.taolesi.mcengine.FileTools.deleteFile;
import static com.taolesi.mcengine.FileTools.toZip;

import android.content.Context;
import android.os.Environment;

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

@SuppressWarnings({"ResultOfMethodCallIgnored", "unchecked"})
public class TextureMap {
    private final Context ctx;

    private final ObjectMapper objectMapper;
    private String textureListPatch;
    private Map<String,List<Map<String,String>>> contentsObj;

    private Map<String, Object> items_json;

    private Map<String, Object> block_json;

    public TextureMap(Context context) {
        ctx = context;
        objectMapper = new ObjectMapper();
    }

    private Context getContext() {
        return ctx;
    }

    private void addData(Map.Entry<String, Object> stringObjectEntry, String type) {
        Map<String, Object> tempMap = null;
        HashMap<String, Object> texture_data = null;
        List<Map<String,String>> subContentList = contentsObj.get("content");
        switch (type) {
            case "items":
                texture_data = (HashMap<String, Object>) items_json.get("texture_data");
                tempMap = items_json;
                break;
            case "blocks":
                texture_data = (HashMap<String, Object>) block_json.get("texture_data");
                tempMap = block_json;
                break;
        }
        if (texture_data == null) {
            return;//防止日后手贱出错
        }
        String patch = textureListPatch + "/" + stringObjectEntry.getKey() + "/textures/" + stringObjectEntry.getKey() + "_" + type;
        ArrayList<String> list = mapItems(patch, textureListPatch + "/" + stringObjectEntry.getKey() + "/");
        Log.put("TextureMap: mapItems 成功");
        for (String name : list) {
            Map<String, String> subMap = new HashMap<>();
            subMap.put("path", name);
            if (subContentList != null) {
                subContentList.add(subMap);
            }
            String dir = name.replace(".png", "");
            String[] latter = dir.split("/");
            String fileName = latter[latter.length - 1];
            try {
                ArrayList<String> temp = new ArrayList<>(Arrays.asList(fileName.split("_")));
                Integer.parseInt(temp.get(temp.size() - 1));//如果图片文件名不是data值结尾的，那么报错跳出，继续使用普文件名作为key
                temp.remove(temp.size() - 1);//删除末尾的数字
                fileName = String.join("_", temp);//将其余间隔部分(如果有的话)使用_填充回去，形成一个不带data的文件名座位key
            } catch (NumberFormatException e) {
                e.printStackTrace();
            }
            ArrayList<String> temp = new ArrayList<>();
            temp.add(dir);

            HashMap<String, ArrayList<String>> littleMap;
            if ((littleMap = (HashMap<String, ArrayList<String>>) texture_data.get(fileName)) != null) {
                ArrayList<String> subTemp = littleMap.get("textures");
                temp = (subTemp == null ? new ArrayList<>() : subTemp);
                temp.add(dir);
            } else {
                littleMap = new HashMap<>();
            }
            littleMap.put("textures", temp);
            texture_data.put(fileName, littleMap);
        }
        tempMap.put("texture_data", texture_data);
    }

    public void run() throws IOException {
        String modListJson = getContext().getExternalFilesDir("") + "/mods.json";
        textureListPatch = getContext().getExternalFilesDir("").getAbsolutePath();

        Log.put("TextureMap: mods.json 读取成功");
        contentsObj = objectMapper.readValue(FileTools.readJsonFile(textureListPatch + "/assets_modify/assets/resource_packs/vanilla_1.14/contents.json"), new TypeReference<>() {
        });
        Log.put("TextureMap: contents.json 读取成功");

        items_json = objectMapper.readValue(FileTools.readJsonFile(textureListPatch + "/assets_modify/assets/resource_packs/vanilla_1.14/textures/item_texture.json"), new TypeReference<>() {
        });
        //items_json.putAll(items);
        Log.put("TextureMap: item_texture.json 读取成功");
        block_json = objectMapper.readValue(FileTools.readJsonFile(textureListPatch + "/assets_modify/assets/resource_packs/vanilla_1.14/textures/terrain_texture.json"), new TypeReference<>() {
        });
        //.putAll(blocks);
        Log.put("TextureMap: terrain_texture.json 读取成功");
        Map<String, Object> jsonMap = objectMapper.readValue(FileTools.readJsonFile(modListJson), new TypeReference<>() {
        });
        for (Map.Entry<String, Object> stringObjectEntry : jsonMap.entrySet()) {
            if (stringObjectEntry.getValue().equals("enabled")) {
                //contents.json
                objectMapper.enable(SerializationFeature.INDENT_OUTPUT);
                //new File(textureListPatch + "/assets").delete();
                deleteFile(textureListPatch + "/assets");
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

        toZip(textureListPatch + "/assets", new FileOutputStream(Environment.getExternalStorageDirectory() + "/games/MCEngine/assets.zip"), true);
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
