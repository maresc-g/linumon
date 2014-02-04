//
// PlayerRepository.hpp for PlayerRepository in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Mon Feb  3 17:41:44 2014 alexis mestag
// Last update Tue Feb  4 15:47:56 2014 laurent ansel
//

#ifndef				__PLAYERREPOSITORY_HPP__
# define			__PLAYERREPOSITORY_HPP__

# include			"Database/Database.hpp"
# include			"Database/Repositories/Repository.hpp"
# include			"Entities/Player-odb.hxx"

template<>
class				Repository<Player> : public BaseRepository<Player>
{
  friend class			Singleton<Repository<Player> >;

private:
  Repository() : BaseRepository() {}
  virtual ~Repository() {}
};

#endif
