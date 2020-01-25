
object traitEx {
  class Point(val x: Int, val y: Int) {
    override
    def toString = s"(${x}, ${y})"
  }

  trait Rectangular {
    def topLeft: Point
    def bottomRight: Point

    def left = topLeft.x
    def right = bottomRight.x
    def width = right - left
  }

  class Rectangle(val topLeft: Point, val bottomRight: Point)
      extends Rectangular {
  }

  def main(args : Array[String]) {
    val rect = new Rectangle(new Point(1, 2), new Point(9, 10))
    println("rect.left " + rect.left + " " + rect.topLeft)
  }
}
