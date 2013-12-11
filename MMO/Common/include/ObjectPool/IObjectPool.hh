//
// IObjectPool.hh for  in /home/ansel_l/Documents/Pfa/work
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Sun Dec  1 20:15:17 2013 laurent ansel
// Last update Thu Dec  5 23:06:14 2013 laurent ansel
//

#ifndef 			__IOBJECTPOOL_HH__
# define 			__IOBJECTPOOL_HH__

class				IObjectPool
{
public:
  virtual ~IObjectPool(){}
  virtual void			run() = 0;
  virtual void			setQuit(bool const quit) = 0;
  virtual bool			waitExit() = 0;
  virtual void			startObjectPool() = 0;
  virtual void			*getObject() = 0;
};

#endif
