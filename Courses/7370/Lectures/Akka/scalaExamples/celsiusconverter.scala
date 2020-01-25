import scala.swing._
import event._

object CelsiusConverter extends SimpleSwingApplication {

   val ui = new FlowPanel {
     val celsius = new TextField {columns = 5}
     val fahrenheit = new TextField {columns = 5}
     contents.append(celsius,
                     new Label(" Celsius  =  "),
                     fahrenheit,
                     new Label(" Fahrenheit"))
     border = Swing.EmptyBorder(15, 10, 10, 10)

     listenTo(fahrenheit, celsius)
     reactions += {
       case EditDone(`fahrenheit`) => {
         val f = fahrenheit.text.toInt
         val c = (f - 32) * 5 / 9
         celsius.text = c.toString
       }
       case EditDone(`celsius`) => {
         val c = celsius.text.toInt
         val f = c * 9 / 5 + 32
         fahrenheit.text = f.toString
       }
     }
   }

   val top = new MainFrame {
     title = "Temperaturkonvertering"
     contents = ui
   }
}
