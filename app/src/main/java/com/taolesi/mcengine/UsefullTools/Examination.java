package com.taolesi.mcengine.UsefullTools;

import static com.taolesi.mcengine.ModHelper.Loader.Toast;

import android.webkit.JavascriptInterface;

public class Examination {
    public static long concurrentTime1, concurrentTime2, concurrentMemory1, concurrentMemory2;
    @JavascriptInterface
    public static void start() {
        concurrentTime1 = System.nanoTime();
        Runtime runtime = Runtime.getRuntime();
        concurrentMemory1 = runtime.totalMemory() - runtime.freeMemory();
    }
    @JavascriptInterface
    public static void end() {
        concurrentTime2 = System.nanoTime();
        Runtime runtime = Runtime.getRuntime();
        concurrentMemory2 = runtime.totalMemory() - runtime.freeMemory();
        String time = String.valueOf((double) (concurrentTime2 - concurrentTime1) / 1000000);
        String memory = String.valueOf((double) (concurrentMemory2 - concurrentMemory1) / 1024 / 1024);
        Toast("---------------您的代码执行时间为：" + time.substring(0, time.equals("0.0") ? 1 : (time.indexOf(".") + 3)) + " ms, 消耗内存：" + memory.substring(0, memory.equals("0.0") ? 1 : (memory.indexOf(".") + 3)) + " M + !---------------");
    }
}