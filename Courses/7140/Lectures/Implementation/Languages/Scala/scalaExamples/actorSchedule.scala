// package com.typesafe.atmos.sample, mods by pmateti@wright.edu
 
import akka.actor._
import scala.concurrent.duration._
import scala.concurrent.ExecutionContext.Implicits.global
// import scala.language.postfixOps

case object X
case object Y
 
class XActor extends Actor {
  def receive = {
    case X => println("Xed at: " + System.currentTimeMillis)
    case Y => println("now Yed: " + System.currentTimeMillis)
  }
}

class YActor extends Actor {
  def receive = {
    case X => println(System.currentTimeMillis + " iYActor")
    case Y => println(System.currentTimeMillis + " oYActor")
  }
}

object XYApp extends App {
  val system = ActorSystem("SimpleApp");
  val xActor = system . actorOf(Props[XActor], "xActor");
  val yActor = system . actorOf(Props[YActor], "whatEver");

  //  implicit val sd = system.dispatcher;

  val s = system.scheduler.schedule(
    5 . seconds,                        // begin after 5 seconds
    1 . seconds,                        // repeat every 1 second
    xActor,                             // targeted receiver
    X                                   // the message object to send
  );

  println("s: " + s);
  system.scheduler.schedule( 7.seconds, 3.seconds, yActor, X);
  system.scheduler.schedule( 9.seconds, 2.seconds, yActor, Y);
  system.scheduler.schedule(10.seconds, 2.seconds, xActor, Y)
}
 
