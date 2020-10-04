
// % scalac bounded-buffers.scala ; % scala BoundedBufferEx; ^C to kill
// Look up Bounded Buffers in Andrews, p187, and also Chap 6: Monitors
// pmateti@wright.edu

class BoundedBuffer(N: Int) {
  val buf = new Array[Int](N)
  var in, out = 0                       // indices of buf
  var n = 0                             // #items in buf

  def put(x: Int) = synchronized {
    while (n >= N) {
      println("buf full")
      wait()
    }
    buf(in) = x ; in = (in + 1) % N ; n += 1
    if (n == 1) notifyAll()
  }

  def get: Int = synchronized {
    while (n == 0) wait()
    val x = buf(out) ; out = (out + 1) % N ; n -= 1
    if (n == N - 1) notifyAll()
    x
  }
}

object BoundedBufferEx {
  val buf = new BoundedBuffer(10)

  def produceItem: Int = util.Random.nextInt()
  def consumeItem(x: Int) = {println("\tconsume " + x)}

  def newProducer = {
    new Thread { override 
    def run() = {
      while (true) {
        val s = produceItem ; buf.put(s)
        println("prd " + buf.n + ", " + s)
      }}}}

  def newConsumer = {
    new Thread { override 
    def run() = {
      while (true) {
        // Thread.sleep(1000) // slow down
        val s = buf.get
        consumeItem(s)
      }}}}

  def main(args: Array[String]) {
    val ap = new Array[Thread](5)
    val ac = new Array[Thread](10)

    for (i <- 0 to 4) {ap(i) = newProducer; ap(i).start}
    for (i <- 0 to 9) {ac(i) = newConsumer; ac(i).start}
  }
}

// -eof-
