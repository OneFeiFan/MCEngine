package com.taolesi.mcengine;

import android.annotation.SuppressLint;
import android.content.ContentResolver;
import android.content.Context;
import android.database.Cursor;
import android.net.Uri;
import android.os.Build;
import android.os.FileUtils;
import android.provider.MediaStore;
import android.provider.OpenableColumns;
import android.widget.Toast;


import androidx.annotation.RequiresApi;
import androidx.documentfile.provider.DocumentFile;

import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.Reader;
import java.nio.charset.StandardCharsets;
import java.util.Enumeration;
import java.util.zip.ZipEntry;
import java.util.zip.ZipFile;
import java.util.zip.ZipInputStream;
import java.util.zip.ZipOutputStream;

public class FileTools {
    public static boolean deleteDirectory(File directory) {
        if (!directory.exists() || !directory.isDirectory()) {
            return false;
        }

        File[] files = directory.listFiles();
        if (files != null) {
            for (File file : files) {
                if (file.isDirectory()) {
                    deleteDirectory(file); // 递归删除子目录
                } else {
                    file.delete(); // 删除文件
                }
            }
        }
        return directory.delete(); // 删除目录本身
    }
    public static void unzip(Context ctx, String res, String output) {
        File targetFile = new File(output);
        if (!targetFile.exists()) {
            targetFile.mkdirs();
        } else {
          deleteDirectory(targetFile);
          targetFile.mkdirs();
        }
        try (ZipFile zipFile = new ZipFile(new File(res))) {
            Enumeration<? extends ZipEntry> enumeration = zipFile.entries();
            while (enumeration.hasMoreElements()) {
                ZipEntry entry = (ZipEntry) enumeration.nextElement();
                String name = entry.getName();
                if (entry.isDirectory()) {
                    continue;
                }
                try (BufferedInputStream inputStream = new BufferedInputStream(zipFile.getInputStream(entry))) {
                    String outName = output + "/" + name;
                    File outFile = new File(outName);
                    File tempFile = new File(outName.substring(0, outName.lastIndexOf("/")));
                    if (!tempFile.exists()) {
                        tempFile.mkdirs();
                    }
                    try (BufferedOutputStream outputStream = new BufferedOutputStream(new FileOutputStream(outFile))) {
                        int len;
                        byte[] buffer = new byte[1024];
                        while ((len = inputStream.read(buffer)) > 0) {
                            outputStream.write(buffer, 0, len);
                        }
                    }
                }
            }
        } catch (Exception e) {
            Toast.makeText(ctx, e.toString(), Toast.LENGTH_SHORT).show();
        }
    }

    public static DocumentFile getDoucmentFile(Context context, String path) {
        if (path.endsWith("/")) {
            path = path.substring(0, path.length() - 1);
        }
        String path2 = path.replace("/storage/emulated/0/", "").replace("/", "%2F");
        return DocumentFile.fromSingleUri(context, Uri.parse("content://com.android.externalstorage.documents/tree/primary%3AAndroid%2Fdata/document/primary%3A" + path2));
    }

    public static String changeToUri(String path) {
        if (path.endsWith("/")) {
            path = path.substring(0, path.length() - 1);
        }
        String path2 = path.replace("/storage/emulated/0/", "").replace("/", "%2F");
        return "content://com.android.externalstorage.documents/tree/primary%3AAndroid%2Fdata/document/primary%3A" + path2;
    }

    public static String JsonToObjTest(String src) {
        try {
            File jsonFile = new File(src);
            FileReader fileReader = new FileReader(jsonFile);
            Reader reader = new InputStreamReader(new FileInputStream(jsonFile), StandardCharsets.UTF_8);
            StringBuilder sb = new StringBuilder();
            while (true) {
                int ch = reader.read();
                if (ch != -1) {
                    sb.append((char) ch);
                } else {
                    fileReader.close();
                    reader.close();
                    return sb.toString();
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
            return e.toString();
        }
    }

    public static String readJsonFile(String fileName) {
        String jsonStr = "";
        File jsonFile = new File(fileName);
        if(!jsonFile.exists()){
            return null;
        }
        try {
            FileReader fileReader = new FileReader(jsonFile);
            Reader reader = new InputStreamReader(new FileInputStream(jsonFile), StandardCharsets.UTF_8);
            int ch = 0;
            StringBuilder sb = new StringBuilder();
            while ((ch = reader.read()) != -1) {
                sb.append((char) ch);
            }
            fileReader.close();
            reader.close();
            jsonStr = sb.toString();
            return jsonStr;
        } catch (IOException e) {
            e.printStackTrace();
            return null;
        }
    }

    @RequiresApi(api = Build.VERSION_CODES.Q)
    public static String uriToFileApiQ(Context context, Uri uri) {
        File file = null;
        //android10以上转换
        if (uri.getScheme().equals(ContentResolver.SCHEME_FILE)) {
            file = new File(uri.getPath());
        } else if (uri.getScheme().equals(ContentResolver.SCHEME_CONTENT)) {
            //把文件复制到沙盒目录
            ContentResolver contentResolver = context.getContentResolver();
            @SuppressLint("Recycle")
            Cursor cursor = contentResolver.query(uri, null, null, null, null);
            if (cursor.moveToFirst()) {
                @SuppressLint("Range")
                String displayName = cursor.getString(cursor.getColumnIndex(OpenableColumns.DISPLAY_NAME));
                try {
                    InputStream is = contentResolver.openInputStream(uri);
                    File cache = new File(context.getExternalCacheDir().getAbsolutePath(), displayName);
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
        if (file != null) {
            return file.getAbsolutePath();
        } else {
            return "";
        }
    }

    @SuppressLint("Range")
    public static String getFileFromContentUri(Context context, Uri uri) {
        if (uri == null) {
            return null;
        }
        String filePath;
        String[] filePathColumn = {MediaStore.DownloadColumns.DATA, MediaStore.DownloadColumns.DISPLAY_NAME};
        ContentResolver contentResolver = context.getContentResolver();
        @SuppressLint("Recycle")
        Cursor cursor = contentResolver.query(uri, filePathColumn, null, null, null);
        if (cursor != null) {
            cursor.moveToFirst();
            try (cursor) {
                filePath = cursor.getString(cursor.getColumnIndex(filePathColumn[0]));
                return filePath;
            } catch (Exception ignored) {
            }
        }
        return "";
    }

    public static void UnZipAssetsFolder(Context context, String zipFileString, String outPathString) throws Exception {
        ZipInputStream inZip = new ZipInputStream(context.getAssets().open(zipFileString));
        ZipEntry zipEntry;
        String szName = "";
        while ((zipEntry = inZip.getNextEntry()) != null) {
            szName = zipEntry.getName();
            if (zipEntry.isDirectory()) {
                szName = szName.substring(0, szName.length() - 1);
                File folder = new File(outPathString + File.separator + szName);
                folder.mkdirs();
            } else {
                File file = new File(outPathString + File.separator + szName);
                if (!file.exists()) {
                    file.getParentFile().mkdirs();
                    file.createNewFile();
                }
                FileOutputStream out = new FileOutputStream(file);
                int len;
                byte[] buffer = new byte[1024];
                while ((len = inZip.read(buffer)) != -1) {
                    out.write(buffer, 0, len);
                    out.flush();
                }
                out.close();
            }
        }
        inZip.close();
    }

    public static void copyFile(File file, File file1) {
        try (FileInputStream fis = new FileInputStream(file); FileOutputStream fos = new FileOutputStream(file1)) {
            byte[] bys = new byte[1024];
            int len;
            while ((len = fis.read(bys)) != -1) {
                fos.write(bys, 0, len);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void copyDir(File file, File file1) {
        if (!file.isDirectory()) {
            return;
        }
        if (!file1.exists()) {
            file1.mkdirs();
        }
        File[] files = file.listFiles();
        for (File f : files) {
            if (f.isDirectory()) {
                copyDir(f, new File(file1.getPath(), f.getName()));
            } else if (f.isFile()) {
                copyFile(f, new File(file1.getPath(), f.getName()));
            }
        }
    }
    public static void removeDir(File file, File file1) {
        if (!file.isDirectory()) {
            return;
        }
        if (!file1.exists()) {
            file1.mkdirs();
        }
        File[] files = file.listFiles();
        for (File f : files) {
            if (f.isDirectory()) {
                removeDir(f, new File(file1.getPath(), f.getName()));
            } else if (f.isFile()) {
                copyFile(f, new File(file1.getPath(), f.getName()));
            }
        }
        deleteDirectory(file);
    }
    public static void toZip(String srcDir, OutputStream out, boolean KeepDirStructure) throws RuntimeException {

        long start = System.currentTimeMillis();
        ZipOutputStream zos = null;
        try {
            zos = new ZipOutputStream(out);
            File sourceFile = new File(srcDir);
            compress(sourceFile, zos, sourceFile.getName(), KeepDirStructure);
            long end = System.currentTimeMillis();
            System.out.println("压缩完成，耗时：" + (end - start) + " ms");
        } catch (Exception e) {
            throw new RuntimeException("zip error from ZipUtils", e);
        } finally {
            if (zos != null) {
                try {
                    zos.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }
    }

    public static void compress(File sourceFile, ZipOutputStream zos, String name, boolean KeepDirStructure) throws Exception {
        byte[] buf = new byte[2 * 1024];
        if (sourceFile.isFile()) {
            zos.putNextEntry(new ZipEntry(name));
            int len;
            FileInputStream in = new FileInputStream(sourceFile);
            while ((len = in.read(buf)) != -1) {
                zos.write(buf, 0, len);
            }
            zos.closeEntry();
            in.close();
        } else {
            File[] listFiles = sourceFile.listFiles();
            if (listFiles == null || listFiles.length == 0) {
                if (KeepDirStructure) {
                    zos.putNextEntry(new ZipEntry(name + "/"));
                    zos.closeEntry();
                }

            } else {
                for (File file : listFiles) {
                    if (KeepDirStructure) {
                        compress(file, zos, name + "/" + file.getName(), KeepDirStructure);
                    } else {
                        compress(file, zos, file.getName(), KeepDirStructure);
                    }

                }
            }
        }
    }
    public static void deleteFile(String path) {
        File file = new File(path);
        if (file.isDirectory()) {
            File[] files = file.listFiles();
            for (File littleFile : files) {
                deleteFile(littleFile.getAbsolutePath());
            }
        } else {
            file.delete();
        }
        file.delete();
    }
}
