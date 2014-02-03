//
// PlayerRepository.hpp for PlayerRepository in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Mon Feb  3 17:41:44 2014 alexis mestag
// Last update Mon Feb  3 17:43:53 2014 alexis mestag
//

#ifndef				__PLAYERREPOSITORY_HPP__
# define			__PLAYERREPOSITORY_HPP__

template<>
class				Repository<Player> : public BaseRepository<Player>
{
  friend class			Singleton<Repository<Player> >;

private:
  Repository() : BaseRepository() {}
  virtual ~Repository() {}
};

#endif
