//
// CircularBuffer.cpp for  in /home/ansel_l/Documents/Rtype/work/Server
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Tue Oct 29 00:13:43 2013 laurent ansel
// Last update Thu Feb  6 14:43:29 2014 laurent ansel
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

void				CircularBuffer::pushTrame(Trame *trame, bool const)
{
  bool				append = false;

  if (trame->isMember(HEADER))
    {
      for (std::list<Trame *>::iterator it = _buffer->begin() ; it != _buffer->end() ; ++it)
	{
	  if ((*(*it))[HEADER] == (*trame)[HEADER])
	    {
	      // if (write && (*trame)[CONTENT].asString().size() + (*(*it))[CONTENT].asString().size() // <= SIZE_BUFFER)
	      // if (write && (*trame)((*trame)[CONTENT]).toString().size() + (*(*it))((*(*it))[CONTENT]).toString().size() <= SIZE_BUFFER)
	      // 	{
	      // 	  (*(*it))[CONTENT].append((*trame)[CONTENT]);
	      // 	  append = true;
	      // 	}
	      // else if (!write)
	      // 	{
	      // 	  (*(*it))[CONTENT].append((*trame)[CONTENT]);
	      // 	  append = true;
	      // 	}
	    }
	}
      if (!append)
	this->_buffer->push_back(trame);
    }
}

void				CircularBuffer::pushFrontTrame(Trame *trame, bool const)
{
  bool				append = false;

  if (trame->isMember(HEADER))
    {
      for (std::list<Trame *>::iterator it = _buffer->begin() ; it != _buffer->end() ; ++it)
	{
	  if ((*(*it))[HEADER] == (*trame)[HEADER])
	    {
	      // if (write && (*trame)[CONTENT].asString().size() + (*(*it))[CONTENT].asString().size() <= SIZE_BUFFER)
	      // 	{
	      // 	  (*(*it))[CONTENT].append((*trame)[CONTENT]);
	      // 	  append = true;
	      // 	}
	      // else if (!write)
	      // 	{
	      // 	  (*(*it))[CONTENT].append((*trame)[CONTENT]);
	      // 	  append = true;
	      // 	}
	    }
	}
      if (!append)
	this->_buffer->push_front(trame);
    }
}

Trame const			&CircularBuffer::getFirstTrame() const
{
  return (*this->_buffer->front());
}

Trame				*CircularBuffer::popFirstTrame()
{
  Trame				*tmp = NULL;

  if (!this->_buffer->empty())
    {
      for (std::list<Trame *>::iterator it = _buffer->begin() ; !tmp && it != _buffer->end() ; ++it)
  	if ((*it)->getEnd())
  	  {
  	    tmp = *it;
  	    it = this->_buffer->erase(it);
  	  }
    }
  return (tmp);
}

Trame				*CircularBuffer::popFirstTrame(unsigned int const id, std::string const &proto)
{
  Trame				*tmp = NULL;

  for (std::list<Trame *>::iterator it = _buffer->begin() ; it != _buffer->end() ; ++it)
    {
      if ((*it)->isMember(HEADER))
	{
	  if ((*(*it))[HEADER]["IDCLIENT"].asUInt() == id &&
	      (*(*it))[HEADER]["PROTOCOLE"].asString() == proto &&
	      (*it)->getEnd())
	    {
	      tmp = (*it);
	      it = this->_buffer->erase(it);
	      return (tmp);
	    }
	}
    }
  return (tmp);
}

void				CircularBuffer::deleteTrame(unsigned int const id)
{
  for (std::list<Trame *>::iterator it = _buffer->begin() ; it != _buffer->end()&& !this->_buffer->empty(); ++it)
    {
      if ((*(*it))[HEADER]["IDCLIENT"].asUInt() == id)
  	{
  	  delete (*it);
  	  it = this->_buffer->erase(it);
  	}
    }
}
