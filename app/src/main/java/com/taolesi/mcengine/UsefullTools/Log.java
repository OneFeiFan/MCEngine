package com.taolesi.mcengine.UsefullTools;

import static com.taolesi.mcengine.UsefullTools.FileTools.deleteFile;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class Log {
    private static String dir;

    public static void init(String dir, String fileName) {
        File file = new File(dir);
        if (!file.exists()) {
            file.mkdir();
        }
        setDir(file.getAbsolutePath() +"/"+fileName);
        clear();
    }

    private static void setDir(String patch) {
        dir = patch;
    }

    private static String getDir() {
        return dir;
    }

    private static boolean clear() {
        deleteFile(getDir());
        return true;
    }

    public static void put(String str) {
        File file = new File(getDir());
        try (BufferedWriter writer = new BufferedWriter(new FileWriter(file, true))) {
            writer.write(str);
            writer.newLine();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
    public static void put(int str) {
        put(String.valueOf(str));
    }
    public static void put(boolean str) {
        put(String.valueOf(str));
    }
    public static void put(long str) {
        put(String.valueOf(str));
    }
}
