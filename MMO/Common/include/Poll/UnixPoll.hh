//
// UnixPoll.hh for  in /home/ansel_l/Documents/Pfa/work/Common/include/Poll
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Thu Nov 28 17:18:27 2013 laurent ansel
// Last update Thu Nov 28 19:22:33 2013 laurent ansel
//

#ifndef 			__UNIXPOLL_HH__
# define 			__UNIXPOLL_HH__

#include			<vector>
#include			<poll.h>
#include			"Poll/IPoll.hh"

class				UnixPoll : public IPoll
{
private:
  std::vector<struct pollfd>	*_fd;
  int				_timeout;
public:
  UnixPoll();
  virtual ~UnixPoll();
  virtual void			pushFd(FD const fd, enum IPoll::ePoll const type);
  virtual void			rmFd(FD const fd);
  virtual void			setTimeout(int const timeout);
  virtual bool			isSet(FD const fd, enum IPoll::ePoll const type);
  virtual int			runPoll(bool const setTimeout);
};

#endif
