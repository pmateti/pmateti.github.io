

// Grep a /var/log/auth.log file for login attempts; Nov 2015; Ex of
// Streams, Lambdas

import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.Arrays;
import java.util.List;
import java.util.stream.Stream;

public class AuthLogStreamEx {
     
    private void grep(String inpfnm, String outfnm)
        throws IOException {
        FileWriter fw = new FileWriter(outfnm);
        Stream<String> lns = Files.lines(Paths.get(inpfnm));

        //@formatter:off
        lns
            .filter(ln -> ln.contains("Invalid user"))
            .map(ln -> ln.split(" "))
            .forEach(a -> writeToFile(fw, a[a.length - 1])); // write IP addr
        //@formatter:on
        lns.close();
        fw.close();
    }
 
    private int pn = 0;         // line counter of fw

    private void writeToFile(FileWriter fw, String s) {
        try {
            fw.write(String.format("%d %s\n", ++pn, s));
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) throws IOException {
        String ifnm = "/var/log/auth.log", ofnm = "/tmp/invalidUsers.txt";
        switch (args.length) {
        case 0: break;
        case 2: ofnm = args[1]; // fall through
        case 1: ifnm = args[0]; break;
        default:
            System.out.println
                ("StreamEx Usage: At most two file names expected");
            System.exit(0);
        }
        new AuthLogStreamEx().grep(ifnm, ofnm);
    }
}

// -eof-
