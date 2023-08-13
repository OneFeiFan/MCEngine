package com.taolesi.mcengine;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class Log {
    public static String dir;
    public static boolean setDir(String patch) {
        dir = patch;
        return true;
    }
    public static String getDir() {
        return dir;
    }
    public static boolean clear() {
        File file = new File(getDir());
        return file.delete();
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
}
