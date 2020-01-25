import scala.sys.process._
val cmd = "uname -a" // Your command
val output = cmd.!! // Captures the output
