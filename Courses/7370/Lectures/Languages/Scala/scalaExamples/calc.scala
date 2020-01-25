
// from ScalaTutorial.pdf 2014 % scalac calc.scala; % scala Calc

object Calc {
  type Environment = String => Int
  abstract class Tree
  case class Sum(l: Tree, r: Tree) extends Tree
  case class Var(n: String) extends Tree
  case class Const(v: Int) extends Tree

  def eval(t: Tree, env: Environment): Int = t match {
    case Sum(l, r) => eval(l, env) + eval(r, env)
    case Var(n) => env(n)
    case Const(v) => v
  }

  def derive(t: Tree, v: String): Tree = t match {
    case Sum(l, r) => Sum(derive(l, v), derive(r, v))
    case Var(n) if (v == n) => Const(1)
    case _ => Const(0)
  }

  def main(args: Array[String]) {
    val exp: Tree = Sum(Sum(Var("x"),Var("x")),Sum(Const(7),Var("y")))
    val env: Environment = { case "x" => 5 case "y" => 7 }
    println("Expression: " + exp)
    println("Evaluation with x=5, y=7: " + eval(exp, env))
    println("Derivative relative to x:\n " + derive(exp, "x"))
    println("Derivative relative to y:\n " + derive(exp, "y"))
  }
}

/* pmateti@wright.edu
 * Exercise 1: Replace the exp (x + x) + (7 + y) with one of
 * your choice, still without * and /
 * Exercise 2: Extend it to include * and /
 * Exercise 3: Develop an extension so that the environment can be
 * redefined from input args.  */
