
// Callable Example coupled to Executor with Future
// unneeded spaces are inserted to clarify Java lexical structure

import java.util.concurrent.*;

class CT implements Callable < Integer > {
    private int delay = 0;
    public CT(int n) {
        delay = n;
    }
    @Override
    public Integer call() throws Exception {
        Thread.sleep(delay);    // represents a long computation
        return delay;
    }
}

public class CallableEx {

    static void futureGet (int d) {
        CT tk = new CT(d);
        ExecutorService es =  Executors . newSingleThreadExecutor();
        Future <Integer> ft = es.submit(tk);
        try {
            System. out. println("nanoTime now: " + System .  nanoTime());
            Integer rg = ft. get();
            System. out. println("nanoTime now: " + System .  nanoTime()
                               + "; ft.get gave " + rg);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void main ( String [] args) {
        int dd = (args.length > 0? Integer.parseInt(args [ 0 ]) : 100);
        futureGet(dd);
        System.exit(0);
    }
}

// -eof-
