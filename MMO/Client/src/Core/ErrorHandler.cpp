//
// ErrorHandler.cpp for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Mon Feb  3 13:06:46 2014 guillaume marescaux
// Last update Wed Feb  5 10:59:16 2014 guillaume marescaux
//

#include			"Core/ErrorHandler.hh"

//-----------------------------------BEGIN CTOR / DTOR-----------------------------------------

ErrorHandler::ErrorHandler()
{
}

ErrorHandler::~ErrorHandler()
{
}

//------------------------------------END CTOR / DTOR------------------------------------------

//---------------------------------BEGIN PRIVATE METHODS---------------------------------------

void				ErrorHandler::badUsernamePass(MutexVar<eState> *state)
{
  *state = NONE;
}

void				ErrorHandler::userConnected(MutexVar<eState> *state)
{
  *state = NONE;
}

void				ErrorHandler::nameExists(MutexVar<eState> *state)
{
  *state = CHOOSE_PLAYER;
}

//----------------------------------END PRIVATE METHODS----------------------------------------

//-------------------------------------BEGIN METHODS-------------------------------------------

void				ErrorHandler::handleError(Error const &error, MutexVar<eState> *state)
{
  static std::map<Error::eError, void (ErrorHandler::*)(MutexVar<eState> *)>	ptrs =
    {
      { Error::USER, &ErrorHandler::badUsernamePass },
      { Error::USERCONNECTED, &ErrorHandler::userConnected },
      { Error::CREATEPLAYER, &ErrorHandler::nameExists }
    };

  (this->*ptrs[error.getType()])(state);
}

//--------------------------------------END METHODS--------------------------------------------
