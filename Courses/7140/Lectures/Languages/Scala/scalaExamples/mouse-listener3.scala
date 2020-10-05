import swing._
import event . _
import java . awt . { Color}
import java.awt.geom._

object MouseListener extends App {

  var a, b = new Point (0, 0)

  var panel = new Panel {
    override def paint(g: Graphics2D) {
      g.setPaint(Color.blue)
      g.draw(new Line2D.Double(a.x, a.y, b.x, b.y))
    }

    listenTo(mouse.clicks)
    reactions += {
      case e: MouseClicked => {
        a = b
        b = e.point
        repaint
      }
    }
    preferredSize = new Dimension(300, 300)
  }

  var f = new MainFrame {
    title = "pmwhiteboard"
    contents = panel
    centerOnScreen
  }

  f.open
}
