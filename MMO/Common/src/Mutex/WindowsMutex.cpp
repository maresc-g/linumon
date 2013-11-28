//
// WindowsMutex.cpp for  in /home/ansel_l/Documents/Rtype/work
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Thu Oct 24 12:57:22 2013 laurent ansel
// Last update Mon Nov 25 22:23:51 2013 alexis mestag
//

#include		"Mutex/WindowsMutex.hh"

WindowsMutex::WindowsMutex() :
  AMutex()
{

}

WindowsMutex::~WindowsMutex()
{

}

bool			WindowsMutex::init()
{
  InitializeCriticalSection(&_section);
  this->setIsInit();
  return (true);
}

bool			WindowsMutex::destroy()
{
  DeleteCriticalSection(&_section);
  return (true);
}

bool			WindowsMutex::lock()
{
  EnterCriticalSection(&_section);
  return (true);
}

bool			WindowsMutex::tryLock()
{
  bool			ret = true;

  if (!TryEnterCriticalSection(&_section)) {
    ret = false;
  }
  return (ret);
}

bool			WindowsMutex::unlock()
{
  LeaveCriticalSection(&_section);
  return (true);
}
