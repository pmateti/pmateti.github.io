
#+begin_src java
import java.io.*;
import java.util.*;
public class Philosopher extends Thread {
  static final int count = 5;
  Chopstick left;
  Chopstick right;
  int position;

  Philosopher(int p, Chopstick l, Chopstick r) {
    position = p;
    left = l;
    right = r;
  }

  // main shown below
}
#+end_src

#+begin_src java
public static void main(String[] args) {
  Philosopher phil[] = new Philosopher[count];
  Chopstick last = new Chopstick();
  Chopstick left = last;
  for (int i = 0; i < count; i++) {
    Chopstick right = (i==count-1) ? last : new Chopstick();
    phil[i] = new Philosopher(i, left, right);
    left = right;
  }

  for (int i = 0; i < count; i++) { phil[i].start(); }
}
#+end_src
