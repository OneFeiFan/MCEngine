package com.taolesi.mcengine;

import static android.content.Intent.FLAG_GRANT_PERSISTABLE_URI_PERMISSION;
import static android.provider.Settings.ACTION_MANAGE_ALL_FILES_ACCESS_PERMISSION;

import static com.taolesi.mcengine.FileTools.UnZipAssetsFolder;
import static com.taolesi.mcengine.FileTools.changeToUri;
import static com.taolesi.mcengine.FileTools.copyDir;
import static com.taolesi.mcengine.FileTools.deleteDirectory;
import static com.taolesi.mcengine.FileTools.getDoucmentFile;
import static com.taolesi.mcengine.FileTools.getFileFromContentUri;
import static com.taolesi.mcengine.FileTools.removeDir;
import static com.taolesi.mcengine.FileTools.unzip;
import static com.taolesi.mcengine.FileTools.uriToFileApiQ;
import static com.taolesi.mcengine.QUESTCODE.OPENFILE;
import static com.taolesi.mcengine.QUESTCODE.REQUEST_CODE_FOR_DIR;
import static com.taolesi.mcengine.StatusBarUtils.setWindowStatusBarColor;

import android.Manifest;
import android.animation.Animator;
import android.annotation.SuppressLint;
import android.content.ActivityNotFoundException;
import android.content.Context;
import android.content.Intent;
import android.content.UriPermission;
import android.net.Uri;
import android.os.Build;
import android.os.Bundle;
import android.os.Environment;
import android.os.Handler;
import android.os.Message;
import android.provider.DocumentsContract;
import android.view.KeyEvent;
import android.view.Menu;
import android.view.MotionEvent;
import android.view.View;
import android.view.animation.Animation;
import android.widget.AbsListView;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;

import androidx.activity.result.ActivityResultCallback;
import androidx.activity.result.ActivityResultLauncher;
import androidx.activity.result.contract.ActivityResultContracts;
import androidx.annotation.NonNull;
import androidx.annotation.RequiresApi;
import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.widget.Toolbar;
import androidx.documentfile.provider.DocumentFile;
import androidx.recyclerview.widget.RecyclerView;

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
import java.util.Arrays;
import java.util.Collections;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.Objects;
import java.util.Timer;
import java.util.TimerTask;

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

    private ArrayList<String> modLists = new ArrayList<String>();

    public static native void copyToPatch(String input, String output);

    private static Context context;
    private String appCacheDir;
    private String appTempDir;

    private String appModsDir;

    private String appFilesDir;
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
    private FloatingActionButton openFileButton;
    private FloatingActionButton launchButton;
    private float x1 = 0.0F;
    private float y1 = 0.0F;

    @SuppressLint("ClickableViewAccessibility")
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContext(this);
        setContentView(R.layout.activity_main);
        setWindowStatusBarColor(this, R.color.purple_300);
        appCacheDir = getExternalCacheDir().getAbsolutePath();
        appTempDir = appCacheDir + "/temp/";
        appModsDir = Environment.getExternalStorageDirectory().getAbsolutePath() + "/games/MCEngine/mods/";
        appFilesDir = getExternalFilesDir("").toString()+"/";
        Log.init(Environment.getExternalStorageDirectory() + "/games/MCEngine","log.txt");

        launchButton = findViewById(R.id.floatingActionButton2);
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

        openFileButton = findViewById(R.id.floatingActionButton);
        Intent intent = new Intent(Intent.ACTION_GET_CONTENT);
        intent.setType("*/*");

        openFileButton.setOnClickListener(v -> {
            startActivityForResult(intent, OPENFILE.ordinal());
        });

        /*openFileButton.setOnLongClickListener(v -> {
            launchButton.hide();
            openFileButton.hide();
            return true;
        });*/
        String filesDirJson = appFilesDir + "mods.json";
        if (new File(filesDirJson).exists()){
            ObjectMapper objectMapper = new ObjectMapper();
            try {
                Map<String, Object> jsonMap = objectMapper.readValue(FileTools.readJsonFile(filesDirJson), new TypeReference<>() {});
                for (Map.Entry<String, Object> stringObjectEntry : jsonMap.entrySet()) {
                    if (!getModLists().contains(stringObjectEntry.getKey())) {
                        if (new File(appModsDir + stringObjectEntry.getKey()).exists() && new File(appFilesDir + stringObjectEntry.getKey()).exists()) {
                            getModLists().add(stringObjectEntry.getKey());
                        } else {
                            deleteDirectory(new File(appFilesDir + stringObjectEntry.getKey()));
                            deleteDirectory(new File(appModsDir + stringObjectEntry.getKey()));
                            removeFromJson(filesDirJson, stringObjectEntry.getKey());
                        }
                    }
                }
            } catch (IOException e) {
                Log.put(e.toString());
            }
        }

        ListView listView = (ListView) findViewById(R.id.modList);
        Collections.sort(getModLists());

        listView.setOnTouchListener((v, event) -> {

            if(event.getAction() == MotionEvent.ACTION_DOWN) {
                x1 = event.getX();
                y1 = event.getY();
            }
            if(event.getAction() == MotionEvent.ACTION_UP) {
                float x2 = event.getX();
                float y2 = event.getY();
                if(y1 - y2 > 50) {
                    launchButton.hide();
                    openFileButton.hide();
                } else if(y2 - y1 > 50) {
                    launchButton.show();
                    openFileButton.show();
                }
            }
            return false;
        });
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


        refreshAssets();
        refreshModList();
    }
    private void refreshMods() {
        try {
            for (String name : getModLists()) {
                if (!new File(appModsDir + name).exists() | !new File(appFilesDir + name).exists()) {
                    getModLists().remove(name);
                    Collections.sort(getModLists());
                    getModAdapter().notifyDataSetChanged();
                    try {
                        removeFromJson(appFilesDir + "mods.json", name);
                    } catch (IOException e) {
                        Log.put(e.toString());
                    }
                    deleteDirectory(new File(appFilesDir + name));
                    deleteDirectory(new File(appModsDir + name));
                }
            }
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
        File assets = new File(appFilesDir + "assets_modify");
        if (!assets.exists()) {
            try {
                UnZipAssetsFolder(getContext(), "app.zip", appFilesDir + "assets_modify");
            } catch (Exception e) {
                Log.put(e.toString());
            }
        }
    }

    private void refreshModList() {
        File modList = new File(appFilesDir + "mods.json");
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
        deleteDirectory(new File(appCacheDir));
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
            ObjectMapper objectMapper = new ObjectMapper();
            String name = "";
            String res = "";
            Uri file = data.getData();
            String path = getFileFromContentUri(getContext(), file);

            if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.Q) {
                path = uriToFileApiQ(this, file);
            }
            unzip(getContext(), path, appTempDir);
            Log.put(path + " 解压至 " + appTempDir);

            String modInfo = FileTools.readJsonFile(appTempDir + "modInfo.json");
            if (modInfo == null) {
                Toast.makeText(this, "加载失败，模组格式错误？", Toast.LENGTH_SHORT).show();
                refreshCacheDir();
                return;
            }
            refreshAssets();
            refreshModList();
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
            File modAssets = new File(appFilesDir + name);
            File tempModAssets = new File(appTempDir + res);
            if (!tempModAssets.exists()){//防止小可爱modInfo.json中的res写错，导致安装异常
                Toast.makeText(this, "加载失败，模组材质文件夹与配置不匹配", Toast.LENGTH_SHORT).show();
                refreshCacheDir();
                return;
            }
            removeDir(tempModAssets, modAssets);
            removeDir(new File(appTempDir), new File(appModsDir + name));
            Log.put(appModsDir + name + "构建完成");
            try {
                HashMap<String, String> json = new HashMap<>();
                Map<String, Object> jsonMap = objectMapper.readValue(FileTools.readJsonFile(appFilesDir + "mods.json"), new TypeReference<>() {
                });
                for (Map.Entry<String, Object> stringObjectEntry : jsonMap.entrySet()) {
                    json.put(stringObjectEntry.getKey(), stringObjectEntry.getValue().toString());
                }
                json.put(name, "enabled");
                if (!modLists.contains(name)) modLists.add(name);
                try {
                    objectMapper.enable(SerializationFeature.INDENT_OUTPUT);
                    objectMapper.writeValue(new File(appFilesDir + "mods.json"), json);
                } catch (IOException e) {
                    Log.put(e.toString());
                }
            } catch (JsonProcessingException e) {
                Log.put(e.toString());
            }
            Log.put("材质复制完成");
            Log.put("mod列表" + modLists.toString());
            refreshCacheDir();
            getModAdapter().notifyDataSetChanged();
        }
    }
}