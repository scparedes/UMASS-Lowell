/*********************************************************/
/* Programmer: Santiago Paredes                          */
/*                                                       */
/* Project 1: Poker Game (Hand.h)                        */
/*********************************************************/ 

#ifndef __HAND_H__
#define __HAND_H__

#include <vector>
#include <iostream>
#include <algorithm>
#include "Card.h"

class Hand
{
  
 public:
  static const size_t szHand;
  Hand();
  bool hasPair(int *extra);
  bool hasTwoPair(int *extra);
  bool hasThreeKind(int *extra);
  bool hasFullHouse(int *extra);
  bool hasFourKind(int *extra);
  bool hasFlush(int *extra);     // All five cards are of the same suit.
  bool hasStraight(int *extra);  // Five cards of consecutive face values.
  void setBadHand();
  int getHighCard();
 

  static bool compareSuit(const Card& a, const Card& b);
  void forceHand(); // For debugging purposes. Allows programmer to create a hand themselves (hard-coded function).
  bool addCard(const Card& c);
  void removeCards(); // Removes cards based upon the indeces in m_undesiredCards.
  void addUndesired(int n); // Adds cards to m_undesiredCards.
  void sortHand();
  const std::vector<Card>& getCards() const;

 private:
  std::vector<Card> m_cards;
  std::vector<int> m_undesiredCards;
  
};

inline bool Hand::addCard(const Card& c)
{
  if (m_cards.size() > szHand)
    {
      return false;
    }
  m_cards.push_back(c);  
  return true;
}

inline void Hand::sortHand() {
  std::sort(m_cards.begin(), m_cards.end());
}

inline const std::vector<Card>& Hand::getCards() const
{
  return m_cards;
}

inline void Hand::addUndesired(int n)
{
  m_undesiredCards.push_back(n-1);
}

#endif
