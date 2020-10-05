
// Use two semaphores, strictly alt acquire/release

import java.util.concurrent.Semaphore;

class MyThread extends Thread {
    Semaphore s1, s2;

    public void run(){
        try {
            for(int i = 0; i < 10; i++) {
                s2.acquire(); System.out.println("  World!"); s1.release();
            }
        } catch (InterruptedException e) {e.printStackTrace();}
    }
}


public class helloTwoThreads {

    static Semaphore s1 = new Semaphore(1);
    static Semaphore s2 = new Semaphore(0);

    public static void main (String[] args) throws InterruptedException {
        MyThread mt = new MyThread();     
        mt.s1 = s1;
        mt.s2 = s2;
        mt.start();
        for (int i=0; i<5; i++) {
            s1.acquire(); System.out.println("Hello, "); s2.release();
        }
    }
}

