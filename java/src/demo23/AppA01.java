/*
 * THREAD-LOCAL STORAGE
 * Introduction
*/

package demo23;



public class AppA01 {

    public static void main(String[] args) {
        // Main thread sets value = "APPLE"
        MyTask.set("APPLE");
        System.out.println(MyTask.get());


        // Child thread gets value
        // Expected output: "NOT SET"
        new Thread(() -> {
            System.out.println(MyTask.get());
        }).start();
    }



    static class MyTask {
        private static ThreadLocal<String> data = new ThreadLocal<>();

        public static String get() {
            // If this is first time getting data
            if (null == data.get()) {
                data.set("NOT SET");
            }

            return data.get();
        }

        public static void set(String value) {
            data.set(value);
        }
    }

}
