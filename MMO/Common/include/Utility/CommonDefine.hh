//
// CommonDefine.hh for  in /home/ansel_l/Documents/Pfa/work
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Thu Nov 28 16:59:05 2013 laurent ansel
// Last update Fri Mar 14 16:05:19 2014 laurent ansel
//

#ifndef 		__COMMONDEFINE_HH__
# define 		__COMMONDEFINE_HH__

#define	SIZE_BUFFER	20000

#define HEADER		"1HEADER"
#define	CONTENT		"2CONTENT"

#ifndef	_WIN32
#define	FD		int
#else
#define	FD		SOCKET
#endif

typedef enum			eStuffAction
  {
    NONE,
    GET,
    PUT
  }				eStuffAction;

typedef enum			eInteraction
  {
    NONE,
    AGRO,
    TRADE
  }				eInteraction;

#endif
