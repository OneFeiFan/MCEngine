package com.taolesi.mcengine;

import android.content.ContentProvider;
import android.content.ContentValues;
import android.database.Cursor;
import android.net.Uri;

public class permissionProvider extends ContentProvider {


    @Override
    public boolean onCreate() {
        // 底层数据库初始化
        return false;
    }

    @Override
    public Cursor query(Uri uri, String[] projection, String selection,
                        String[] selectionArgs, String sortOrder) {
        return null;
    }

    @Override //要实现该方法必须完成
    //1.定义MIME类型
    //2.定义URI字符串
    //3.用urimather建立code和uri映射
    //4.用code来映射不同MIEM类型
    public String getType(Uri uri) {
        // 返回MIME类型,一般用静态块来完成
        return null;
    }

    @Override
    public Uri insert(Uri uri, ContentValues values) {
        return null;
    }

    @Override
    public int delete(Uri uri, String selection, String[] selectionArgs) {
        return 0;
    }

    @Override
    public int update(Uri uri, ContentValues values, String selection,
                      String[] selectionArgs) {
        return 0;
    }
}