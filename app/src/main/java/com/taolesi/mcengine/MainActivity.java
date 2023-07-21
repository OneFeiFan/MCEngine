package com.taolesi.mcengine;

import androidx.appcompat.app.AppCompatActivity;

import android.Manifest;
import android.content.Intent;
import android.net.Uri;
import android.os.Build;
import android.os.Bundle;
import android.os.Environment;
import android.provider.Settings;
import android.widget.Toast;

import com.permissionx.guolindev.PermissionX;
import com.permissionx.guolindev.callback.ExplainReasonCallbackWithBeforeParam;
import com.permissionx.guolindev.callback.ForwardToSettingsCallback;
import com.permissionx.guolindev.callback.RequestCallback;
import com.permissionx.guolindev.request.ExplainScope;
import com.permissionx.guolindev.request.ForwardScope;

import java.util.List;

public class MainActivity extends AppCompatActivity {
    private String[] PERMISSIONS = {
            Manifest.permission.WRITE_EXTERNAL_STORAGE,
            Manifest.permission.READ_EXTERNAL_STORAGE,
            Manifest.permission.MANAGE_EXTERNAL_STORAGE
    };
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        requestPermissions(PERMISSIONS, 99);
        /*PermissionX.init(this)
                .permissions(
                        Manifest.permission.WRITE_EXTERNAL_STORAGE, Manifest.permission.READ_EXTERNAL_STORAGE)
                .onExplainRequestReason(
                        new ExplainReasonCallbackWithBeforeParam() {
                            @Override
                            public void onExplainReason(
                                    ExplainScope scope, List<String> deniedList, boolean beforeRequest) {
                                scope.showRequestReasonDialog(deniedList, "即将申请的权限是程序必须依赖的权限", "我已明白");
                            }
                        })
                .onForwardToSettings(
                        new ForwardToSettingsCallback() {
                            @Override
                            public void onForwardToSettings(ForwardScope scope, List<String> deniedList) {
                                scope.showForwardToSettingsDialog(deniedList, "您需要去应用程序设置当中手动开启权限", "我已明白");
                            }
                        })
                .request(
                        new RequestCallback() {
                            @Override
                            public void onResult(
                                    boolean allGranted, List<String> grantedList, List<String> deniedList) {
                                if (allGranted) {
                                    Toast.makeText(MainActivity.this, "所有申请的权限都已通过", Toast.LENGTH_SHORT).show();

                                } else {
                                    Toast.makeText(MainActivity.this, "您拒绝了如下权限：" + deniedList, Toast.LENGTH_SHORT)
                                            .show();
                                }
                            }
                        });*/
    }

}