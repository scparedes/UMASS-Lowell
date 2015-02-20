/*********************************************************/
/* Programmer: Santiago Paredes                          */
/*                                                       */
/* Project 1: Poker Game (poker.cc)                      */
/*********************************************************/ 

#include <iostream>
#include <vector>
#include <string>
#include <ctype.h>
#include <cassert>
#include <iterator>
#include <sstream>
#include <cstdio>

#include "DeckOfCards.h"
#include "Player.h"

// Parses a line of input with spaces and puts the input back into the inputVector that was passed with it
bool parseLine(std::string line, std::vector<int> &inputVector) {

  std::vector<double> v;

  // Build an istream that holds the input string
  std::istringstream iss(line);

  // Iterate over the istream, using >> to grab ints
  // and push_back to store them in the vector
  std::copy(std::istream_iterator<int>(iss),
	    std::istream_iterator<int>(),
        back_inserter(inputVector));

  return true;
}

// Returns whether or not player2 beat player1.
int determineWinner(int player1, int player2) {
  
  return (player2 > player1);
}

// Returns what kind of hand the player had (this was a routine that my colleague suggested I add).
void printHandType(int points) {

  if (points > 10000)
    std::cout << "Royal Flush";
  else if (points > 9000)
    std::cout << "Four of a Kind";
  else if (points > 8000)
    std::cout << "Full House";
  else if (points > 7000)
    std::cout << "Flush";
  else if (points > 6000)
    std::cout << "Straight";
  else if (points > 5000)
    std::cout << "Three of a Kind";
  else if (points > 4000)
    std::cout << "Two Pair";
  else if (points > 3000)
    std::cout << "Pair";
  else {
    std::cout << "High Card";
  }
  
}

// Points are decided here.
int determinePoints(Player& player, int *extra) {
  
  if (player.getHand().hasFlush(extra)) {
    if (player.getHand().hasStraight(extra))
      return 10000; // Royal flush.
    return 7000;
  }
  else if (player.getHand().hasFourKind(extra))
    return 9000;
  else if (player.getHand().hasFullHouse(extra))
    return 8000;
  else if (player.getHand().hasStraight(extra))
    return 6000;
  else if (player.getHand().hasThreeKind(extra)) 
    return 5000;
  else if (player.getHand().hasTwoPair(extra))
    return 4000;
  else if (player.getHand().hasPair(extra))
    return 3000;
  else {
    player.getHand().setBadHand();
    return 0;
  }
}

int main(int argc, const char** argv)
{
  DeckOfCards deck;
  Player dealer, player;
  int dealerPoints, playerPoints;        // Keeps track of who's winning.
  int winner;                            // Stores who won the game.
  int playerExtra = 0, dealerExtra = 0;  // Keeps track of the highest valued card involved in making a poker hand.
  std::string line;                      // Stores user-input as a string.
  std::vector<int> v;                    // Holds the converted user-input's undesired cards.

  // Clear buffer.
  system("clear");

  std::cout << "=============================================\nSANTIAGO'S "<< 
    "POKER                            |\n=============================================\n" << std::endl;

  // Game begins.
  deck.shuffle();
  
  // Hands are dealt to player and dealer, respectively, and with alternation.
  for (size_t i = 0; i < Hand::szHand; i++) {
    if (!player.receiveCard(deck.deal())) {
      std::cout << "Error: Cannot add more cards to this hand." << std::endl; 
    }
    if (!dealer.receiveCard(deck.deal())) {
      std::cout << "Error: Cannot add more cards to this hand." << std::endl; 
    }
  }

  // NOTE: This commented code is for open-hand play.
  //  std::cout << "Dealer's hand" << std::endl;
  //  dealer.showHand();
  
  /*
    =================================================
    Player's poker hand analysis and decision-making
    =================================================
  */

  // Player is shown their hand.
  std::cout << "\nYour hand:" << std::endl;
  player.showHand();
  std::cout << std::endl;
  
  // Player is prompted to decide which cards he/she would like to discard.
  v.clear();
  std::cout << "Which cards would you like to discard (choose at most 3)? (Ex. 1 2 3)" << std::endl;
  getline(std::cin, line);

  // Those cards are parsed from string to int (int is the index of the card in their hand).
  parseLine(line, v);
  
  // The cards to be discarded are designated, and then discarded.
  player.addBadCards(v);
  player.discard();

  // Player is dealt as many cards as he discarded.
  while (player.getHand().getCards().size() < Hand::szHand)
    {
      player.receiveCard(deck.deal());
    }
  
  // The player's final score is calculated.
  playerPoints = player.getHand().getHighCard() + determinePoints(player, &playerExtra);
  playerPoints += (playerExtra * 10);

  /*
    =================================================
    Dealer's poker hand analysis and decision-making
    =================================================
  */

  // Dealer evaluates hand based upon the score he received on his original hand.
  dealerPoints = dealer.getHand().getHighCard() + determinePoints(dealer, &dealerExtra);

  // Based upon that evaluation, he discards unwanted cards.
  dealer.discard();
  
  // Dealer deals himself as many cards as he discarded.
  while (dealer.getHand().getCards().size() < Hand::szHand)
    {
      dealer.receiveCard(deck.deal());
    }

  // The dealer's final score is then calculated.
  dealerPoints = dealer.getHand().getHighCard() + determinePoints(dealer, &dealerExtra);
  dealerPoints += (dealerExtra * 10);

  // The players show each other their hands.
  std::cout << "Your hand:" << std::endl;
  player.showHand(); std::cout << std::endl;
  std::cout << "Dealer's Hand:" << std::endl;
  dealer.showHand(); std::cout << std::endl;

  // The winner is determined (whoever had the higher score).
  winner = determineWinner(dealerPoints, playerPoints);

  // Player's are explicitely told what kinds of poker hands they had.
  std::cout << "You had a ";
  printHandType(playerPoints);
  std::cout << "\nThe dealer had a ";
  printHandType(dealerPoints);

  // The winner is finally announced.
  if (winner == 1)
    std::cout << "\n\nYOU WON! YOU'RE A WINNER!\n"<< std::endl;
  else 
    std::cout << "\n\nYou...lost... :'(\n" << std::endl;    
  
  // End of program
  return 0;
}
