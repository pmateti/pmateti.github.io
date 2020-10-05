

// scalac printOptions.scala; scala PrintOptions -a -f -g blah -x -y

object PrintOptions {
  def main(args: Array[String]) = {
    for (a <- args; if a startsWith "-")
      println(a)
  }
}
