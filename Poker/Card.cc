/*********************************************************/
/* Programmer: Santiago Paredes                          */
/*                                                       */
/* Project 1: Poker Game (Card.cc)                       */
/*********************************************************/ 

#include <iostream>
#include "Card.h"

static const std::string STR_EMPTY("");

// Faces of cards associated with an array of strings, positively offset by 1.
const std::string Card::s_Faces[] = {
  STR_EMPTY, 
  "Ace", 
  "2", 
  "3", 
  "4", 
  "5", 
  "6", 
  "7", 
  "8", 
  "9", 
  "10", 
  "Jack", 
  "Queen", 
  "King"
};
const size_t Card::s_FacesSz(sizeof(s_Faces)/sizeof(std::string) - 1);

// Suites of cards associated with an array of strings, positively offset by 1.
const std::string Card::s_Suits[] = {
  STR_EMPTY, 
  "Spades", 
  "Hearts", 
  "Diamonds", 
  "Clubs"
};
const size_t Card::s_SuitsSz(sizeof(s_Suits)/sizeof(std::string) - 1);

Card::Card(size_t face, size_t suit) 
  :m_face(face),
   m_suit(suit)
{
};

const char* Card::toString() const
{
  return (s_Faces[m_face] + " of " + s_Suits[m_suit]).c_str();
};

const size_t Card::getFace() const
{
  if (m_face == 1)
    return 14;
  return m_face;
};

const size_t Card::getSuit() const
{
  return m_suit;
};

bool operator< (Card const& a, Card const& b)
{
  return (a.m_face < b.m_face);
};

bool operator== (Card const& a, Card const& b)
{
  return (a.m_face == b.m_face && a.m_suit == b.m_suit);
};

bool Card::compareSuit (Card const& a, Card const& b)
{
  if (a.m_suit != b.m_suit) return a.m_suit < b.m_suit;
  return (a.m_face < b.m_face);
};
