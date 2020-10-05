
// TBD has bugs


public class InsertionSort {

    public static void iSort1(int a[]) {
        for (int j = 1; j < a.length; j ++) {
            int key = a[j];
            int i = j - 1;
            while (i >= 0 &&  a[i] > key) {
                a[i+1] = a[i];
                i --;
            }
            a[i+1] = key;
        }
    }

    public static void iSort2(int a[]) {
        for (int j = 1; j < a.length; j ++) {
            int key = a[j];
            for (int i = j - 1; i >= 0; i --) {
                if (a[i] <= key)
                    break;
                a[i+1] = a[i];
            }
            a[j] = key;
        }
    }

    public static void iSort3(int a[]) {
        for (int j = a.length - 1; j >= 0; j --) {
            int x = 0;
            for (int i = 1; i < j; i ++) {
                if (a[i] > a[x]) x = i;
            }
            a[j] = a[x];
        }
    }

    public static void main(String argv[]) {
	int a[] = new int[argv.length];
	for (int i = argv.length - 1; i >= 0; i --)
	    a[i] = Integer.parseInt(argv[i]);

        switch (a[0]) {
        case 1: iSort1(a); break;
        case 2: iSort2(a); break;
        default: iSort3(a);
        }
	for (int i = 0 ; i < argv.length ; i ++) System.out.print(a[i] + " ");
	System.out.println();
    }   
}
