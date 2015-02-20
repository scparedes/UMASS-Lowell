/*********************************************************/
/* Programmer: Santiago Paredes                          */
/*                                                       */
/* Project 1: Poker Game (Hand.cc)                       */
/*********************************************************/ 

#include <algorithm>
#include <vector>
#include "Hand.h"

const size_t Hand::szHand(5);

// Hands will always be constructed with empty parameters and data members.
Hand::Hand()
{
}

void Hand::removeCards()
{
  // First, get references for items we want to delete.
  std::vector<Card> targets;
  
  std::sort(m_cards.begin(), m_cards.end());

  for (size_t i = 0; i < (m_undesiredCards.size() % 4); i++) 
    {
      // Storing undesired card objects into target array.
      targets.push_back(m_cards[m_undesiredCards[i]]);
    }
  
  for (std::vector<Card>::const_iterator it = targets.begin();
       it != targets.end();
       ++it)
    {
      // Matching undesired cards with cards in the hand and removing them.
      m_cards.erase(std::remove(m_cards.begin(), m_cards.end(),
				*it), m_cards.end());
    }
}

/*  ===========================================================
    The following functions are poker-hand detection functions
    =========================================================== */

bool Hand::hasPair(int *extra) 
{
  bool o1, o2, o3, o4;  // Create 3 bools: option 1, 2, 3, and 4.

  std::sort(m_cards.begin(), m_cards.end());
  /*
   * Checking: a a x y z
   */
  o1 = (m_cards[0].getFace() == m_cards[1].getFace()) 
    && (m_cards[0].getFace() != m_cards[2].getFace()) 
    && (m_cards[0].getFace() != m_cards[3].getFace()) 
    && (m_cards[0].getFace() != m_cards[4].getFace());

  /*
   * Checking: x a a y z
   */
  o2 = (m_cards[1].getFace() == m_cards[2].getFace()) 
    && (m_cards[1].getFace() != m_cards[0].getFace()) 
    && (m_cards[1].getFace() != m_cards[3].getFace()) 
    && (m_cards[1].getFace() != m_cards[4].getFace());

  /*
   * Checking: x y a a z
   */
  o3 = (m_cards[2].getFace() == m_cards[3].getFace()) 
    && (m_cards[2].getFace() != m_cards[0].getFace()) 
    && (m_cards[2].getFace() != m_cards[1].getFace()) 
    && (m_cards[2].getFace() != m_cards[4].getFace());

  /*
   * Checking: x y z a a
   */
  o4 = (m_cards[3].getFace() == m_cards[4].getFace()) 
    && (m_cards[3].getFace() != m_cards[0].getFace()) 
    && (m_cards[3].getFace() != m_cards[1].getFace()) 
    && (m_cards[3].getFace() != m_cards[2].getFace());


  if (o1 == true) 
    {
      m_undesiredCards.push_back(2);
      m_undesiredCards.push_back(3);
      m_undesiredCards.push_back(4);
      *extra = m_cards[0].getFace();
    }
  if (o2 == true) 
    {
      m_undesiredCards.push_back(0);
      m_undesiredCards.push_back(3);
      m_undesiredCards.push_back(4);
      *extra = m_cards[2].getFace();
    }
  if (o3 == true) 
    {
      m_undesiredCards.push_back(0);
      m_undesiredCards.push_back(1);
      m_undesiredCards.push_back(4);
      *extra = m_cards[2].getFace();
    }
  if (o4 == true) 
    {
      m_undesiredCards.push_back(0);
      m_undesiredCards.push_back(1);
      m_undesiredCards.push_back(2);
      *extra = m_cards[3].getFace();
    }

  return( o1 || o2 || o3 || o4 );
}

bool Hand::hasTwoPair(int *extra) 
{
  
  bool o1, o2, o3;  // Create 3 bools: option 1, 2, and 3.
  
  std::sort(m_cards.begin(), m_cards.end());

  /*
   * Checking: a a  b b x
   */                       
  o1 = m_cards[0].getFace() == m_cards[1].getFace() &&
    m_cards[2].getFace() == m_cards[3].getFace() ;
  
  /*
   * Checking: a a  x b b 
   */                       
  o2 = m_cards[0].getFace() == m_cards[1].getFace() &&
    m_cards[3].getFace() == m_cards[4].getFace() ;

  /*
   * Checking: x a a  b b 
   */                       
  o3 = m_cards[1].getFace() == m_cards[2].getFace() &&
    m_cards[3].getFace() == m_cards[4].getFace() ;

  return o1 || o2 || o3;
  
}
bool Hand::hasFullHouse(int *extra) 
{
  bool o1, o2;  // Create 2 bools: option 1 and 2.
  
  std::sort(m_cards.begin(), m_cards.end());

  /*
   * Check for: x x x a a
   */
  o1 = m_cards[0].getFace() == m_cards[1].getFace() &&
    m_cards[1].getFace() == m_cards[2].getFace() &&
    m_cards[3].getFace() == m_cards[4].getFace();

  /*
   * Check for: a a x x x
   */
  o2 = m_cards[2].getFace() == m_cards[3].getFace() &&
    m_cards[3].getFace() == m_cards[4].getFace() &&
    m_cards[0].getFace() == m_cards[1].getFace();

  if (o1 == true) 
    {
      *extra = m_cards[0].getFace();
    }

  if (o2 == true) 
    {
      *extra = m_cards[4].getFace();
    }

  return( o1 || o2 );


}

bool Hand::hasThreeKind(int *extra) 
{
  bool o1, o2, o3;  // Create 3 bools: option 1, 2, and 3.
  
  std::sort(m_cards.begin(), m_cards.end());

  /*
   * Check for: x x x a b
   */
  o1 = m_cards[0].getFace() == m_cards[1].getFace() &&
    m_cards[1].getFace() == m_cards[2].getFace() &&
    m_cards[3].getFace() != m_cards[0].getFace() &&
    m_cards[4].getFace() != m_cards[0].getFace() &&
    m_cards[3].getFace() != m_cards[4].getFace();

  /*
   * Check for: a x x x b
   */
  o2 = m_cards[1].getFace() == m_cards[2].getFace() &&
    m_cards[2].getFace() == m_cards[3].getFace() &&
    m_cards[0].getFace() != m_cards[1].getFace() &&
    m_cards[4].getFace() != m_cards[1].getFace() &&
    m_cards[0].getFace() != m_cards[4].getFace();

  /*
   * Check for: a b x x x
   */
  o3 = m_cards[2].getFace() == m_cards[3].getFace() &&
    m_cards[3].getFace() == m_cards[4].getFace() &&
    m_cards[0].getFace() != m_cards[2].getFace() &&
    m_cards[1].getFace() != m_cards[2].getFace() &&
    m_cards[0].getFace() != m_cards[1].getFace();
  
  if (o1 == true)
    {
      if (m_cards[4].getFace() < 7)
	{
	  m_undesiredCards.push_back(3);
	  m_undesiredCards.push_back(4);
	}
      *extra = m_cards[2].getFace();
    }
  if (o2 == true)
    {
      if (m_cards[0].getFace() < 7) 
	{
	  m_undesiredCards.push_back(0);
	}
      if (m_cards[4].getFace() < 7) {
	m_undesiredCards.push_back(4);
      }
      *extra = m_cards[3].getFace();
    }
  if (o3 == true)
    {
      if (m_cards[1].getFace() < 7)
	{
	  m_undesiredCards.push_back(0);
	  m_undesiredCards.push_back(0);
	}
      *extra = m_cards[4].getFace();
    }

  return( o1 || o2 || o3 );
  
};


bool Hand::hasFourKind(int *extra)
{

  bool o1, o2;  // Create 3 bools: option 1, and 2.

  std::sort(m_cards.begin(), m_cards.end());

  /*
   * Checking: x x  x x a
   */ 
  o1 = m_cards[0].getFace() == m_cards[1].getFace() &&
    m_cards[1].getFace() == m_cards[2].getFace() &&
    m_cards[2].getFace() == m_cards[3].getFace() ;

  /*
   * Checking: a x  x x x
   */ 
  o2 = m_cards[1].getFace() == m_cards[2].getFace() &&
    m_cards[2].getFace() == m_cards[3].getFace() &&
    m_cards[3].getFace() == m_cards[4].getFace() ;

  if (o1 == true)
    {
      if (m_cards[4].getFace() < 7)
	m_undesiredCards.push_back(4);
      *extra = m_cards[0].getFace();
    }
  if (o2 == true)
    {
      if (m_cards[0].getFace() < 7)
	m_undesiredCards.push_back(0);
      *extra = m_cards[1].getFace();
    }

  return( o1 || o2 );
}

// Overloaded operator for comparing suit values.
//
bool Hand::compareSuit (const Card& a, const Card& b) 
{
  if (a.getSuit() != b.getSuit()) return a.getSuit() < b.getSuit();
      return (a.getFace() < b.getFace());
}
//
// End of compare suits function.

bool Hand::hasFlush(int *extra) 
{
  bool isFlush;
  
  std::sort(m_cards.begin(), m_cards.end(), Hand::compareSuit);
  isFlush = m_cards[0].getSuit() == m_cards[szHand-1].getSuit();
  
  std::sort(m_cards.begin(), m_cards.end());
  *extra = m_cards[4].getFace();
  
  return (isFlush);
}

bool Hand::hasStraight(int *extra) {

  size_t i, tempCardPos;
  bool o1, o2;

  std::sort(m_cards.begin(), m_cards.end());

  // Check if hand has an Ace.

  if ( m_cards[0].getFace() == 1 )
    {
      // Check straight using an Ace.
      o1 = m_cards[1].getFace() == 2 && m_cards[2].getFace() == 3 &&
	m_cards[3].getFace() == 4 && m_cards[4].getFace() == 5 ;
      o2 = m_cards[1].getFace() == 10 && m_cards[2].getFace() == 11 &&
	m_cards[3].getFace() == 12 && m_cards[4].getFace() == 13 ;
      
      if (o2 == true)
	*extra = m_cards[0].getFace();

      return ( o1 || o2 );
    }
  else
    {
      
      // General case: check for increasing values
      tempCardPos = m_cards[0].getFace() + 1;
      
      for ( i = 1; i < 5; i++ )
	{
	  if ( m_cards[i].getFace() != tempCardPos )
	    return false;        // Straight failed.
	  
	  tempCardPos++;   // Next card in hand.
	}
      *extra = m_cards[4].getFace();

      return true;        // Straight found.
    }
}


void Hand::forceHand() 
{
  Card a(3, 1);
  m_cards.push_back(a);
  Card b(3, 2);
  m_cards.push_back(b);
  Card c(3, 3);
  m_cards.push_back(c);
  Card d(1, 4);
  m_cards.push_back(d);
  Card e(4, 3);
  m_cards.push_back(e);
}

void Hand::setBadHand()
{

  std::sort(m_cards.begin(), m_cards.end());

  if (m_cards[0].getFace() < 7)
    m_undesiredCards.push_back(0);

  if (m_cards[1].getFace() < 7)
    m_undesiredCards.push_back(1);

  if (m_cards[2].getFace() < 7)
    m_undesiredCards.push_back(2);

}

int Hand::getHighCard() 
{  
  std::sort(m_cards.begin(), m_cards.end());
  if (m_cards[0].getFace() == 14)
    return 14;
  return m_cards[szHand-1].getFace();
}
