package com.taolesi.mcengine;

import android.app.Activity;
import android.app.Dialog;
import android.os.Build;
import android.view.Window;
import android.view.WindowManager;

public class StatusBarUtils {

    //设置Activity对应的顶部状态栏的颜色
    public static void setWindowStatusBarColor(Activity activity, int colorResId) {
        try {
            Window window = activity.getWindow();
            window.addFlags(WindowManager.LayoutParams.FLAG_DRAWS_SYSTEM_BAR_BACKGROUNDS);
            window.setStatusBarColor(activity.getResources().getColor(colorResId));
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    //设置Dialog对应的顶部状态栏的颜色
    public static void setWindowStatusBarColor(Dialog dialog, int colorResId) {
        try {
            Window window = dialog.getWindow();
            window.addFlags(WindowManager.LayoutParams.FLAG_DRAWS_SYSTEM_BAR_BACKGROUNDS);
            window.setStatusBarColor(dialog.getContext().getResources().getColor(colorResId));
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}