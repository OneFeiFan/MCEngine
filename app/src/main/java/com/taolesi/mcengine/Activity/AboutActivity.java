package com.taolesi.mcengine.Activity;

import static com.taolesi.mcengine.R.layout;
import static com.taolesi.mcengine.UsefullTools.StatusBarUtils.setWindowStatusBarColor;

import android.os.Bundle;

import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.widget.Toolbar;

import com.taolesi.mcengine.R;
import com.taolesi.mcengine.UsefullTools.StatusBarUtils;

public class AboutActivity extends AppCompatActivity {
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(layout.activity_about);
        StatusBarUtils.setWindowStatusBarColor(this, R.color.blue_200);
        Toolbar toolbar = (Toolbar) findViewById(R.id.about_toolbar);


    }
}