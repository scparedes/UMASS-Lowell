/*********************************************************/
/* Programmer: Santiago Paredes                          */
/*                                                       */
/* Project 1: Poker Game (DeckOfCards.cc)                */
/*********************************************************/ 

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include "DeckOfCards.h"

DeckOfCards::DeckOfCards()
  : m_currentCard(0)
{
  // Simple double for loop for initiating a card of every face and suit.
  for (size_t f = 1; f <= Card::s_FacesSz; ++f)
    {
      for (size_t s = 1; s <= Card::s_SuitsSz; ++s)
	{
	  Card c(f, s);
	  m_deck.push_back(c); // Add the created card to the deck.
	}
    }
};

// Prints out the entire deck to standard output.
void DeckOfCards::dumpDeck() const
{
  for (std::vector<Card>::const_iterator i = m_deck.begin();
       i != m_deck.end();
       ++i)
    {
      std::cout << (*i).toString() << std::endl;
    }
}

void DeckOfCards::shuffle()
{
  // Seeding
  srand(time(NULL));
  const size_t numCards = Card::s_FacesSz * Card::s_SuitsSz; 

  // Routine for breaking the built-in pseudorandomness of C++.
  for (size_t n = 0; n < numCards; ++n)
    {
      int x = (rand() % 1000000 + 1) % numCards;
      // Swap cards.
      Card temp = m_deck[x];
      m_deck[x] = m_deck[n];
      m_deck[n] = temp;
    }
}

