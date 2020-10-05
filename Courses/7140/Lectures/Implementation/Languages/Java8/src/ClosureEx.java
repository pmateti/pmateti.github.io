// should illustrate closure; not ok

interface IntFunc {
    public int call(int i);
}

class PlusX implements IntFunc {
    final int x = 0;
    PlusX(int n) { x = n; }
    public int call(int i) { return i + x; }
}

public class ClosureEx {

    public static void main(String args[]) {
        IntFunc f = new PlusX(2);
        System.out.println(f.call(3));
        // prints 5
    }
}
