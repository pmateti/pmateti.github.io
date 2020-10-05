
// This is edited from activator package sample.become

import akka.actor._
import scala.concurrent.duration._

sealed trait DiningHakkerMessage
case class Put(hakker: ActorRef) extends DiningHakkerMessage
case class Take(hakker: ActorRef) extends DiningHakkerMessage
case class Busy(chopstick: ActorRef) extends DiningHakkerMessage
case class IsWith(chopstick: ActorRef) extends DiningHakkerMessage
object Eat extends DiningHakkerMessage
object Think extends DiningHakkerMessage

class Chopstick extends Actor {
  import context._

  def takenBy(hakker: ActorRef): Receive = {
    case Take(otherHakker) =>
      otherHakker ! Busy(self)
    case Put(`hakker`) =>
      become(available)
  }

  def available: Receive = {
    case Take(hakker) =>
      become(takenBy(hakker))
      hakker ! IsWith(self)
  }

  def receive = available
}

class Hakker(name: String, left: ActorRef, right: ActorRef) extends Actor {
  import context._

  def thinking: Receive = {
    case Eat =>
      become(hungry)
      left ! Take(self)
      right ! Take(self)
  }

  def hungry: Receive = {
    case IsWith(`left`) =>
      become(waiting_for(right, left))
    case IsWith(`right`) =>
      become(waiting_for(left, right))
    case Busy(chopstick) =>
      become(denied_a_chopstick)
  }

  def waiting_for(needs: ActorRef, has: ActorRef): Receive = {
    case IsWith(`needs`) =>
      println("%s has picked up %s and %s and starts to eat" .
              format(name, left.path.name, right.path.name))
      become(eating)
      system.scheduler.scheduleOnce(5.seconds, self, Think)
    case Busy(chopstick) =>
      has ! Put(self)
      startThinking(10.milliseconds)
  }

  def denied_a_chopstick: Receive = {
    case IsWith(chopstick) =>
      chopstick ! Put(self)
      startThinking(10.milliseconds)
    case Busy(chopstick) =>
      startThinking(10.milliseconds)
  }

  def eating: Receive = {
    case Think =>
      left ! Put(self)
      right ! Put(self)
      println("%s puts down his chopsticks and starts to think".format(name))
      startThinking(5.seconds)
  }

  def receive = {
    case Think =>
      println("%s starts to think".format(name))
      startThinking(5.seconds)
  }

  def startThinking(duration: FiniteDuration): Unit = {
    become(thinking)
    system.scheduler.scheduleOnce(duration, self, Eat)
  }
}

object DiningHakkersOnBecome {
  def main(args: Array[String]) = {
    val system = ActorSystem()
    val chopsticks = 
      for (i <- 0 to 4) yield
        system.actorOf(Props[Chopstick], "C" + i)
    val hakkers = for {
      (name, i) <- List (
        "P0", "P1", "P2", "P3", "P4").zipWithIndex
    } yield
      system.actorOf(
        Props(classOf[Hakker], name, chopsticks(i), chopsticks((i+1)%5)))
    hakkers.foreach( _ ! Think)
  }
}
