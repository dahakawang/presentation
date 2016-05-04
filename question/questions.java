package net.davidvoid.test;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;



class CustomizedLoader extends ClassLoader {

    @SuppressWarnings("deprecation")
    @Override
    protected Class<?> loadClass(String name, boolean resolve)
            throws ClassNotFoundException {
        synchronized (getClassLoadingLock(name)) {
            System.out.println(name);
            if (name == "test") {
                byte[] bytes = load();
                return defineClass(bytes, 0, bytes.length);
            }
            return super.loadClass(name, resolve);
        }
    }

    private byte[] load() {
        File file = new File("I:\\Data\\Projects\\PMCH\\workspace\\LearnJava8\\bin\\net\\davidvoid\\test\\Main.class");
        int size = (int) file.length();
        byte[] bytes = new byte[size];
        try (FileInputStream f = new FileInputStream(file)) {
            int s = f.read(bytes);
            if (s != bytes.length) {
                throw new RuntimeException("file " + bytes.length + " load:" + s);
            }
        } catch (IOException e) {
            throw new RuntimeException("no class");
        }
        
        return bytes;
    }
    
}

public class Main {
    public String name = "";

    public static void main(String[] args) throws ClassNotFoundException, InstantiationException, IllegalAccessException {
        ClassLoader loader = new CustomizedLoader();
        Class clazz = loader.loadClass("test");
        Main o = (Main) clazz.newInstance();
        o.name = "asdf";
    }
}
