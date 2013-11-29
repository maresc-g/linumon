//
// CircularBuffer.cpp for  in /home/ansel_l/Documents/Rtype/work/Server
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Tue Oct 29 00:13:43 2013 laurent ansel
// Last update Thu Nov 28 19:30:09 2013 laurent ansel
//

#include			"Socket/ISocketClient.hh"
#include			"CircularBufferManager/CircularBuffer.hh"

CircularBuffer::CircularBuffer():
  _buffer(new std::list<Trame *>)
{
}

CircularBuffer::~CircularBuffer()
{
  if (this->_buffer)
    {
      for (std::list<Trame *>::iterator it = _buffer->begin() ; it != _buffer->end() ; ++it)
	delete *it;
      delete _buffer;
    }
}

void				CircularBuffer::pushTrame(Trame *trame, bool const check)
{
  (void)trame;
  (void)check;
  // bool				append = false;

  // for (std::list<Trame *>::iterator it = _buffer->begin() ; it != _buffer->end() ; ++it)
  //   {
  //     if ((*it)->getHeader().getId() == trame->getHeader().getId() &&
  // 	  (*it)->getHeader().getTrameId() == trame->getHeader().getTrameId() &&
  // 	  (*it)->getHeader().getProto() == trame->getHeader().getProto())
  // 	{
  // 	  if (check && trame->getContent().size() + (*it)->getContent().size() <= SIZE_BUFFER)
  // 	    {
  // 	      (*it)->appendContent(trame->getContent());
  // 	      append = true;
  // 	    }
  // 	  else if (!check)
  // 	    {
  // 	      (*it)->appendContent(trame->getContent());
  // 	      append = true;
  // 	    }
  // 	}
  //   }
  // if (!append)
  //   this->_buffer->push_back(trame);
}

void				CircularBuffer::pushFrontTrame(Trame *trame, bool const check)
{
  (void)trame;
  (void)check;
  // bool				append = false;

  // for (std::list<Trame *>::iterator it = _buffer->begin() ; it != _buffer->end() ; ++it)
  //   {
  //     if ((*it)->getHeader().getId() == trame->getHeader().getId() &&
  // 	  (*it)->getHeader().getTrameId() == trame->getHeader().getTrameId() &&
  // 	  (*it)->getHeader().getProto() == trame->getHeader().getProto())
  // 	{
  // 	  if (check && trame->getContent().size() + (*it)->getContent().size() <= SIZE_BUFFER)
  // 	    {
  // 	      (*it)->appendContent(trame->getContent());
  // 	      append = true;
  // 	    }
  // 	  else if (!check)
  // 	    {
  // 	      (*it)->appendContent(trame->getContent());
  // 	      append = true;
  // 	    }
  // 	}
  //   }
  // if (!append)
  //   this->_buffer->push_front(trame);
}

Trame const			&CircularBuffer::getFirstTrame() const
{
  return (*this->_buffer->front());
}

Trame				*CircularBuffer::popFirstTrame()
{
  Trame				*tmp = NULL;

  // if (!this->_buffer->empty())
  //   {
  //     for (std::list<Trame *>::iterator it = _buffer->begin() ; !tmp && it != _buffer->end() ; ++it)
  // 	if ((*it)->isSetEndTrame())
  // 	  {
  // 	    tmp = *it;
  // 	    it = this->_buffer->erase(it);
  // 	  }
  //   }
  return (tmp);
}

Trame				*CircularBuffer::popFirstTrame(unsigned int const id, std::string const &proto)
{
  Trame				*tmp = NULL;

  (void)id;
  (void)proto;
  // for (std::list<Trame *>::iterator it = _buffer->begin() ; it != _buffer->end() ; ++it)
  //   {
  //     if ((*it)->getHeader().getId() == id &&
  // 	  (*it)->getHeader().getProto() == proto &&
  // 	  (*it)->isSetEndTrame())
  // 	{
  // 	  //	  std::cout << "content = " << (*it)->getContent()<< std::endl;
  // 	  tmp = (*it);
  // 	  it = this->_buffer->erase(it);
  // 	  return (tmp);
  // 	}
  //   }
  return (tmp);
}

void				CircularBuffer::deleteTrame(unsigned int const id)
{
  (void)id;
  // for (std::list<Trame *>::iterator it = _buffer->begin() ; it != _buffer->end()&& !this->_buffer->empty(); ++it)
  //   {
  //     if ((*it)->getHeader().getId() == id)
  // 	{
  // 	  delete (*it);
  // 	  it = this->_buffer->erase(it);
  // 	}
  //   }
}
