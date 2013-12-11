//
// IPoll.hh for  in /home/ansel_l/Documents/Pfa/work/Common/include/Poll
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Thu Nov 28 17:02:58 2013 laurent ansel
// Last update Fri Dec  6 10:27:18 2013 laurent ansel
//

#ifndef 			__IPOLL_HH__
# define 			__IPOLL_HH__

#include			"Utility/CommonDefine.hh"

#define	CLIENT_MIN		1000

class				IPoll
{
public:
  enum				ePoll
    {
      READ = POLLIN,
      WRITE = POLLOUT,
      DISCONNECT = POLLRDHUP,
      RDDC = POLLIN | POLLRDHUP,
      WRDC = POLLOUT | POLLRDHUP,
      RDWR = POLLIN | POLLOUT,
      RDWRDC = POLLIN | POLLOUT | POLLRDHUP,
    };

public:
  virtual ~IPoll(){}
  virtual void			pushFd(FD const fd, enum IPoll::ePoll const type) = 0;
  virtual void			rmFd(FD const fd) = 0;
  virtual void			setTimeout(int const timeout) = 0;
  virtual bool			isSet(FD const fd, enum IPoll::ePoll const type) = 0;
  virtual int			runPoll(bool const setTimeout) = 0;
};

#endif
