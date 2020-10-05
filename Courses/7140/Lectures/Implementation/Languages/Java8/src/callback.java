
// ObjectCallback??


public class callback {

    public static void main(String[] args) {
        int number = 5;

        Object callback = () -> {
            return (number = number + 1);
        };

        Object result = callback.Callback();
        System.out.println(result);
    }
}
