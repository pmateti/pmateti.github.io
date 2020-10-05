
import scala.swing._
import event . _
import java.awt . { Color}
import java.awt.geom._

object MouseListener extends App {
  var path = new GeneralPath

  var panel = new Panel {
    override def paint(g: Graphics2D) {
      g.setPaint(Color.red)
      g.draw(path)
    }

    listenTo(mouse.clicks)
    reactions += {
      case e: MousePressed => {
        path.lineTo(e.point.x, e.point.y)
        path.moveTo(e.point.x, e.point.y)
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

  path.moveTo(0, 0); f.open
}
