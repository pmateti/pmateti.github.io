/*
<link href="http://www.cs.wright.edu/~pmateti/SyntaxHighLighter/styles/shCoreEclipse.css" rel="stylesheet" type="text/css" />
<script type="text/javascript" src="http://www.cs.wright.edu/~pmateti/SyntaxHighLighter/scripts/shCore.js"></script>

<script type="text/javascript" src="http://www.cs.wright.edu/~pmateti/SyntaxHighLighter/scripts/shBrushScala.js"></script>

<pre class="brush: scala">
*/

/* % scalac bounded-buffers*.scala ; % scala BoundedBufferThreads; ^C to kill
 * The println and sleep statements are here only to help demo.
 * pmateti@wright.edu 2014 */

class BoundedBuffer(N: Int) {

  val buf = new Array[Int](N)           // circular buf of N integers
  var in, out = 0                       // indices of buf
  var n = 0                             // #items in buf

  def put(x: Int) = synchronized {
    while (n >= N) {
      println("** buf full")
      wait()
    }
    buf(in) = x ; in = (in + 1) % N ; n += 1
    if (n == 1) notifyAll()
  }

  def get: Int = synchronized {
    while (n == 0) {
      println("** buf empty")
      wait()
    }
    val x = buf(out) ; out = (out + 1) % N ; n -= 1
    if (n == N - 1) notifyAll()
    x
  }
}

object BoundedBufferThreads {
  val buf = new BoundedBuffer(10)

  def produceItem: Int = {Thread sleep 500; util.Random.nextInt()}
  def consumeItem(x: Int) = {Thread sleep 500}

  def newProducer = {
    new Thread { 
      override 
      def run() = {
        while (true) {
          val s = produceItem ; buf.put(s)
          println(this + " producer " + buf.n + ": " + s)
        }}}}

  def newConsumer = {
    new Thread {
      override 
      def run() = {
        while (true) {
          val s = buf.get; consumeItem(s)
          print(this + " consumer " + buf.n + ": " + s)
        }}}}

  def main(args: Array[String]) {
    val ap = new Array[Thread](5)       // producers array
    val ac = new Array[Thread](10)      // consumers array

    for (i <- 0 to 4) {ap(i) = newProducer; ap(i).start}
    for (i <- 0 to 9) {ac(i) = newConsumer; ac(i).start}
  }
}

// -eof-
/*
</pre>
<script type="text/javascript">     SyntaxHighlighter.all();</script>
</html>
*/
