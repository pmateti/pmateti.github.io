
// scalac swing-button.scala; scala FirstSwingApp
// % scalac swing-button.scala ; % scala SwingButtonApp

import scala.swing._ 

object SwingButtonApp extends SimpleSwingApplication {
  def top = new MainFrame {             // the names defined here are from
    title = "Swing Button App"          // SimpleSwingApplication API
    contents = new Button { 
      text = "Click me"
      reactions += { 
        case scala.swing.event.ButtonClicked(_) => 
          println("Button clicked")
          quit()
      }
    }
  }
}
