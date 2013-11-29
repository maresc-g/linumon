//
// UnixPoll.cpp for  in /home/ansel_l/Documents/Pfa/work/Common/include/Poll
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Thu Nov 28 17:56:11 2013 laurent ansel
// Last update Thu Nov 28 19:58:37 2013 laurent ansel
//

#include			<iostream>
#include			"Poll/UnixPoll.hh"

UnixPoll::UnixPoll():
  _fd(new std::vector<struct pollfd>)
{

}

UnixPoll::~UnixPoll()
{
  delete _fd;
}

void				UnixPoll::pushFd(FD const fd, enum IPoll::ePoll const type)
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

void				UnixPoll::rmFd(FD const fd)
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

void				UnixPoll::setTimeout(int const timeout)
{
  _timeout = timeout;
}

bool				UnixPoll::isSet(FD const fd, enum IPoll::ePoll const type)
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

int				UnixPoll::runPoll(bool const setTimeout)
{
  int				ret;

  if (setTimeout)
    ret = poll(&(*_fd)[0], _fd->size(), _timeout);
  else
    ret = poll(&(*_fd)[0], _fd->size(), -1);
  return (ret);
}
