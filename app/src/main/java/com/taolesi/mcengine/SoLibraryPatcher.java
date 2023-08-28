package com.taolesi.mcengine;
import android.content.Context;
import android.os.Build;
import dalvik.system.DexFile;
import dalvik.system.PathClassLoader;
import java.io.File;
import java.lang.reflect.Array;
import java.lang.reflect.Constructor;
import java.lang.reflect.Field;
import java.lang.reflect.InvocationTargetException;
import java.util.List;

public class SoLibraryPatcher{

    public static void v22Install(PathClassLoader pathClassLoader, String nativeLibraryPath){
        Object pathList = getPathList(pathClassLoader);
        try{
            Field field = pathList.getClass().getDeclaredField("nativeLibraryDirectories");
            field.setAccessible(true);
            Object list = field.get(pathList);
            File file = new File(nativeLibraryPath);
            if (list instanceof List){
                // add
                ((List) list).add(file);
            }else if (list instanceof File[]){
                // create
                File[] newList = new File[((File[]) list).length + 1];
                // clone data
                System.arraycopy(list, 0 , newList, 0, ((File[]) list).length);
                // add
                newList[((File[]) list).length] = file;
                // set
                field.set(pathList, newList);
            }
        }catch (NoSuchFieldException | IllegalAccessException e){
            e.printStackTrace();
        }
    }

    public static void v25Install(PathClassLoader pathClassLoader, String nativeLibraryPath){
        Object pathList = getPathList(pathClassLoader);
        try{
            Field field = pathList.getClass().getDeclaredField("nativeLibraryPathElements");
            field.setAccessible(true);
            Object list = field.get(pathList);
            Class<?> elementType = field.getType().getComponentType();
            Constructor<?> constructor = elementType.getConstructor(File.class, boolean.class, File.class, DexFile.class);
            constructor.setAccessible(true);
            Object element = constructor.newInstance(new File(nativeLibraryPath), true, null, null);
            if (list instanceof List){
                ((List) list).add(element);
            }else if (list instanceof Object[]){
                Object[] newList = new File[((Object[]) list).length + 1];
                System.arraycopy(list, 0 , newList, 0, ((Object[]) list).length);
                newList[((Object[]) list).length] = element;
                field.set(pathList, newList);
            }
        }catch (NoSuchFieldException | IllegalAccessException | NoSuchMethodException | InstantiationException |InvocationTargetException e){
            e.printStackTrace();
        }
    }

    public static Object getPathList(Object classLoader){
        try{
            Class clazz = Class.forName("dalvik.system.BaseDexClassLoader");
            Field field = clazz.getDeclaredField("pathList");
            field.setAccessible(true);
            return field.get(classLoader);
        }catch (ClassNotFoundException | NoSuchFieldException | IllegalAccessException e){
            e.printStackTrace();
        }
        return null;
    }

    public static void nowInstall(PathClassLoader pathClassLoader, String nativeLibraryPath)throws ClassNotFoundException, NoSuchFieldException, IllegalAccessException, NoSuchMethodException, InvocationTargetException, InstantiationException{
        Object pathList = getPathList(pathClassLoader);

        Class<?> nativeLibraryElementClass = Class.forName("dalvik.system.DexPathList$NativeLibraryElement");
        Constructor<?> element = nativeLibraryElementClass.getConstructor(File.class);
        Field systemNativeLibraryDirectories = pathList.getClass()
                .getDeclaredField("systemNativeLibraryDirectories");
        Field nativeLibraryDirectories = pathList.getClass().getDeclaredField("nativeLibraryDirectories");
        Field nativeLibraryPathElements = pathList.getClass().getDeclaredField("nativeLibraryPathElements");
        systemNativeLibraryDirectories.setAccessible(true);
        nativeLibraryDirectories.setAccessible(true);
        nativeLibraryPathElements.setAccessible(true);
        List<File> systemFiles = (List<File>) systemNativeLibraryDirectories.get(pathList);
        List<File> nativeFiles = (List<File>) nativeLibraryDirectories.get(pathList);
        Object[] elementFiles = (Object[]) nativeLibraryPathElements.get(pathList);
        Object newElementFiles = Array.newInstance(nativeLibraryElementClass, elementFiles.length + 1);

        systemFiles.add(new File(nativeLibraryPath));
        nativeFiles.add(new File(nativeLibraryPath));

        systemNativeLibraryDirectories.set(pathList, systemFiles);
        nativeLibraryDirectories.set(pathList, nativeFiles);
        element.setAccessible(true);
        Object newInstance = element.newInstance(new File(nativeLibraryPath));
        Array.set(newElementFiles, 0, newInstance);
        for (int i = 1; i < elementFiles.length + 1; i++){
            Array.set(newElementFiles, i, elementFiles[i - 1]);
        }
        nativeLibraryPathElements.set(pathList, newElementFiles);
    }


    public static void addNativeLibraryDir(ClassLoader classLoader, String nativeLibraryPath) throws ClassNotFoundException, NoSuchFieldException, IllegalAccessException, NoSuchMethodException, InvocationTargetException, InstantiationException{
        PathClassLoader pathClassLoader = (PathClassLoader) classLoader;
        if (Build.VERSION.SDK_INT <= 22){
            v22Install(pathClassLoader, nativeLibraryPath);
        }else if (Build.VERSION.SDK_INT <= 25){
            v25Install(pathClassLoader, nativeLibraryPath);
        }else{
            nowInstall(pathClassLoader, nativeLibraryPath);
        }
    }

    public static void patchNativeLibraryDir(ClassLoader classLoader, String nativeLibraryPath) throws ClassNotFoundException, NoSuchFieldException, IllegalAccessException, NoSuchMethodException, InvocationTargetException, InstantiationException {
        ClassLoader pathClassLoader =  classLoader;
        if (Build.VERSION.SDK_INT <= 22) {
            Field fieldPathList = Class.forName("dalvik.system.BaseDexClassLoader").getDeclaredField("pathList");
            fieldPathList.setAccessible(true);
            Object pathList = fieldPathList.get(pathClassLoader);
            Field nativeLibraryDirectories = pathList.getClass().getDeclaredField("nativeLibraryDirectories");
            nativeLibraryDirectories.setAccessible(true);
            File[] files = (File[]) nativeLibraryDirectories.get(pathList);
            Object newFiles = Array.newInstance(File.class, files.length + 1);
            Array.set(newFiles, 0, new File(nativeLibraryPath));
            for (int i = 1; i < files.length + 1; i++) {
                Array.set(newFiles, i, files[i - 1]);
            }
            nativeLibraryDirectories.set(pathList, newFiles);
        } else if (Build.VERSION.SDK_INT <= 25) {
            Class<?> classBaseDexClassLoader = Class.forName("dalvik.system.BaseDexClassLoader");
            Field fieldPathList = classBaseDexClassLoader.getDeclaredField("pathList");
            fieldPathList.setAccessible(true);
            Object pathList = fieldPathList.get(pathClassLoader);

            Class<?> nativeLibraryElementClass = Class.forName("dalvik.system.DexPathList$Element");
            Constructor<?> element = nativeLibraryElementClass.getConstructor(File.class, boolean.class, File.class, DexFile.class);
            Field systemNativeLibraryDirectories = pathList.getClass().getDeclaredField("systemNativeLibraryDirectories");
            Field nativeLibraryDirectories = pathList.getClass().getDeclaredField("nativeLibraryDirectories");
            Field nativeLibraryPathElements = pathList.getClass().getDeclaredField("nativeLibraryPathElements");
            systemNativeLibraryDirectories.setAccessible(true);
            nativeLibraryDirectories.setAccessible(true);
            nativeLibraryPathElements.setAccessible(true);
            List<File> systemFiles = (List<File>) systemNativeLibraryDirectories.get(pathList);
            List<File> nativeFiles = (List<File>) nativeLibraryDirectories.get(pathList);
            Object[] elementFiles = (Object[]) nativeLibraryPathElements.get(pathList);
            Object newElementFiles = Array.newInstance(nativeLibraryElementClass, elementFiles.length + 1);

            systemFiles.add(new File(nativeLibraryPath));
            nativeFiles.add(new File(nativeLibraryPath));

            systemNativeLibraryDirectories.set(pathList, systemFiles);
            nativeLibraryDirectories.set(pathList, nativeFiles);
            element.setAccessible(true);
            Object newInstance = element.newInstance(new File(nativeLibraryPath), true, null, null);
            Array.set(newElementFiles, 0, newInstance);
            for (int i = 1; i < elementFiles.length + 1; i++) {
                Array.set(newElementFiles, i, elementFiles[i - 1]);
            }
            nativeLibraryPathElements.set(pathList, newElementFiles);
        } else {
            Class<?> classBaseDexClassLoader = Class.forName("dalvik.system.BaseDexClassLoader");
            Field fieldPathList = classBaseDexClassLoader.getDeclaredField("pathList");
            fieldPathList.setAccessible(true);
            Object pathList = fieldPathList.get(pathClassLoader);

            Class<?> nativeLibraryElementClass = Class.forName("dalvik.system.DexPathList$NativeLibraryElement");
            Constructor<?> element = nativeLibraryElementClass.getConstructor(File.class);
            Field systemNativeLibraryDirectories = pathList.getClass()
                    .getDeclaredField("systemNativeLibraryDirectories");
            Field nativeLibraryDirectories = pathList.getClass().getDeclaredField("nativeLibraryDirectories");
            Field nativeLibraryPathElements = pathList.getClass().getDeclaredField("nativeLibraryPathElements");
            systemNativeLibraryDirectories.setAccessible(true);
            nativeLibraryDirectories.setAccessible(true);
            nativeLibraryPathElements.setAccessible(true);
            List<File> systemFiles = (List<File>) systemNativeLibraryDirectories.get(pathList);
            List<File> nativeFiles = (List<File>) nativeLibraryDirectories.get(pathList);
            Object[] elementFiles = (Object[]) nativeLibraryPathElements.get(pathList);
            Object newElementFiles = Array.newInstance(nativeLibraryElementClass, elementFiles.length + 1);

            systemFiles.add(new File(nativeLibraryPath));
            nativeFiles.add(new File(nativeLibraryPath));

            systemNativeLibraryDirectories.set(pathList, systemFiles);
            nativeLibraryDirectories.set(pathList, nativeFiles);
            element.setAccessible(true);
            Object newInstance = element.newInstance(new File(nativeLibraryPath));
            Array.set(newElementFiles, 0, newInstance);
            for (int i = 1; i < elementFiles.length + 1; i++) {
                Array.set(newElementFiles, i, elementFiles[i - 1]);
            }
            nativeLibraryPathElements.set(pathList, newElementFiles);
        }
    }

}