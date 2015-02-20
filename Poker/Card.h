/*********************************************************/
/* Programmer: Santiago Paredes                          */
/*                                                       */
/* Project 1: Poker Game (Card.h)                        */
/*********************************************************/ 

#ifndef __CARD_H__
#define __CARD_H__

#include <string>

class Card
{
 public:
  Card(size_t face, size_t suit);
  const char* toString() const;
  static const size_t s_FacesSz;
  static const size_t s_SuitsSz;
  const size_t getFace() const;
  const size_t getSuit() const;
  
  friend bool operator< (Card const& a, Card const& b);
  friend bool operator== (Card const& a, Card const& b);
  bool compareSuit (Card const& a, Card const& b);
  
 private:
  size_t m_face;
  size_t m_suit;
  static const std::string s_Faces[];
  static const std::string s_Suits[];
};

#endif
