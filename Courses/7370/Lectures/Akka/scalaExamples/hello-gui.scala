
// % scalac -classpath /usr/share/java/swing-layout.jar hello-gui.scala
// % scala HelloWorld

import scala.swing._

object HelloWorld extends SimpleSwingApplication {
  def top = new MainFrame {
    title = "Hello, World!"
    contents = new Button {
      text = "Hello! Click Me!"
      reactions += { 
        case scala.swing.event.ButtonClicked(_) => 
          println("Button clicked")
          quit()
      }
    }
  }
}
