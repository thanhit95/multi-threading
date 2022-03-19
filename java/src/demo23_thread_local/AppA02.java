/*
 * THREAD-LOCAL STORAGE
 * Introduction
 *
 * Use ThreadLocal.withInitial for better initialization.
 */

package demo23_thread_local;



public class AppA02 {

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



    private static class MyTask {
        private static final ThreadLocal<String> data
                = ThreadLocal.withInitial(() -> "NOT SET");

        public static String get() {
            return data.get();
        }

        public static void set(String value) {
            data.set(value);
        }
    }

}
