
/* The famous Quick Sort of C.A.R. Hoare;
 * % scalac quickSort.scala; scala QuickSort */

object QuickSort {

  def quicksort(a: Array[Int]) {

    def swap(i: Int, j: Int) {val t = a(i); a(i) = a(j); a(j) = t}
    
    def partition(l: Int, r: Int) {
      val pivot = a((l + r) / 2)
      var i = l;
      var j = r
      while (i <= j) {
        while (a(i) < pivot) i += 1
        while (a(j) > pivot) j -= 1
        if (i <= j) {
          swap(i, j)
          i += 1
          j -= 1
        }
      }
      if (l < j) partition(l, j)
      if (j < r) partition(i, r)
    }

    partition(0, a.length - 1)
  }
  
  def genArray(a: Array[Int]) = {
    for (i <- 0 until a.length) a(i) = util.Random.nextInt() % 100
  }

  def printArray(a: Array[Int]) = {
    for (e <- a) print(" " + e)
    println
  }

  def main(args : Array[String]) {
    val size = 20
    var a : Array[Int] = new Array[Int](size)
    genArray(a);  printArray(a)
    quicksort(a); printArray(a)
  }
}
