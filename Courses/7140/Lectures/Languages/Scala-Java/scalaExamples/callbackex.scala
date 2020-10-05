
// from ScalaTutorial.pdf 2014 % scalac callbackex.scala; scala CallBackEx

object  CallBackEx {
  var k = 0
  def oncePerSecond(callback: () => Unit) {
    while (k < 10) { callback(); Thread sleep 1000 }
  }
  def timeFlies() {
    k += 1
    println("time flies like an arrow " + k)
  }
  def main(args: Array[String]) {
    oncePerSecond(timeFlies)
  }
}

/* Exercise: If we move k += 1 from where it is to just above the
 * while loop, k does not change from 1.  Explain why.
 */
