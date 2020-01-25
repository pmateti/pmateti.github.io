import swing._
import event . _
import java.awt . { Color}
import java.awt.geom._

object MouseListener extends App {

  var x1, x2, xz, y1, y2, yz = 0

  var panel = new Panel {
    override def paint(g: Graphics2D) {
      g.setPaint(Color.red)
      g.draw(new Line2D.Double(xz, yz, x2, y2))
    }

    listenTo(mouse.clicks)
    reactions += {
      case e: MousePressed => {
        // x1 = x2; // generates compilation error; has to do with x1 ??
        xz = x2; yz = y2
        x2 = e.point.x; y2 = e.point.y
        repaint
      }
    }
    preferredSize = new Dimension(300, 300)
  }

  var f = new MainFrame {
    title = "pmwhiteboard2"
    contents = panel
    centerOnScreen
  }

  f.open
}
