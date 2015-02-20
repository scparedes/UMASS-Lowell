/*********************************************************/
/* Programmer: Santiago Paredes                          */
/*                                                       */
/* Project 1: Poker Game                                 */
/*********************************************************/ 


This README file describes the thought-process and syntactical/semantic idiosyncrasies of the implementation of my poker program.  It also reports the initial results and errors of the program, and it contains feedback from a friend with respect to the playability and interface of the program itself.



===========================================================
| PART 1: Client code, class design, and implementation   | 
===========================================================

-----------------------
|     Card Class      |
-----------------------

The card class was particularly easy to design, most certainly because we were provided with the basic structure and strategy for creating card objects.  I overloaded the less than and face-value equivalence operators, and I also made an overloading operator for the comparison of suits (which was useful for detecting a flush). These comparison operators were essential for sorting, which was the back-bone strategy of organizing the structure and implementation of my Hand Class.  The equivalence operator was used in the Hand Class to ensure proper deletion or discard of unwanted cards from the hand.

I indexed cards with a positive offset of 1 for convenience when accessing and processing point accumulation.  Also, whenever an Ace was accessed, I converted its value from 1 to 14, so that in hand evaluations, it was always considered a high card (except with a straight that began with an Ace).

-----------------------
| Deck of Cards Class |
-----------------------

Deck of Cards was a container for holding cards.  For a brief period of time, I considered making the Hand Class derive from the Deck of Cards Class.  The decision was ultimately to separate the two classes. 

Deck of Cards creates a full deck of cards (for every suit, create 13 faces).  It relies on the client code in main() to call the shuffle function for it.  A basic index called m_currentCard kept track of the card that will be dealt for every deal.  

-----------------------
|     Hand Class      |
-----------------------

Originally, I planned on representing a hand with only a vector of cards, but when I decided that a hand should be not only a container for cards, but also a structure that is also aware of its contents, I decided to create the Hand Class.

The implementation of Hand is completely dependent upon the sorting of cards, and so I used overloaded comparison operators in the Card Class to achieve this.  Instead of taking an approach where Hand is aware of its "good" cards (the cards that constitute a pair, three of a kind, royal flush, etc.), I decided to make Hand aware of the cards that were the least beneficial to the player.  Therefore, Hand contains a vector called m_undesiredCards which contained the index of the least beneficial cards in the hand.  Then those cards were removed from the m_cards hand based upon their equivalence to the cards in the temporary target vector.

Each hand type has checked exhaustively.  This was done because a hand could contain at most 5 cards, so as far as performance was concerned, I wasn't overly worried.  A pointer to an integer called 'extra' was passed as an argument to all but one of the hand-evaluating functions.  This 'extra' variable was used to keep track of the highest valued card involved in making a poker hand.  

The logic for deciding which cards are least valuable was almost completely based on face value.  Therefore, the dealer makes no decisions based on suit, thereby almost completely eliminating the strategic acquiring of a flush.

-----------------------
|    Player Class     |
-----------------------

The Player Class was created to basically only contain the ability to hold a hand.  Most of its other functions were simply straight calls to Hand Class functions.  
-----------------------
|   poker.cc (main)   |
-----------------------

This was the program driver.  The essential pieces of this program were parsing the input, maintaining the proper order of play in the game, and deciding which player won the game.

For user input, I ensured in my Hand Class that players could not try to discard more than 3 cards.  If they tried to do otherwise, I simply allowed them to only discard the first of the cards that they listed.

The winner was decided through a simple point system.  First off, a player's hand carried the most weight, so a poker hand awarded each player with some ordered number in the thousands.  Then, the 'extra' variables were used to keep track of the highest valued card involved in making a poker hand.  This number was multiplied by 10.  In this way, the 'extra' value of a hand could not outweigh the base value of another poker hand, unless two players had two of the same types of poker hands.  Lastly, the dealers high card was taken into account, so that it could not outweigh the value of the poker hand + the extra value, unless two players had the same types of poker hands with the same extra values.



===========================================================
| PART 2: Bugs, game play, a friend's feedback             | 
===========================================================

When I initially completed the program, there were some basic bugs within my logic for creating poker hands.  Without delving too much into unnecessary details, the biggest issue was deciding whether or not I would pair the three-of-a-kind function with the two-of-a-kind function to synthesize a full house function, thereby avoiding the implementation of a full house function all together.  This plan backfired, and was ultimately avoided by creating a separate full house function.  

When I played my poker game, I immediately became annoyed with the cluttered buffer that lay before my eyes each time I initiated a game.  My solution was to use the system("clear") function to clear the terminal and start fresh for every instantiation of a new poker game.  

The only person around to play my poker game was someone who was not familiar with the game of poker.  After a quick crash course, she picked up the rules fairly quickly and thoroughly enjoyed the game.  I believe it's because of the instantaneous nature of the game when it is purely digital, and requires no actual shuffling or waiting on other players' decisions at all.  But my friend insisted that players be explicitly told what kinds of poker hands they had.  When I added that feature, she was very pleased, and reportedly said that my "poker game would be great for teaching people new to the game how to play."  These were encouraging words.

I also changed some of the prompts and output to convey more concise and clear messages to the user.  

I ran 50 simulations.  20 on myself, 20 on my friend, and 10 open hand simulations.  There were some peculiar, inexplicable errors in 5 of the 50 simulations I did.  I still have not quite figured out what went wrong, but for the most part, it seems that my new logic in the Hand Class fixed the issues.  Issues included the dealer senselessly discarding cards that were constituents of a good hand, and also misevaluations of the player who had the better hand.  To see these odd results, search '????' to locate the exact instances of these oddities.  



===========================================================
| PART 3: Game results (My, Alicia's, Open-Hand)          | 
===========================================================


=======================================================
|                   My Results                        |
=======================================================

====================================
Simulation 1
====================================

Your hand:
1)  Ace of Spades
2)  3 of Hearts
3)  7 of Spades
4)  9 of Spades
5)  King of Spades

Which cards would you like to discard? (separate input by space, 3 cards max)
2
Your hand:
1)  Ace of Spades
2)  3 of Clubs
3)  7 of Spades
4)  9 of Spades
5)  King of Spades

Dealer's Hand:
1)  2 of Spades
2)  3 of Spades
3)  7 of Hearts
4)  Jack of Hearts
5)  King of Clubs

The winner is YOU!

====================================
Simulation 2
====================================

Your hand:
1)  Ace of Clubs
2)  3 of Spades
3)  8 of Hearts
4)  9 of Spades
5)  10 of Diamonds

Which cards would you like to discard? (separate input by space, 3 cards max)
1 2
Your hand:
1)  5 of Clubs
2)  7 of Clubs
3)  8 of Hearts
4)  9 of Spades
5)  10 of Diamonds

Dealer's Hand:
1)  Ace of Diamonds
2)  7 of Hearts
3)  10 of Hearts
4)  Queen of Spades
5)  Queen of Diamonds

The winner is the dealer.

====================================
Simulation 3 ????
====================================

Your hand:
1)  Ace of Diamonds
2)  3 of Diamonds
3)  5 of Spades
4)  5 of Hearts
5)  8 of Diamonds

Which cards would you like to discard? (separate input by space, 3 cards max)
2 7
Your hand:
1)  Ace of Diamonds
2)  2 of Clubs
3)  5 of Spades
4)  5 of Hearts
5)  8 of Diamonds

Dealer's Hand:
1)  8 of Hearts
2)  9 of Hearts
3)  Queen of Hearts
4)  King of Spades
5)  King of Clubs

The winner is the dealer.

====================================
Simulation 4
====================================

Your hand:
1)  Ace of Hearts
2)  3 of Clubs
3)  8 of Clubs
4)  10 of Diamonds
5)  Queen of Diamonds

Which cards would you like to discard? (separate input by space, 3 cards max)
2 3 4
Your hand:
1)  Ace of Hearts
2)  2 of Hearts
3)  6 of Spades
4)  7 of Spades
5)  Queen of Diamonds

Dealer's Hand:
1)  4 of Hearts
2)  4 of Diamonds
3)  5 of Diamonds
4)  Queen of Spades
5)  Queen of Hearts

The winner is the dealer.

====================================
Simulation 5
====================================

Your hand:
1)  Ace of Hearts
2)  5 of Spades
3)  6 of Spades
4)  10 of Spades
5)  King of Spades

Which cards would you like to discard? (separate input by space, 3 cards max)
2 3 4
Your hand:
1)  Ace of Hearts
2)  2 of Spades
3)  4 of Diamonds
4)  7 of Clubs
5)  King of Spades

Dealer's Hand:
1)  6 of Hearts
2)  6 of Clubs
3)  10 of Diamonds
4)  10 of Clubs
5)  Queen of Spades

The winner is the dealer.

====================================
Simulation 6
====================================

Your hand:
1)  Ace of Spades
2)  2 of Spades
3)  3 of Diamonds
4)  3 of Spades
5)  Queen of Clubs

Which cards would you like to discard? (separate input by space, 3 cards max)
2 5
Your hand:
1)  Ace of Spades
2)  2 of Clubs
3)  3 of Spades
4)  3 of Hearts
5)  3 of Diamonds

Dealer's Hand:
1)  Ace of Hearts
2)  4 of Clubs
3)  9 of Hearts
4)  9 of Diamonds
5)  9 of Clubs

The winner is the dealer.

====================================
Simulation 7
====================================

Your hand:
1)  2 of Spades
2)  5 of Clubs
3)  6 of Spades
4)  Queen of Diamonds
5)  King of Diamonds

Which cards would you like to discard? (separate input by space, 3 cards max)
1 2 3
Your hand:
1)  Ace of Hearts
2)  5 of Hearts
3)  7 of Diamonds
4)  Queen of Diamonds
5)  King of Diamonds

Dealer's Hand:
1)  7 of Spades
2)  9 of Diamonds
3)  10 of Hearts
4)  Jack of Spades
5)  King of Hearts

The winner is YOU!

====================================
Simulation 8
====================================

Your hand:
1)  Ace of Clubs
2)  3 of Diamonds
3)  5 of Spades
4)  9 of Clubs
5)  Queen of Clubs

Which cards would you like to discard? (separate input by space, 3 cards max)
2 3 4
Your hand:
1)  Ace of Clubs
2)  2 of Diamonds
3)  8 of Diamonds
4)  Jack of Clubs
5)  Queen of Clubs

Dealer's Hand:
1)  4 of Clubs
2)  6 of Hearts
3)  8 of Hearts
4)  10 of Spades
5)  10 of Diamonds

The winner is the dealer.

====================================
Simulation 9
====================================

Your hand:
1)  2 of Spades
2)  5 of Spades
3)  6 of Hearts
4)  6 of Clubs
5)  Queen of Clubs

Which cards would you like to discard? (separate input by space, 3 cards max)
1 2
Your hand:
1)  6 of Hearts
2)  6 of Clubs
3)  7 of Hearts
4)  Jack of Spades
5)  Queen of Clubs

Dealer's Hand:
1)  Ace of Hearts
2)  3 of Hearts
3)  7 of Diamonds
4)  Queen of Diamonds
5)  King of Spades

The winner is YOU!

====================================
Simulation 10 ????
====================================

Your hand:
1)  Ace of Diamonds
2)  2 of Clubs
3)  7 of Spades
4)  8 of Clubs
5)  Jack of Clubs

Which cards would you like to discard? (separate input by space, 3 cards max)
2 3 4
Your hand:
1)  Ace of Diamonds
2)  3 of Spades
3)  8 of Spades
4)  9 of Hearts
5)  Jack of Clubs

Dealer's Hand:
1)  Ace of Clubs
2)  3 of Diamonds
3)  6 of Hearts
4)  9 of Diamonds
5)  King of Diamonds

The winner is the dealer.

====================================
Simulation 11
====================================

Your hand:
1)  2 of Diamonds
2)  4 of Hearts
3)  5 of Clubs
4)  6 of Diamonds
5)  King of Spades

Which cards would you like to discard? (separate input by space, 3 cards max)
5
Your hand:
1)  2 of Diamonds
2)  3 of Clubs
3)  4 of Hearts
4)  5 of Clubs
5)  6 of Diamonds

Dealer's Hand:
1)  Ace of Hearts
2)  8 of Clubs
3)  Queen of Clubs
4)  King of Hearts
5)  King of Clubs

The winner is YOU!

====================================
Simulation 12
====================================

Your hand:
1)  3 of Hearts
2)  5 of Spades
3)  8 of Spades
4)  9 of Diamonds
5)  Queen of Clubs

Which cards would you like to discard? (separate input by space, 3 cards max)
1 2 3
Your hand:
1)  3 of Clubs
2)  5 of Clubs
3)  7 of Diamonds
4)  9 of Diamonds
5)  Queen of Clubs

Dealer's Hand:
1)  7 of Clubs
2)  9 of Hearts
3)  10 of Diamonds
4)  10 of Clubs
5)  Queen of Hearts

The winner is the dealer.

====================================
Simulation 13
====================================

Your hand:
1)  Ace of Hearts
2)  5 of Hearts
3)  7 of Spades
4)  9 of Diamonds
5)  King of Diamonds

Which cards would you like to discard? (separate input by space, 3 cards max)
2 3 4
Your hand:
1)  Ace of Hearts
2)  3 of Spades
3)  Jack of Clubs
4)  Queen of Clubs
5)  King of Diamonds

Dealer's Hand:
1)  2 of Spades
2)  6 of Spades
3)  7 of Clubs
4)  10 of Diamonds
5)  Queen of Hearts

The winner is YOU!

====================================
Simulation 14
====================================

Your hand:
1)  4 of Clubs
2)  6 of Clubs
3)  7 of Diamonds
4)  10 of Clubs
5)  Jack of Clubs

Which cards would you like to discard? (separate input by space, 3 cards max)
1 2 3
Your hand:
1)  Ace of Clubs
2)  8 of Spades
3)  8 of Hearts
4)  10 of Clubs
5)  Jack of Clubs

Dealer's Hand:
1)  5 of Clubs
2)  9 of Diamonds
3)  10 of Hearts
4)  Queen of Spades
5)  King of Clubs

The winner is YOU!

====================================
Simulation 15
====================================

Your hand:
1)  Ace of Clubs
2)  Ace of Diamonds
3)  4 of Hearts
4)  5 of Diamonds
5)  6 of Clubs

Which cards would you like to discard? (separate input by space, 3 cards max)
5
Your hand:
1)  Ace of Diamonds
2)  Ace of Clubs
3)  4 of Hearts
4)  5 of Spades
5)  5 of Diamonds

Dealer's Hand:
1)  2 of Hearts
2)  2 of Diamonds
3)  9 of Hearts
4)  10 of Spades
5)  Queen of Diamonds

The winner is YOU!

====================================
Simulation 16
====================================

Your hand:
1)  3 of Hearts
2)  3 of Spades
3)  8 of Spades
4)  9 of Diamonds
5)  Jack of Hearts

Which cards would you like to discard? (separate input by space, 3 cards max)
3
Your hand:
1)  3 of Spades
2)  3 of Hearts
3)  9 of Hearts
4)  9 of Diamonds
5)  Jack of Hearts

Dealer's Hand:
1)  Ace of Hearts
2)  Ace of Clubs
3)  6 of Diamonds
4)  9 of Spades
5)  9 of Clubs

The winner is the dealer.

====================================
Simulation 17
====================================

Your hand:
1)  Ace of Clubs
2)  5 of Hearts
3)  5 of Spades
4)  6 of Clubs
5)  10 of Hearts

Which cards would you like to discard? (separate input by space, 3 cards max)
4 5
Your hand:
1)  Ace of Clubs
2)  5 of Spades
3)  5 of Hearts
4)  7 of Diamonds
5)  King of Spades

Dealer's Hand:
1)  3 of Clubs
2)  7 of Spades
3)  9 of Clubs
4)  Jack of Hearts
5)  Queen of Spades

The winner is YOU!

====================================
Simulation 18
====================================

Your hand:
1)  2 of Clubs
2)  3 of Diamonds
3)  5 of Spades
4)  6 of Spades
5)  7 of Spades

Which cards would you like to discard? (separate input by space, 3 cards max)
2 3
Your hand:
1)  2 of Clubs
2)  6 of Spades
3)  7 of Spades
4)  8 of Spades
5)  9 of Diamonds

Dealer's Hand:
1)  3 of Spades
2)  5 of Clubs
3)  6 of Clubs
4)  9 of Clubs
5)  Queen of Diamonds

The winner is the dealer.

====================================
Simulation 19 ????
====================================

Your hand:
1)  Ace of Diamonds
2)  2 of Hearts
3)  3 of Diamonds
4)  4 of Clubs
5)  6 of Diamonds

Which cards would you like to discard? (separate input by space, 3 cards max)
1
Your hand:
1)  Ace of Hearts
2)  2 of Hearts
3)  3 of Diamonds
4)  4 of Clubs
5)  6 of Diamonds

Dealer's Hand:
1)  6 of Clubs
2)  9 of Spades
3)  10 of Spades
4)  Queen of Spades
5)  King of Hearts

The winner is the dealer.

====================================
Simulation 20
====================================

Your hand:
1)  Ace of Clubs
2)  3 of Hearts
3)  7 of Spades
4)  10 of Spades
5)  King of Diamonds

Which cards would you like to discard? (separate input by space, 3 cards max)
2 3
Your hand:
1)  Ace of Hearts
2)  Ace of Clubs
3)  3 of Spades
4)  10 of Spades
5)  King of Diamonds

Dealer's Hand:
1)  5 of Hearts
2)  7 of Clubs
3)  9 of Hearts
4)  10 of Hearts
5)  Jack of Clubs

The winner is YOU!

=======================================================
|                  Alicia's Results                   |
=======================================================

====================================
Simulation 1
====================================

Your hand:
1)  3 of Diamonds
2)  4 of Spades
3)  4 of Hearts
4)  6 of Hearts
5)  Jack of Clubs

Which cards would you like to discard? (separate input by space, 3 cards max)
1 4 5
Your hand:
1)  2 of Diamonds
2)  4 of Spades
3)  4 of Hearts
4)  5 of Diamonds
5)  10 of Clubs

Dealer's Hand:
1)  6 of Diamonds
2)  9 of Clubs
3)  10 of Hearts
4)  King of Hearts
5)  King of Diamonds

The winner is the dealer.

====================================
Simulation 2
====================================

Your hand:
1)  3 of Clubs
2)  4 of Clubs
3)  6 of Diamonds
4)  10 of Hearts
5)  Jack of Clubs

Which cards would you like to discard? (separate input by space, 3 cards max)
3 4
Your hand:
1)  3 of Clubs
2)  4 of Clubs
3)  5 of Hearts
4)  6 of Spades
5)  Jack of Clubs

Dealer's Hand:
1)  3 of Hearts
2)  3 of Diamonds
3)  8 of Hearts
4)  Jack of Hearts
5)  Queen of Spades

The winner is the dealer.

====================================
Simulation 3
====================================

Your hand:
1)  5 of Clubs
2)  6 of Hearts
3)  8 of Spades
4)  9 of Diamonds
5)  Jack of Spades

Which cards would you like to discard? (separate input by space, 3 cards max)
5
Your hand:
1)  5 of Hearts
2)  5 of Clubs
3)  6 of Hearts
4)  8 of Spades
5)  9 of Diamonds

Dealer's Hand:
1)  2 of Spades
2)  2 of Hearts
3)  6 of Diamonds
4)  6 of Clubs
5)  Jack of Hearts

The winner is the dealer.

====================================
Simulation 4
====================================

Your hand:
1)  6 of Spades
2)  8 of Spades
3)  10 of Clubs
4)  Queen of Spades
5)  Queen of Hearts

Which cards would you like to discard? (separate input by space, 3 cards max)
1 2 3
Your hand:
1)  3 of Hearts
2)  4 of Clubs
3)  5 of Hearts
4)  Queen of Spades
5)  Queen of Hearts

Dealer's Hand:
1)  2 of Spades
2)  6 of Hearts
3)  9 of Hearts
4)  King of Hearts
5)  King of Clubs

The winner is the dealer.

====================================
Simulation 5
====================================

Your hand:
1)  2 of Hearts
2)  5 of Diamonds
3)  6 of Hearts
4)  8 of Hearts
5)  8 of Spades

Which cards would you like to discard? (separate input by space, 3 cards max)
1 2 3 
Your hand:
1)  3 of Hearts
2)  5 of Spades
3)  8 of Spades
4)  8 of Hearts
5)  9 of Spades

Dealer's Hand:
1)  7 of Spades
2)  8 of Clubs
3)  10 of Clubs
4)  King of Spades
5)  King of Hearts

The winner is the dealer.

====================================
Simulation 6
====================================

Your hand:
1)  4 of Clubs
2)  4 of Spades
3)  6 of Spades
4)  9 of Spades
5)  King of Hearts

Which cards would you like to discard? (separate input by space, 3 cards max)
3 4
Your hand:
1)  4 of Spades
2)  4 of Clubs
3)  Jack of Diamonds
4)  King of Spades
5)  King of Hearts

Dealer's Hand:
1)  5 of Diamonds
2)  8 of Diamonds
3)  9 of Hearts
4)  10 of Clubs
5)  Jack of Hearts

The winner is YOU!

====================================
Simulation 7
====================================

Your hand:
1)  2 of Diamonds
2)  3 of Hearts
3)  4 of Clubs
4)  6 of Hearts
5)  Jack of Clubs

Which cards would you like to discard? (separate input by space, 3 cards max)
5   
Your hand:
1)  2 of Diamonds
2)  3 of Hearts
3)  4 of Clubs
4)  6 of Hearts
5)  10 of Hearts

Dealer's Hand:
1)  Ace of Diamonds
2)  2 of Spades
3)  9 of Spades
4)  Jack of Diamonds
5)  Queen of Diamonds

The winner is the dealer.

====================================
Simulation 8
====================================

Your hand:
1)  4 of Spades
2)  5 of Hearts
3)  8 of Clubs
4)  9 of Hearts
5)  9 of Spades

Which cards would you like to discard? (separate input by space, 3 cards max)
1 2 3
Your hand:
1)  Ace of Hearts
2)  7 of Spades
3)  9 of Spades
4)  9 of Hearts
5)  10 of Spades

Dealer's Hand:
1)  2 of Spades
2)  4 of Diamonds
3)  Jack of Hearts
4)  Queen of Clubs
5)  King of Clubs

The winner is YOU!

====================================
Simulation 9
====================================

Your hand:
1)  4 of Diamonds
2)  5 of Spades
3)  5 of Clubs
4)  8 of Spades
5)  10 of Clubs

Which cards would you like to discard? (separate input by space, 3 cards max)
1 4 5
Your hand:
1)  Ace of Hearts
2)  3 of Diamonds
3)  5 of Spades
4)  5 of Clubs
5)  9 of Hearts

Dealer's Hand:
1)  Ace of Diamonds
2)  3 of Spades
3)  7 of Hearts
4)  9 of Diamonds
5)  Queen of Clubs

The winner is YOU!

====================================
Simulation 10
====================================

Your hand:
1)  4 of Spades
2)  5 of Clubs
3)  9 of Diamonds
4)  10 of Diamonds
5)  Queen of Clubs

Which cards would you like to discard? (separate input by space, 3 cards max)
1 2 3
Your hand:
1)  Ace of Clubs
2)  7 of Spades
3)  7 of Hearts
4)  10 of Diamonds
5)  Queen of Clubs

Dealer's Hand:
1)  Ace of Spades
2)  8 of Diamonds
3)  9 of Clubs
4)  10 of Clubs
5)  Jack of Hearts

The winner is YOU!

====================================
Simulation 11
====================================

Your hand:
1)  6 of Clubs
2)  8 of Diamonds
3)  8 of Hearts
4)  Queen of Hearts
5)  Queen of Spades

Which cards would you like to discard? (separate input by space, 3 cards max)
1
Your hand:
1)  8 of Hearts
2)  8 of Diamonds
3)  Jack of Spades
4)  Queen of Spades
5)  Queen of Hearts

Dealer's Hand:
1)  Ace of Spades
2)  2 of Hearts
3)  4 of Spades
4)  6 of Hearts
5)  7 of Diamonds

The winner is YOU!

====================================
Simulation 12
====================================

Your hand:
1)  2 of Clubs
2)  2 of Hearts
3)  Jack of Spades
4)  Queen of Diamonds
5)  King of Hearts

Which cards would you like to discard? (separate input by space, 3 cards max)
3 4
Your hand:
1)  2 of Hearts
2)  2 of Clubs
3)  9 of Spades
4)  Jack of Hearts
5)  King of Hearts

Dealer's Hand:
1)  Ace of Spades
2)  2 of Spades
3)  7 of Spades
4)  Jack of Diamonds
5)  Queen of Hearts

The winner is YOU!

====================================
Simulation 13
====================================

Your hand:
1)  3 of Clubs
2)  5 of Clubs
3)  9 of Spades
4)  9 of Hearts
5)  King of Hearts

Which cards would you like to discard? (separate input by space, 3 cards max)
1 2
Your hand:
1)  2 of Hearts
2)  9 of Spades
3)  9 of Hearts
4)  Jack of Hearts
5)  King of Hearts

Dealer's Hand:
1)  2 of Diamonds
2)  4 of Spades
3)  4 of Hearts
4)  10 of Hearts
5)  10 of Clubs

The winner is the dealer.

====================================
Simulation 14
====================================

Your hand:
1)  2 of Spades
2)  3 of Hearts
3)  6 of Spades
4)  Jack of Diamonds
5)  King of Spades

Which cards would you like to discard? (separate input by space, 3 cards max)
2 4
Your hand:
1)  2 of Spades
2)  4 of Clubs
3)  6 of Spades
4)  King of Spades
5)  King of Diamonds

Dealer's Hand:
1)  Ace of Spades
2)  3 of Clubs
3)  6 of Diamonds
4)  9 of Clubs
5)  10 of Hearts

The winner is YOU!

====================================
Simulation 15
====================================

Your hand:
1)  3 of Clubs
2)  3 of Spades
3)  4 of Clubs
4)  6 of Hearts
5)  Jack of Hearts

Which cards would you like to discard? (separate input by space, 3 cards max)
3 4 5
Your hand:
1)  3 of Spades
2)  3 of Clubs
3)  5 of Spades
4)  5 of Diamonds
5)  Jack of Spades

Dealer's Hand:
1)  Ace of Diamonds
2)  2 of Hearts
3)  4 of Spades
4)  4 of Diamonds
5)  King of Spades

The winner is YOU!

====================================
Simulation 16
====================================

Your hand:
1)  Ace of Diamonds
2)  5 of Diamonds
3)  10 of Spades
4)  10 of Diamonds
5)  Jack of Hearts

Which cards would you like to discard? (separate input by space, 3 cards max)
2 5  
Your hand:
1)  Ace of Diamonds
2)  3 of Diamonds
3)  4 of Hearts
4)  10 of Spades
5)  10 of Diamonds

Dealer's Hand:
1)  Ace of Hearts
2)  2 of Spades
3)  4 of Diamonds
4)  9 of Hearts
5)  King of Clubs

The winner is YOU!

====================================
Simulation 17
====================================

Your hand:
1)  3 of Spades
2)  5 of Diamonds
3)  5 of Clubs
4)  Queen of Diamonds
5)  Queen of Hearts

Which cards would you like to discard? (separate input by space, 3 cards max)
1
Your hand:
1)  5 of Diamonds
2)  5 of Clubs
3)  8 of Hearts
4)  Queen of Hearts
5)  Queen of Diamonds

Dealer's Hand:
1)  Ace of Spades
2)  5 of Spades
3)  7 of Hearts
4)  9 of Diamonds
5)  King of Diamonds

The winner is YOU!

====================================
Simulation 18
====================================

Your hand:
1)  Ace of Clubs
2)  Ace of Diamonds
3)  2 of Diamonds
4)  8 of Spades
5)  Jack of Diamonds

Which cards would you like to discard? (separate input by space, 3 cards max)
3 4 5
Your hand:
1)  Ace of Diamonds
2)  Ace of Clubs
3)  4 of Spades
4)  6 of Hearts
5)  Jack of Hearts

Dealer's Hand:
1)  5 of Clubs
2)  7 of Hearts
3)  8 of Diamonds
4)  Queen of Diamonds
5)  King of Spades

The winner is YOU!

====================================
Simulation 19
====================================

Your hand:
1)  5 of Spades
2)  6 of Diamonds
3)  6 of Clubs
4)  7 of Hearts
5)  9 of Spades

Which cards would you like to discard? (separate input by space, 3 cards max)
1 4 5
Your hand:
1)  3 of Clubs
2)  6 of Diamonds
3)  6 of Clubs
4)  7 of Spades
5)  Jack of Diamonds

Dealer's Hand:
1)  2 of Spades
2)  2 of Clubs
3)  6 of Spades
4)  8 of Spades
5)  10 of Spades

The winner is YOU!

====================================
Simulation 20
====================================

Your hand:
1)  3 of Clubs
2)  4 of Spades
3)  10 of Spades
4)  Jack of Clubs
5)  Queen of Diamonds

Which cards would you like to discard? (separate input by space, 3 cards max)
1 2 3
Your hand:
1)  4 of Clubs
2)  9 of Spades
3)  9 of Hearts
4)  Jack of Clubs
5)  Queen of Diamonds

Dealer's Hand:
1)  7 of Spades
2)  8 of Spades
3)  9 of Diamonds
4)  Queen of Clubs
5)  King of Hearts

The winner is YOU!


=======================================================
|                  Open-Hand Results                  |
=======================================================

====================================
Simulation 1
====================================

Dealer's hand
1)  Ace of Diamonds
2)  2 of Diamonds
3)  5 of Clubs
4)  7 of Diamonds
5)  Jack of Clubs

Your hand:
1)  3 of Clubs
2)  7 of Hearts
3)  7 of Clubs
4)  8 of Hearts
5)  8 of Diamonds

Which cards would you like to discard? (separate input by space, 3 cards max)
3
Your hand:
1)  3 of Clubs
2)  7 of Hearts
3)  8 of Spades
4)  8 of Hearts
5)  8 of Diamonds

Dealer's Hand:
1)  Ace of Diamonds
2)  7 of Diamonds
3)  8 of Clubs
4)  Jack of Diamonds
5)  Jack of Clubs

The winner is YOU!

====================================
Simulation 2
====================================

Dealer's hand
1)  Ace of Spades
2)  2 of Hearts
3)  6 of Diamonds
4)  8 of Clubs
5)  10 of Spades

Your hand:
1)  3 of Hearts
2)  7 of Spades
3)  10 of Hearts
4)  Queen of Diamonds
5)  King of Clubs

Which cards would you like to discard? (separate input by space, 3 cards max)
1 2
Your hand:
1)  Ace of Hearts
2)  5 of Clubs
3)  10 of Hearts
4)  Queen of Diamonds
5)  King of Clubs

Dealer's Hand:
1)  Ace of Spades
2)  8 of Clubs
3)  9 of Clubs
4)  10 of Spades
5)  Queen of Spades

The winner is YOU!

====================================
Simulation 3 ????
====================================

Dealer's hand
1)  2 of Clubs
2)  2 of Diamonds
3)  3 of Hearts
4)  4 of Hearts
5)  King of Hearts

Your hand:
1)  7 of Diamonds
2)  8 of Diamonds
3)  9 of Clubs
4)  9 of Hearts
5)  Queen of Diamonds

Which cards would you like to discard? (separate input by space, 3 cards max)
1 2
Your hand:
1)  5 of Clubs
2)  9 of Hearts
3)  9 of Clubs
4)  Queen of Spades
5)  Queen of Diamonds

Dealer's Hand:
1)  2 of Hearts
2)  2 of Diamonds
3)  2 of Clubs
4)  9 of Diamonds
5)  Queen of Clubs

The winner is the dealer.

====================================
Simulation 4
====================================

Dealer's hand
1)  Ace of Spades
2)  2 of Spades
3)  5 of Clubs
4)  10 of Clubs
5)  10 of Hearts

Your hand:
1)  3 of Hearts
2)  5 of Diamonds
3)  7 of Clubs
4)  9 of Spades
5)  Jack of Hearts

Which cards would you like to discard? (separate input by space, 3 cards max)
1 2 3
Your hand:
1)  4 of Diamonds
2)  8 of Clubs
3)  9 of Spades
4)  Jack of Hearts
5)  Queen of Clubs

Dealer's Hand:
1)  5 of Spades
2)  8 of Spades
3)  8 of Diamonds
4)  10 of Hearts
5)  10 of Clubs

The winner is the dealer.

====================================
Simulation 5
====================================

Dealer's hand
1)  Ace of Clubs
2)  4 of Hearts
3)  6 of Diamonds
4)  7 of Clubs
5)  8 of Clubs

Your hand:
1)  Ace of Hearts
2)  2 of Spades
3)  9 of Clubs
4)  10 of Diamonds
5)  King of Hearts

Which cards would you like to discard? (separate input by space, 3 cards max)
2 3 4
Your hand:
1)  Ace of Hearts
2)  9 of Spades
3)  10 of Clubs
4)  Jack of Clubs
5)  King of Hearts

Dealer's Hand:
1)  Ace of Clubs
2)  5 of Clubs
3)  7 of Clubs
4)  8 of Hearts
5)  8 of Clubs

The winner is the dealer.

====================================
Simulation 6 ????
====================================

Dealer's hand
1)  2 of Hearts
2)  5 of Hearts
3)  9 of Hearts
4)  9 of Spades
5)  Queen of Clubs

Your hand:
1)  Ace of Diamonds
2)  Ace of Clubs
3)  9 of Clubs
4)  10 of Spades
5)  King of Diamonds

Which cards would you like to discard? (separate input by space, 3 cards max)
3 4
Your hand:
1)  Ace of Diamonds
2)  Ace of Clubs
3)  7 of Diamonds
4)  Queen of Spades
5)  King of Diamonds

Dealer's Hand:
1)  Ace of Hearts
2)  9 of Spades
3)  9 of Hearts
4)  Queen of Diamonds
5)  King of Clubs

The winner is YOU!

====================================
Simulation 7
====================================

Dealer's hand
1)  Ace of Hearts
2)  2 of Clubs
3)  4 of Hearts
4)  7 of Clubs
5)  Jack of Hearts

Your hand:
1)  5 of Clubs
2)  5 of Hearts
3)  8 of Spades
4)  Queen of Diamonds
5)  King of Spades

Which cards would you like to discard? (separate input by space, 3 cards max)
3 
Your hand:
1)  5 of Hearts
2)  5 of Clubs
3)  Queen of Diamonds
4)  Queen of Clubs
5)  King of Spades

Dealer's Hand:
1)  Ace of Hearts
2)  3 of Spades
3)  7 of Clubs
4)  10 of Diamonds
5)  Jack of Hearts

The winner is YOU!

====================================
Simulation 8
====================================

Dealer's hand
1)  2 of Hearts
2)  8 of Spades
3)  8 of Hearts
4)  10 of Diamonds
5)  King of Clubs

Your hand:
1)  Ace of Clubs
2)  2 of Diamonds
3)  5 of Spades
4)  7 of Spades
5)  7 of Diamonds

Which cards would you like to discard? (separate input by space, 3 cards max)
2 3
Your hand:
1)  Ace of Clubs
2)  5 of Hearts
3)  7 of Spades
4)  7 of Hearts
5)  7 of Diamonds

Dealer's Hand:
1)  6 of Spades
2)  8 of Spades
3)  8 of Hearts
4)  8 of Clubs
5)  Jack of Spades

The winner is the dealer.

====================================
Simulation 9
====================================

Dealer's hand
1)  Ace of Hearts
2)  6 of Clubs
3)  7 of Spades
4)  8 of Clubs
5)  King of Spades

Your hand:
1)  5 of Spades
2)  6 of Diamonds
3)  10 of Spades
4)  10 of Diamonds
5)  Jack of Clubs

Which cards would you like to discard? (separate input by space, 3 cards max)
1 2
Your hand:
1)  6 of Hearts
2)  8 of Spades
3)  10 of Spades
4)  10 of Diamonds
5)  Jack of Clubs

Dealer's Hand:
1)  Ace of Hearts
2)  7 of Spades
3)  8 of Clubs
4)  Jack of Hearts
5)  King of Spades

The winner is YOU!

====================================
Simulation 10
====================================

Dealer's hand
1)  2 of Hearts
2)  4 of Spades
3)  8 of Hearts
4)  9 of Clubs
5)  Queen of Hearts

Your hand:
1)  4 of Hearts
2)  5 of Diamonds
3)  9 of Diamonds
4)  10 of Diamonds
5)  King of Diamonds

Which cards would you like to discard? (separate input by space, 3 cards max)
1
Your hand:
1)  4 of Diamonds
2)  5 of Diamonds
3)  9 of Diamonds
4)  10 of Diamonds
5)  King of Diamonds

Dealer's Hand:
1)  8 of Hearts
2)  9 of Hearts
3)  9 of Clubs
4)  Jack of Spades
5)  Queen of Hearts

The winner is YOU!
