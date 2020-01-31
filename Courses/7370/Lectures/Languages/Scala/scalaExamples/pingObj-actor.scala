/*
 package com.typesafe.atmos.sample, mods by pmateti@wright.edu
 scalac name-of-this-file.scala; scala PingObj
 when you had enough, kill it with ^C */


import akka.actor._
import scala.concurrent.duration._
import scala.concurrent.ExecutionContext.Implicits.global

case object Ping
case object Pong
 
class PingActor extends Actor {
  def receive = {
    case Ping => println("Pinged at: " + System.currentTimeMillis)
    case Pong => println("now Ponged: " + System.currentTimeMillis)
  }
}

object PingObj extends App {
  val acsys = ActorSystem("SimpleApp");
  val pingActor = acsys . actorOf(Props[PingActor], "pingActor");
  //  implicit val sd = acsys.dispatcher;
  val s = acsys.scheduler.schedule(
    5 . seconds,                        // begin after 5 seconds
    1 . seconds,                        // repeat every 1 second
    pingActor,                          // targeted receiver
    Ping                                // the message object to send
  );

  acsys.scheduler.schedule(10.seconds, 2.seconds, pingActor, Pong);

  println("s: " + s)
}
 
