
// The N-Queens Problem from ScalaByExample.pdf

object NQueens {
  def isSafe(col: Int, queens: List[Int], delta: Int): Boolean = {
    false
  }
  def queens(n: Int): List[List[Int]] = {
    def placeQueens(k: Int): List[List[Int]] =
      if (k == 0) List(List())
      else
        for { 
          queens <- placeQueens(k - 1)
          column <- List.range(1, n + 1)
          if isSafe(column, queens, 1) 
        }
        yield
          column :: queens
    placeQueens(n)
  }
  def main(args: Array[String]) {
    println(queens(8))
  }
}

/* Omits many omittable tokens. */

/*
 * With the dummy isSafe returning true, the above will not terminate.
 * (Actually you get java.lang.OutOfMemoryError)
 * With  it returning false, no solutions are found.
 * 
 * Exercise 10.1.1 Replace the dummy function
 * def isSafe(col: Int, queens: List[Int], delta: Int): Boolean
 * with a correct one.  Here, delta is the difference between
 * the row of the queen to be placed and the row of the first
 * queen in the list.
 */
