//
// ClientWriter.cpp for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Thu Feb  6 12:45:02 2014 laurent ansel
// Last update Thu Feb  6 15:20:51 2014 laurent ansel
//

#include			"ClientWriter/ClientWriter.hh"
#include			"Server/Server.hh"

ClientWriter::ClientWriter():
  Thread(),
  _write(new std::map<FD, unsigned int>),
  _quit(false),
  _mutex(new Mutex)
{
  _mutex->init();
  this->create(&runClientWriter, this);
  this->start();
}

ClientWriter::~ClientWriter()
{
  delete _write;
  _mutex->destroy();
  delete _mutex;
}

void				ClientWriter::run()
{
  FD				tmp = 0;

  _mutex->lock();
  while (!_quit)
    {
      for (auto it = this->_write->begin() ; it != this->_write->end() ; ++it)
	if (it->second > 0)
	  {
	    tmp = it->first;
	    _mutex->unlock();
	    Server::getInstance()->detectWrite(tmp);
	    _mutex->lock();
	  }
      _mutex->unlock();
      usleep(50000);
      _mutex->lock();
    }
  _mutex->unlock();
}

void				ClientWriter::setQuit(bool const quit)
{
  _mutex->lock();
  _quit = quit;
  _mutex->unlock();
}

void				ClientWriter::newClient(FD const fd)
{
  std::cout << "NEW1" << std::endl;
  _mutex->lock();
  if (this->_write->find(fd) == this->_write->end())
    (*this->_write)[fd] = 0;
  _mutex->unlock();
  std::cout << "NEW2" << std::endl;
}

void				ClientWriter::deleteClient(FD const fd)
{
  _mutex->lock();
  this->_write->erase(fd);
  _mutex->unlock();
}

unsigned int			ClientWriter::getNbTrame(FD const fd) const
{
  std::cout << "GET1" << std::endl;
  _mutex->lock();
  if (this->_write->find(fd) != this->_write->end())
    {
      _mutex->unlock();
      std::cout << "GET2" << std::endl;
      return ((*this->_write)[fd]);
    }
  _mutex->unlock();
  std::cout << "GET2.1" << std::endl;
  return (0);
}

void				ClientWriter::addNewTrame(FD const fd, unsigned int const nb)
{
  std::cout << "ADD1" << std::endl;
  _mutex->lock();
  if (this->_write->find(fd) != this->_write->end())
    (*this->_write)[fd] += nb;
  else
    (*this->_write)[fd] = nb;
  _mutex->unlock();
  std::cout << "ADD2" << std::endl;
}

void				*runClientWriter(void *data)
{
  if (data)
    {
      ClientWriter		*manager = reinterpret_cast<ClientWriter *>(data);

      manager->run();
    }
  return (NULL);
}

