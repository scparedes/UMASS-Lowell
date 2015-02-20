/*********************************************************/
/* Programmer: Santiago Paredes                          */
/*                                                       */
/* Project 1: Poker Game (Player.h)                      */
/*********************************************************/ 

#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <vector>
#include "Card.h"
#include "Hand.h"
#include "Player.h"

class Player
{
  
 public:
  Player();
  void discard();
  Hand& getHand();
  bool receiveCard(const Card& card);
  void addBadCards(std::vector<int> v);
  void showHand();
  
 private:
  Hand m_hand;
};

inline Hand& Player::getHand()
{
  return m_hand;
};

#endif
