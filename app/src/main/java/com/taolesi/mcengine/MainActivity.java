package com.taolesi.mcengine;

import android.Manifest;
import android.content.ActivityNotFoundException;
import android.content.Context;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.os.Build;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Toast;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.widget.Toolbar;

import com.google.android.material.floatingactionbutton.FloatingActionButton;

import java.util.ArrayList;

public class MainActivity extends AppCompatActivity {
    private final String[] PERMISSIONS = {
            Manifest.permission.WRITE_EXTERNAL_STORAGE,
            Manifest.permission.READ_EXTERNAL_STORAGE
    };
    private final String[] PERMISSIONS_33 = {
            Manifest.permission.WRITE_EXTERNAL_STORAGE,
            Manifest.permission.READ_EXTERNAL_STORAGE,
            Manifest.permission.MANAGE_EXTERNAL_STORAGE
    };
    public ArrayList<String> modLists = new ArrayList<String>();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        //requestPermissions(PERMISSIONS, 99);
        setContentView(R.layout.activity_main);
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.R) {
            requestPermissions(PERMISSIONS_33, 20);
        } else {
            requestPermissions(PERMISSIONS, 20);
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
                Toast.makeText(MainActivity.this, "启动MC失败", Toast.LENGTH_SHORT);
            }
        });

        /*if (modLists.length == 0) {

        }*/
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.menu_main, menu);
        return super.onCreateOptionsMenu(menu);
    }

}