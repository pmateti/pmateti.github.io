
import java.util.*;

public class Meenie {

    public static Thread oneThread(String s, int d) {
      return new Thread
          (() ->                // a lambda exp Runnable
           {
               int i = 0;
               while (true) {
                   System.out.println(s + " " + i++);
                   try {Thread.sleep(d);} catch(Exception e) {};
               }
           });
    }

    public static void main(String args[]) {
        Thread t1 = oneThread("eeny", 500), t2 = oneThread("meeny", 100);
        Thread t3 = oneThread("miny", 200), t4 = oneThread("moe", 300);
        t1.start();
        t2.start();
        try {Thread.sleep(5000);} catch(Exception e) {};
        t3.start();
        t4.start();
    }
}
