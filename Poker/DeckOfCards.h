/*********************************************************/
/* Programmer: Santiago Paredes                          */
/*                                                       */
/* Project 1: Poker Game (DeckOfCards.h)                 */
/*********************************************************/ 

#ifndef __DECKOFCARDS_H__
#define __DECKOFCARDS_H__

#include <string>
#include <vector>

#include "Card.h"

class DeckOfCards
{
 public:
  DeckOfCards();
  const Card& deal();
  void dumpDeck() const; // This function is for debugging purposes.
  bool moreCards() const; // In this particular poker game, this function is unused.
  void shuffle();

 private:
  std::vector<Card> m_deck;
  size_t m_currentCard; // To keep track of the card that is to be dealt.
};

inline const Card& DeckOfCards::deal()
{
  return m_deck[m_currentCard++];
}

inline bool DeckOfCards::moreCards() const
{
  return m_currentCard < m_deck.size();
}

#endif
