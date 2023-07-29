package com.taolesi.mcengine;

import static android.provider.Settings.ACTION_MANAGE_ALL_FILES_ACCESS_PERMISSION;

import static com.taolesi.mcengine.FileTools.unzip;
import static com.taolesi.mcengine.QUESTCODE.OPENFILE;
import static com.taolesi.mcengine.QUESTCODE.REQUESTPERMISSIONMCDATA;

import android.Manifest;
import android.annotation.SuppressLint;
import android.content.ActivityNotFoundException;
import android.content.ContentResolver;
import android.content.Context;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.database.Cursor;
import android.net.Uri;
import android.os.Build;
import android.os.Bundle;
import android.os.Environment;
import android.os.FileUtils;
import android.provider.DocumentsContract;
import android.provider.MediaStore;
import android.provider.OpenableColumns;
import android.text.TextUtils;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.Toast;

import androidx.activity.result.ActivityResult;
import androidx.activity.result.ActivityResultCallback;
import androidx.activity.result.contract.ActivityResultContract;
import androidx.activity.result.contract.ActivityResultContracts;
import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.annotation.RequiresApi;
import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.widget.Toolbar;
import androidx.documentfile.provider.DocumentFile;

import com.fasterxml.jackson.core.JsonProcessingException;
import com.fasterxml.jackson.core.type.TypeReference;
import com.fasterxml.jackson.databind.ObjectMapper;
import com.google.android.material.floatingactionbutton.FloatingActionButton;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.net.URI;
import java.net.URISyntaxException;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.Map;
import java.util.Objects;

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
    public ArrayList<String> modLists = new ArrayList<String>();
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
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
        toolbar.setOnMenuItemClickListener(new Toolbar.OnMenuItemClickListener() {
            @Override
            public boolean onMenuItemClick(MenuItem item) {
                if (item.getItemId() == R.id.settings) {
                    Intent settings = new Intent(MainActivity.this, SettingsActivity.class);
                    startActivity(settings);
                } else if (item.getItemId() == R.id.about) {
                    Intent about = new Intent(MainActivity.this, AboutActivity.class);
                    startActivity(about);
                }
                return true;
            }
        });

        FloatingActionButton launchButton = (FloatingActionButton) findViewById(R.id.floatingActionButton2);
        launchButton.setOnClickListener(v -> {
            try {
                Intent intent = new Intent();
                intent.setClassName("com.mojang.minecraftpe", "com.mojang.minecraftpe.MainActivity");

                startActivity(intent);
            } catch (ActivityNotFoundException exception) {
                Toast.makeText(MainActivity.this, "启动MC失败", Toast.LENGTH_SHORT).show();
            }
        });

        FloatingActionButton openFileButton = (FloatingActionButton) findViewById(R.id.floatingActionButton);
        Intent intent = new Intent(Intent.ACTION_GET_CONTENT);
        intent.setType("*/*");

        openFileButton.setOnClickListener(v -> {
            startActivityForResult(intent, OPENFILE.ordinal());
        });
    }
    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.menu_main, menu);
        return super.onCreateOptionsMenu(menu);
    }
    @RequiresApi(api = Build.VERSION_CODES.Q)
    private String uriToFileApiQ(Context context, Uri uri) {
        File file = null;
        //android10以上转换
        if (uri.getScheme().equals(ContentResolver.SCHEME_FILE)) {
            file = new File(uri.getPath());
        } else if (uri.getScheme().equals(ContentResolver.SCHEME_CONTENT)) {
            //把文件复制到沙盒目录
            ContentResolver contentResolver = context.getContentResolver();
            Cursor cursor = contentResolver.query(uri, null, null, null, null);
            if (cursor.moveToFirst()) {
                @SuppressLint("Range")
                String displayName = cursor.getString(cursor.getColumnIndex(OpenableColumns.DISPLAY_NAME));
                //Toast.makeText(context, displayName, Toast.LENGTH_SHORT).show();
                try {
                    InputStream is = contentResolver.openInputStream(uri);
                    File cache = new File(context.getExternalCacheDir().getAbsolutePath(), /*Math.round((Math.random() + 1) * 1000) + */displayName);
                    FileOutputStream fos = new FileOutputStream(cache);
                    FileUtils.copy(is, fos);
                    file = cache;
                    fos.close();
                    is.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }
        return file.getAbsolutePath();
    }
    @SuppressLint("Range")
    public String getFileFromContentUri(Context context, Uri uri) {
        if (uri == null) {
            return null;
        }
        String filePath;
        String[] filePathColumn = {MediaStore.DownloadColumns.DATA, MediaStore.DownloadColumns.DISPLAY_NAME};
        ContentResolver contentResolver = context.getContentResolver();
        Cursor cursor = contentResolver.query(uri, filePathColumn, null,
                null, null);
        if (cursor != null) {
            cursor.moveToFirst();
            try {
                filePath = cursor.getString(cursor.getColumnIndex(filePathColumn[0]));
                return filePath;
            } catch (Exception e) {
            } finally {
                cursor.close();
            }
        }
        return "";
    }
    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        if (requestCode == OPENFILE.ordinal()) {
            Uri file = data.getData();
            String path;
            if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.Q) {
                path = uriToFileApiQ(this, file);
            } else {
                path = getFileFromContentUri(this, file);
            }

            File f = new File(path);
            String dataDir;
            dataDir = getApplicationInfo().dataDir;
            unzip(this, path, getExternalCacheDir() + "/temp");
            ObjectMapper objectMapper = new ObjectMapper();
            String name = "";
            String modInfo = FileTools.readJsonFile(getExternalCacheDir() + "/temp/modInfo.json");
            try {
                Map<String, Object> jsonMap = objectMapper.readValue(modInfo, new TypeReference<Map<String,Object>>(){});
                Iterator<Map.Entry<String, Object>> entries = jsonMap.entrySet().iterator();
                while (entries.hasNext()) {
                    Map.Entry<String, Object> entry = entries.next();
                    if(entry.getKey().equals("name")) {
                        name = entry.getValue().toString();
                    }
                }
            } catch (JsonProcessingException e) {
                throw new RuntimeException(e);
            }
            boolean out = true;
            if (out) {
                unzip(this, path, Environment.getExternalStorageDirectory() + "/tmp/mods/" + name);
            }else {
                unzip(this, path, getExternalCacheDir() + "/mods/" + name);
            }
            //Toast.makeText(this, modInfo, Toast.LENGTH_SHORT).show();
            //unzip(this, path, Environment.getExternalStorageDirectory() + "/tmp/mods/" + name);
            //File s = new File(getExternalCacheDir() + "/temp");
            //s.delete();
        }
        if (requestCode == REQUESTPERMISSIONMCDATA.ordinal()) {

        }
    }


}