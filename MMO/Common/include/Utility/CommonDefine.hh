//
// CommonDefine.hh for  in /home/ansel_l/Documents/Pfa/work
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Thu Nov 28 16:59:05 2013 laurent ansel
// Last update Mon Dec  9 19:09:56 2013 laurent ansel
//

#ifndef 		__COMMONDEFINE_HH__
# define 		__COMMONDEFINE_HH__

#define	SIZE_BUFFER	4096

#define HEADER		"1HEADER"
#define	CONTENT		"2CONTENT"

#ifndef	_WIN32
#define	FD		int
#else
#define	FD		SOCKET
#endif

#endif
