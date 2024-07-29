package com.taolesi.mcengine.Adapter;

import android.app.Activity;
import android.content.Context;
import android.net.Uri;
import android.os.Environment;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.ImageView;
import android.widget.TextView;


import com.taolesi.mcengine.R;

import java.io.File;
import java.util.ArrayList;

public class ModAdapter extends BaseAdapter {
    private Context context;
    private ArrayList<String> mods;

    public ModAdapter(Context ctx, ArrayList<String> list) {
        context = ctx;
        mods = list;
    }

    @Override
    public int getCount() {
        return mods.size();
    }

    @Override
    public Object getItem(int position) {
        return mods.get(position);
    }

    @Override
    public long getItemId(int position) {
        return position;
    }

    @Override
    public View getView(int position, View convertView, ViewGroup parent) {
        convertView = ((Activity)context).getLayoutInflater().inflate(R.layout.activity_list, parent, false);
        TextView modName = convertView.findViewById(R.id.path_name);
        modName.setText(mods.get(position));
        ImageView modIcon = convertView.findViewById(R.id.file_name);
        modIcon.setImageURI(Uri.fromFile(new File(Environment.getExternalStorageDirectory() + "/games/MCEngine/mods/" + modName.getText() + "/mod_icon.png")));

        return convertView;
    }
}
