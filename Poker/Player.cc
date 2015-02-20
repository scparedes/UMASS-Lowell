/*********************************************************/
/* Programmer: Santiago Paredes                          */
/*                                                       */
/* Project 1: Poker Game (Player.cc)                     */
/*********************************************************/ 

#include <iostream>
#include <algorithm>
#include <iterator>

#include "Player.h"


Player::Player()
{
}

void Player::discard() {
  m_hand.removeCards();
}

bool Player::receiveCard(const Card& card)
{
  return m_hand.addCard(card);
}

void Player::addBadCards(std::vector<int> v) {

    for (std::vector<int>::const_iterator i = v.begin();
	 i != v.end();
	 ++i)
      {
	m_hand.addUndesired(*i);
      }
}

void Player::showHand()
{
  int count = 0;
  
  m_hand.sortHand();
  
  for (std::vector<Card>::const_iterator i = m_hand.getCards().begin();
       i != m_hand.getCards().end();
       ++i)
    {
      std::cout << (++count) << ")  " << (*i).toString() << std::endl;
    }
}
