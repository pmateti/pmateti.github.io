object Cards {
  sealed trait Suit
  case object Spades extends Suit
  case object Clubs extends Suit
  case object Hearts extends Suit
  case object Diamonds extends Suit

  sealed trait Rank
  trait FaceCard extends Rank

  case object Jack  extends FaceCard
  case object Queen extends FaceCard
  case object King  extends FaceCard
  case object Ace   extends FaceCard

  case class ValueCard(n: Int) extends Rank

  case class Card(rank: Rank, suit: Suit)

  type Deck = List[Card]

  def numberToRank(n: Int): Rank = n match {
    case 1 => Ace
    case x if x <= 10 => ValueCard(x)
    case 11 => Jack
    case 12 => Queen
    case 13 => King
    case _ => throw new IllegalArgumentException
  }

  def numberToSuit(n: Int): Suit = n match {
    case 0 => Spades
    case 1 => Clubs
    case 2 => Hearts
    case 3 => Diamonds
  }

  def apply(): Deck = (for(rank <- 1 to 13; suit <- 0 to 3) yield Card(numberToRank(rank), numberToSuit(suit))).to[List]
}


object Main extends App {
	println (Cards())
}