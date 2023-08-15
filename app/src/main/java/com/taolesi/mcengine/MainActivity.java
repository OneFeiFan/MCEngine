package com.taolesi.mcengine;

import static android.provider.Settings.ACTION_MANAGE_ALL_FILES_ACCESS_PERMISSION;

import static com.taolesi.mcengine.FileTools.UnZipAssetsFolder;
import static com.taolesi.mcengine.FileTools.copyDir;
import static com.taolesi.mcengine.FileTools.deleteFie;
import static com.taolesi.mcengine.FileTools.getFileFromContentUri;
import static com.taolesi.mcengine.FileTools.unzip;
import static com.taolesi.mcengine.FileTools.uriToFileApiQ;
import static com.taolesi.mcengine.QUESTCODE.OPENFILE;

import android.Manifest;
import android.annotation.SuppressLint;
import android.content.ActivityNotFoundException;
import android.content.Context;
import android.content.Intent;
import android.net.Uri;
import android.os.Build;
import android.os.Bundle;
import android.os.Environment;
import android.os.Handler;
import android.os.Message;
import android.view.Menu;
import android.widget.ArrayAdapter;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;

import androidx.activity.result.contract.ActivityResultContracts;
import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.widget.Toolbar;

import com.fasterxml.jackson.core.JsonProcessingException;
import com.fasterxml.jackson.core.type.TypeReference;
import com.fasterxml.jackson.databind.ObjectMapper;
import com.fasterxml.jackson.databind.SerializationFeature;
import com.google.android.material.floatingactionbutton.FloatingActionButton;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;
import java.util.Timer;
import java.util.TimerTask;
import java.util.concurrent.Executors;
import java.util.concurrent.ScheduledExecutorService;
import java.util.concurrent.TimeUnit;

public class MainActivity extends AppCompatActivity {
    private final String[] PERMISSIONS = {
            Manifest.permission.WRITE_EXTERNAL_STORAGE,
            Manifest.permission.READ_EXTERNAL_STORAGE
    };
    private final String[] PERMISSIONS_30 = {
            Manifest.permission.READ_MEDIA_AUDIO,
            Manifest.permission.READ_MEDIA_IMAGES,
            Manifest.permission.READ_MEDIA_VIDEO,
            Manifest.permission.MANAGE_EXTERNAL_STORAGE
    };

    static {
        System.loadLibrary("mcengine");
    }

    private ArrayList<String> modLists = new ArrayList<>();

    public static native void copyToPatch(String input, String output);

    private static Context context;

    private static void setContext(Context context_) {
        context = context_;
    }

    private static Context getContext() {
        return context;
    }
    private ArrayList<String> getModLists() {
        return modLists;
    };
    private ModAdapter modAdapter;
    private void setModAdapter(ModAdapter adapter) {
        modAdapter = adapter;
    }
    private ModAdapter getModAdapter() {
        return modAdapter;
    }
    @SuppressLint("HandlerLeak")
    private Handler hander = new Handler(){
        @Override
        public void handleMessage(Message msg) {
            refreshMods();
        }
    };

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContext(this);
        setContentView(R.layout.activity_main);

        if (Build.VERSION.SDK_INT >= 30) {
            if (!Environment.isExternalStorageManager()) {
                Intent request = new Intent(ACTION_MANAGE_ALL_FILES_ACCESS_PERMISSION);
                startActivityForResult(request, 0);
            }
            registerForActivityResult(new ActivityResultContracts.RequestMultiplePermissions(), result -> {
            }).launch(PERMISSIONS_30);
        } else {
            registerForActivityResult(new ActivityResultContracts.RequestMultiplePermissions(), result -> {
            }).launch(PERMISSIONS);
        }
        Toolbar toolbar = (Toolbar) findViewById(R.id.toolbar);
        toolbar.setOnMenuItemClickListener(item -> {
            if (item.getItemId() == R.id.settings) {
                Intent settings = new Intent(MainActivity.this, SettingsActivity.class);
                startActivity(settings);
            } else if (item.getItemId() == R.id.about) {
                Intent about = new Intent(MainActivity.this, AboutActivity.class);
                startActivity(about);
            }
            return true;
        });

        Log.setDir(Environment.getExternalStorageDirectory() + "/games/MCEngine/log.txt");
        Log.clear();

        if (new File(getExternalFilesDir("") + "/mods.json").exists()){
            ObjectMapper objectMapper = new ObjectMapper();
            try {
                Map<String, Object> jsonMap = objectMapper.readValue(FileTools.readJsonFile(getExternalFilesDir("") + "/mods.json"), new TypeReference<>() {});
                for (Map.Entry<String, Object> stringObjectEntry : jsonMap.entrySet()) {
                    if (!getModLists().contains(stringObjectEntry.getKey())) {
                        if (new File(Environment.getExternalStorageDirectory() + "/games/MCEngine/mods/" + stringObjectEntry.getKey()).exists() && new File(getExternalFilesDir("") + "/" + stringObjectEntry.getKey()).exists()) {
                            getModLists().add(stringObjectEntry.getKey());
                        } else {
                            removeFromJson(getExternalFilesDir("") + "/mods.json", stringObjectEntry.getKey());
                            deleteFie(getExternalFilesDir("") + "/" + stringObjectEntry.getKey());
                            deleteFie(Environment.getExternalStorageDirectory() + "/games/MCEngine/mods/" + stringObjectEntry.getKey());
                        }
                    }
                }
            } catch (IOException e) {
                Log.put(e.toString());
            }
        }

        ListView listView = (ListView) findViewById(R.id.modList);
        setModAdapter(new ModAdapter(getContext(), getModLists()));
        try {
            listView.setAdapter(modAdapter);
        } catch (Exception e) {
            Log.put(e.toString());
        }
        TimerTask task = new TimerTask() {
            public void run() {
                hander.sendEmptyMessage(0);
            }
        };
        Timer timer = new Timer();
        long intevalPeriod = 1000;

        timer.scheduleAtFixedRate(task, 0, intevalPeriod);


        FloatingActionButton launchButton = findViewById(R.id.floatingActionButton2);
        launchButton.setOnClickListener(v -> {
            try {
                TextureMap textureMap = new TextureMap(getContext());
                textureMap.run();

                Intent intent = new Intent();
                intent.setClassName("com.mojang.minecraftpe", "com.mojang.minecraftpe.MainActivity");
                startActivity(intent);
            } catch (ActivityNotFoundException e) {
                Log.put(e.toString());
                Toast.makeText(MainActivity.this, "启动MC失败", Toast.LENGTH_SHORT).show();
            } catch (IOException e) {
                Log.put(e.toString());
            }
        });

        FloatingActionButton openFileButton = findViewById(R.id.floatingActionButton);
        Intent intent = new Intent(Intent.ACTION_GET_CONTENT);
        intent.setType("*/*");

        openFileButton.setOnClickListener(v -> {
            startActivityForResult(intent, OPENFILE.ordinal());
        });

        refreshAssets();
        refreshModList();
        refreshCacheDir();
        refreshTextView();
    }
    private void refreshMods() {
        try {
            for (String name : getModLists()) {
                if (!new File(Environment.getExternalStorageDirectory() + "/games/MCEngine/mods/" + name).exists() | !new File(getExternalFilesDir("") + "/" + name).exists()) {
                    getModLists().remove(name);
                    try {
                        removeFromJson(getExternalFilesDir("") + "/mods.json", name);
                    } catch (IOException e) {
                        Log.put(e.toString());
                    }
                    deleteFie(getExternalFilesDir("") + "/" + name);
                    deleteFie(Environment.getExternalStorageDirectory() + "/games/MCEngine/mods/" + name);
                }
            }
            getModAdapter().notifyDataSetChanged();
            refreshTextView();
        } catch (Exception e) {
            Log.put(e.toString());
        }
    }
    private void refreshTextView() {
        if (getModLists().size() != 0) {
            TextView textView = (TextView) findViewById(R.id.textView);
            textView.setText("");
        } else {
            TextView textView = (TextView) findViewById(R.id.textView);
            textView.setText("没有模组");
        }
    }
    private void removeFromJson(String path, String key) throws IOException {
        File jsonFile = new File(path);
        if (!jsonFile.exists()) {
            Log.put(path + "不存在");
        } else {
            HashMap<String, Object> temp = new HashMap<>();
            ObjectMapper objectMapper = new ObjectMapper();
            Map<String, Object> jsonMap = objectMapper.readValue(FileTools.readJsonFile(path), new TypeReference<>() {});
            for (Map.Entry<String, Object> stringObjectEntry : jsonMap.entrySet()) {
               if (!stringObjectEntry.getKey().equals(key)) temp.put(stringObjectEntry.getKey(), stringObjectEntry.getValue());
            }
            objectMapper.enable(SerializationFeature.INDENT_OUTPUT);
            objectMapper.writeValue(new File(path), temp);
        }
    }

    private void refreshAssets() {
        File assets = new File(getExternalFilesDir("") + "/assets_modify");
        if (!assets.exists()) {
            try {
                UnZipAssetsFolder(getContext(), "app.zip", getExternalFilesDir("") + "/assets_modify");
            } catch (Exception e) {
                Log.put(e.toString());
            }
        }
    }

    private void refreshModList() {
        File modList = new File(getExternalFilesDir("") + "/mods.json");
        if (!modList.exists()) {
            try (BufferedWriter writer = new BufferedWriter(new FileWriter(modList, true))) {
                writer.write("{}");
                writer.newLine();
            } catch (IOException e) {
                Log.put(e.toString());
            }
        }
    }
    private void refreshCacheDir() {
        deleteFie(getExternalCacheDir().getAbsolutePath());
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.menu_main, menu);
        return super.onCreateOptionsMenu(menu);
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        if (data == null) return;
        if (requestCode == OPENFILE.ordinal()) {
            refreshAssets();
            refreshModList();
            refreshCacheDir();
            Uri file = data.getData();
            String path = "";
            if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.Q) {
                try{
                    path = uriToFileApiQ(getContext(), file);
                } catch (Exception e) {
                    Log.put(e.toString());
                }
            } else {
                path = getFileFromContentUri(getContext(), file);
            }
            unzip(this, path, getExternalCacheDir() + "/temp");
            Log.put(path + " 解压至 " + getExternalCacheDir() + "/temp");
            ObjectMapper objectMapper = new ObjectMapper();
            String name = "";
            String res = "";
            String modInfo = FileTools.readJsonFile(getExternalCacheDir() + "/temp/modInfo.json");
            try {
                Map<String, Object> jsonMap = objectMapper.readValue(modInfo, new TypeReference<>() {
                });
                for (Map.Entry<String, Object> entry : jsonMap.entrySet()) {
                    switch (entry.getKey()) {
                        case "name":
                            name = entry.getValue().toString();
                            break;
                        case "res":
                            res = entry.getValue().toString();
                            break;
                    }
                }
                Log.put(name + " json读取成功");
            } catch (JsonProcessingException e) {
                Log.put(e.toString());
            }
            deleteFie(Environment.getExternalStorageDirectory() + "/games/MCEngine/mods/" + name);
            unzip(getContext(), path, Environment.getExternalStorageDirectory() + "/games/MCEngine/mods/" + name);
            Log.put(path + " 解压至 " + Environment.getExternalStorageDirectory() + "/games/MCEngine/mods/" + name);
            Log.put("解压完成");
            File modAssets = new File(getExternalFilesDir("") + "/" + name);
            deleteFie(getExternalFilesDir("") + "/" + name);
            copyDir(new File(Environment.getExternalStorageDirectory() + "/games/MCEngine/mods/" + name + "/" + res), modAssets);
            try {
                HashMap<String, String> json = new HashMap<>();
                Map<String, Object> jsonMap = objectMapper.readValue(FileTools.readJsonFile(getExternalFilesDir("") + "/mods.json"), new TypeReference<>() {});
                for (Map.Entry<String, Object> stringObjectEntry : jsonMap.entrySet()) {
                    json.put(stringObjectEntry.getKey(), stringObjectEntry.getValue().toString());
                }
                json.put(name, "enabled");
                if (!getModLists().contains(name)) getModLists().add(name);
                try {
                    objectMapper.enable(SerializationFeature.INDENT_OUTPUT);
                    objectMapper.writeValue(new File(getExternalFilesDir("") + "/mods.json"), json);
                } catch (IOException e) {
                    Log.put(e.toString());
                }
            } catch (JsonProcessingException e) {
                Log.put(e.toString());
            }
            Log.put("材质复制完成");
            Log.put("mod列表" + getModLists().toString());
            //getModAdapter().notifyDataSetChanged();
            refreshTextView();
        }
    }
}