//
// UnixPoll.hh for  in /home/ansel_l/Documents/Pfa/work/Common/include/Poll
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Thu Nov 28 17:18:27 2013 laurent ansel
// Last update Thu Nov 28 20:00:38 2013 laurent ansel
//

#ifndef 			__WINDOWSPOLL_HH__
# define 			__WINDOWSPOLL_HH__

#include			<vector>
#include			<windows.h>
#include			"Poll/IPoll.hh"

class				WindowsPoll : public IPoll
{
private:
  std::vector<WSAPOLLFD>	*_fd;
  int				_timeout;
public:
  WindowsPoll();
  virtual ~WindowsPoll();
  virtual void			pushFd(FD const fd, enum IPoll::ePoll const type);
  virtual void			rmFd(FD const fd);
  virtual void			setTimeout(int const timeout);
  virtual bool			isSet(FD const fd, enum IPoll::ePoll const type);
  virtual int			runPoll(bool const setTimeout);
};

#endif
