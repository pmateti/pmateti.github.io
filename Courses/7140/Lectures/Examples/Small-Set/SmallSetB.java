/**
 * This class implements a set of integers.  It is limited by the size
 * sz chosen at compile time.

 * This is expected to be a good example of software design in the
 * tiny*tiny.  It is also intended as an example for use with learning
 * JML, JUnit/TestNG, PMD, FindBugs, and others.  See
 * ./smallset-exercises.html .

 * Possibly contains bugs.  But do remember how we define bugs.  Some
 * tools find style issues and label them as bugs.  We naively assume
 * all objects are non-null.  Also, not fully documented as expected
 * in HW2 of CS7140.

 * @file SmallSet.java
 * @author pmateti@wright.edu
 * @date Oct 20, 2013, Jul 20, 2018

 * <p> For further details, see
 * http://cecs.wright.edu/~pmateti/Courses/7140/Lectures/Examples/SmallSet
 * Long names have been shortened.

 * <p>Apparently javadoc has no tags for pre- and post-conditions; so
 * I am placing assert()s at the top of the methods for pre- and at
 * the bottom for post.  As is, we are not using JML syntax.  The old
 * objects, setOf() and classInv() are needed only because of asserts.
 * The obj1 == obj2 used below is intended to be deep equality.
 */

import java.io.*;

public class SmallSet {

    private int[] ear;          // element array storing the set elements
    private int ux = 0;         // ear[0..ux-1] occupied; ear[ux..sz-1] vacant
    private int sz = 1000;      // new-created size of this array
    
    /**
     * Return the abstract set value of concrete object s
     */
    private SmallSet setOf(SmallSet s) {
        return s.compact();
    }

    /**
     * Return the abstract set value of a[m..n]
     */

    private SmallSet setOf(int [] a, int m, int n) {
        return setOf(new SmallSet(a, m, n));
    }

    /**
     * @param s any SmallSet
     * Class invariant, expressed as a boolean function.
     * @return truthhood of the boolen exp of the invariant
     */
    public boolean classInv(SmallSet s) {
        return
            0 <= s.ux && s.ux < s.sz
            && setOf(s) == setOf(s.ear, 0, ux-1)
            ;
    }

    public SmallSet() {
        ear = new int[sz];
    }

    public SmallSet(int [] a, int m, int n) {
        assert m < n;
        ear = new int[sz];
        for (int i = m; i < n; i++) {
            insert(a[i]);       // should we instead do ear[ux++] = a[i]?
        }
    }

    /**
     * @param e element to search for
     * @return any i such that ear[i] == e
     */
    private int indexOf(int e) {
        int i = 0, saved = ear[ux];
        ear[ux] = e;            // sentinel
        while (ear[i] != e)
            i++;
        assert 0 <= i && i <= ux && e == ear[i] ;
        ear[ux] = saved;
        return i;
    }

    public boolean isin(int e) {
        int x = indexOf(e);
        assert x >= ux || (e == ear[x] && 0 <= x && x < ux); // TBD
        return (x < ux);
    }

    /**
     * While keeping the abstraction intact, delete duplicats from
     * ear[] so that ux can be the lowest possible.  Rewrite it
     * without using newset. [Why?] [API design question: Should this
     * method be public or private?]
     * @return the new SmallSet equal to setOf(this)
     */
    
    private SmallSet compact1() {
        SmallSet newset = new SmallSet();
        while (ux > 0) {
            int e = ear[ux-1];
            delete(e); // why delete? because of the ux > 0 of while loop
            if (! newset.isin(e))
                newset.insert(e);
        }
        //        assert setOf(this) == newset && newset.ux <= this.ux;
        return newset;
    }

    private SmallSet compact2() {
        SmallSet newset = new SmallSet();
        for (int i = 0; i < ux; i++) {
            int e = ear[i];
            if (! newset.isin(e))
                newset.insert(e);
        }
        return newset;
    }

    private SmallSet compact() {
        int oldux = ux;
        ux = 0;
        for (int i = 0; i < oldux; i++) {
            int e = ear[i];
            if (indexOf(e) == ux)
                ux++;
        }
        return this;
    }

    public SmallSet insert(int e) {
        if (ux < sz - 1) {
            if (ux > 0)
                ear[ux] = ear[0];
            ear[0] = e;
            ux++;
        } else {
            // see design obligations discussion at the URL given above.
        }
        assert ux == sz - 1 || isin(e);
        return this;
    }

    /**
     * Delete all occurrences of e in ear[a to b-1], and compact ear[].
     * A casual reader comments: This is tricky!  Do write a loop invariant.
     * @return the count of deletions.
     */
    private int delete(int a, int b, int e) {
        assert 0 <= a && a < b;
        int nd = 0;             // deleted e this many times
        for (int i = a, j = a; i < b; i++) {
            if (ear[i] == e)
                nd ++;
            else {
                if (j < i)
                    ear[j] = ear[i];
                j++;
            }
        }
        //        assert 0 <= nd && nd < b - a && ! setOf(ear, a, b).isin(e);
        return nd;
    }
    
    /**
     * @param e All occurrences of e in ear[] must be deleted.
     * @return this
     */

    public SmallSet delete(int e) {
        assert ux < sz;
        ux -= delete(0, ux, e);
        assert ux < sz && !isin(e);
        return this;
    }

    /**
     * @return size of the set; Side effect: this set gets compacted;
     */
    public int nitems() {
        SmallSet s = compact();
        ux = s.ux;
        ear = s.ear;
        return ux;
    }

    private SmallSet mathUnion(SmallSet a, SmallSet b) {
        for (int i = 0; i < b.ux; i++)
            a.insert(b.ear[i]);
        return a;
    }

    public SmallSet union(SmallSet tba) {
        SmallSet old = this;
        for (int i = 0; i < tba.ux; i++)
            insert(tba.ear[i]);
        assert setOf(this) == mathUnion(setOf(old), setOf(tba));
        return this;
    }

    private SmallSet mathIntersect(SmallSet a, SmallSet b) {
        SmallSet c = new SmallSet();
        for (int i = 0; i < b.ux; i++) {
            int e = b.ear[i];
            if (a.isin(e))
                c.insert(e);
        }
        return c;
    }

    private SmallSet mathDiff(SmallSet a, SmallSet b) {
        SmallSet c = mathUnion(a, b);
        SmallSet d = mathIntersect(a, b);
        for (int i = 0; i < d.ux; i++)
            c.delete(d.ear[i]);
        return c;
    }

    public SmallSet diff(SmallSet tbs) {
        SmallSet old = this;
        SmallSet newset = new SmallSet();
        for (int i = 0; i < tbs.ux; i++)
            if (! this.isin(tbs.ear[i])) newset.insert(tbs.ear[i]);
        for (int i = 0; i < this.ux; i++) {
            if (! tbs.isin(this.ear[i])) newset.insert(this.ear[i]);
        }
        ear = newset.ear;
        ux = newset.ux;
        boolean b = setOf(this) == mathDiff(setOf(old), setOf(tbs));
        return this;
    }

    public String toString() {
        String s = "el: ";
        for (int i = 0; i < ux; i++) {
            s += ", " + ear[i];
        }
        s += ", ux=" + ux;
        return s;
    }

    public static void main(String[] args) {
        int [] a = {1,2,3,4,5,6,7, 1,2,3,4,5,6};
        SmallSet s = new SmallSet(a, 0, a.length - 1); // shows a bug
        SmallSet t = new SmallSet();
        for (int j = 0; j < 3; j++)
            for (int i = 0; i < a.length; i++) {
                t.insert(a[i] - 1);
            }
        // some simple tests
        System.out.println("set s " + s + "; nitems=" + s.nitems());
        s.delete(1);
        s.delete(3);
        System.out.println("set s " + s + "; nitems=" + s.nitems());
        s.union(t);
        System.out.println("set s " + s + "; nitems=" + s.nitems());
        t.insert(7);
        t.diff(s);
        System.out.println("set t " + t + "; nitems=" + t.nitems());


        SmallSet s1 = new SmallSet();
        SmallSet s2 = new SmallSet();
        s1.insert(3);
        s1.insert(5);
        s2.insert(7);
        SmallSet s3 = s1.union(s2);
        System.out.println(s3);

    }
}

// -eof-
