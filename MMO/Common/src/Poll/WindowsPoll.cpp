//
// WindowsPoll.cpp for  in /home/ansel_l/Documents/Pfa/work/Common/include/Poll
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Thu Nov 28 17:56:11 2013 laurent ansel
// Last update Thu Nov 28 20:01:58 2013 laurent ansel
//

#include			<iostream>
#include			"Poll/WindowsPoll.hh"

WindowsPoll::WindowsPoll():
  _fd(new std::vector<struct pollfd>)
{

}

WindowsPoll::~WindowsPoll()
{
  delete _fd;
}

void				WindowsPoll::pushFd(FD const fd, enum IPoll::ePoll const type)
{
  bool				init = false;
  struct pollfd			tmp;

  for (auto it = _fd->begin() ; it != _fd->end() ; ++it)
    {
      if ((*it).fd == fd)
	{
	  (*it).events |= type;
	  init = true;
	}
    }
  if (!init)
    {
      tmp.fd = fd;
      tmp.events |= type;
      _fd->push_back(tmp);
    }

}

void				WindowsPoll::rmFd(FD const fd)
{
  for (auto it = _fd->begin() ; it != _fd->end() ; ++it)
    {
      if ((*it).fd == fd)
	{
	  _fd->erase(it);
	  break;
	}
    }
}

void				WindowsPoll::setTimeout(int const timeout)
{
  _timeout = timeout;
}

bool				WindowsPoll::isSet(FD const fd, enum IPoll::ePoll const type)
{
  for (auto it = _fd->begin() ; it != _fd->end() ; ++it)
    {
      if ((*it).fd == fd)
	{
	  if ((*it).revents & type)
	    return (true);
	  return (false);
	}
    }
  return (false);
}

int				WindowsPoll::runPoll(bool const setTimeout)
{
  int				ret;

  if (setTimeout)
    ret = WSAPoll(&(*_fd)[0], _fd->size(), _timeout);
  else
    ret = WSAPoll(&(*_fd)[0], _fd->size(), -1);
  return (ret);
}
