

// Parse a log file
// mod of an example from http://eyalgo.com/ 2015 by pmateti@wright.edu

import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.Arrays;
import java.util.List;
import java.util.stream.Stream;

class OneLogFile {
    public Stream<String> logFile;
    OneLogFile() {
        final String s1 = "2015-01-06 11:33:03 b.s.d.task [INFO] Emitting:"
            + "adEventToRequestsBolt __ack_ack [-6722594615019711369" +
            "-1335723027906100557]";
        final String s2 = "2015-01-06 11:33:03 b.s.d.executor [INFO]"
            + " Processing received message source: eventToManageBolt:2,"
            + " stream: __ack_ack, id: {}, [-6722594615019711369 "
            + "-1335723027906100557]";
        final String s3 = "2015-01-06 11:33:04 c.s.p.d.PackagesProvider "
            + "[INFO] ===---> Loaded package com.foo.bar";
        final String s4 = "2015-01-06 11:33:04 c.s.p.d.PackagesProvider "
            + "[INFO] ===---> Loaded package co.il.boo";
        final String s5 = "2015-01-06 11:33:04 c.s.p.d.PackagesProvider "
            + "[INFO] ===---> Loaded package dot.org.biz";
        logFile = Arrays.asList(s1, s2, s3, s4, s5).stream();
    }
}

public class StreamEx {
     
    private void parse(Stream<String> lns, String ofnm)
        throws IOException {
        final FileWriter fw = new FileWriter(ofnm);
        //@formatter:off
        lns.filter(line -> line.contains("===---> Loaded package"))
            .map(line -> line.split(" "))
            .map(arr -> arr[arr.length - 1])
            .forEach(packageName-> writeToFile(fw, packageName));
        //@formatter:on
        fw.close();
        lns.close();
    }
 
    private int pn = 0;

    private void writeToFile(FileWriter fw, String packageName) {
        try {
            fw.write(String.format("%d %s\n", ++pn, packageName));
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    public static void main(String[] args) throws IOException {
        if (args.length == 0) {
            System.out.println("StreamEx Usage: Output file name is missing");
            System.exit(0);
        }
        Stream<String> lns =  (args.length == 1
                                 ? new OneLogFile().logFile
                                 : Files.lines(Paths.get(args[1])));
        new StreamEx().parse(lns, args[0]);
    }

}
