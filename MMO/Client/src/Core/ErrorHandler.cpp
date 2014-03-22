//
// ErrorHandler.cpp for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Mon Feb  3 13:06:46 2014 guillaume marescaux
// Last update Sat Mar 22 17:55:38 2014 guillaume marescaux
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

void				ErrorHandler::badUsernamePass(MutexVar<CLIENT::eState> *state, MutexVar<ErrorBox *> *)
{
  *state = CLIENT::NONE;
}

void				ErrorHandler::userConnected(MutexVar<CLIENT::eState> *state, MutexVar<ErrorBox *> *)
{
  *state = CLIENT::NONE;
}

void				ErrorHandler::nameExists(MutexVar<CLIENT::eState> *state, MutexVar<ErrorBox *> *)
{
  *state = CLIENT::CHOOSE_PLAYER;
}

void				ErrorHandler::guildExists(MutexVar<CLIENT::eState> *, MutexVar<ErrorBox *> *errorBox)
{
  (**errorBox)->setInfos("Error", "There already is a guild of this name");
}

void				ErrorHandler::alreadyInGuild(MutexVar<CLIENT::eState> *, MutexVar<ErrorBox *> *errorBox)
{
  (**errorBox)->setInfos("Error", "Player not found or is already in a guild");
}

//----------------------------------END PRIVATE METHODS----------------------------------------

//-------------------------------------BEGIN METHODS-------------------------------------------

void				ErrorHandler::handleError(Error const &error, MutexVar<CLIENT::eState> *state,
							  MutexVar<ErrorBox *> *errorBox)
{
  static std::map<Error::eError, void (ErrorHandler::*)(MutexVar<CLIENT::eState> *, MutexVar<ErrorBox *> *)>	ptrs =
    {
      { Error::USER, &ErrorHandler::badUsernamePass },
      { Error::USERCONNECTED, &ErrorHandler::userConnected },
      { Error::CREATEPLAYER, &ErrorHandler::nameExists },
      { Error::GUILDEXIST, &ErrorHandler::guildExists },
      { Error::ALREADYINGUILD, &ErrorHandler::alreadyInGuild }
    };

  if (ptrs.find(error.getType()) != ptrs.end())
    (this->*ptrs[error.getType()])(state, errorBox);
}

//--------------------------------------END METHODS--------------------------------------------
