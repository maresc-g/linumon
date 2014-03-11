//
// PlayerViewRepository.hpp for PlayerViewRepository in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Mon Feb  3 15:38:27 2014 alexis mestag
// Last update Mon Mar 10 20:29:12 2014 alexis mestag
//

#ifndef				__PLAYERVIEWREPOSITORY_HPP__
# define			__PLAYERVIEWREPOSITORY_HPP__

# include			<list>
# include			"Database/Database.hpp"
# include			"Database/Repositories/Repository.hpp"
# include			"Entities/Views/PlayerView-odb.hxx"

template<>
class				Repository<PlayerView> : public Singleton<Repository<PlayerView> >
{
  friend class			Singleton<Repository<PlayerView> >;

private:
  Repository() : Singleton() {}
  virtual ~Repository() {}

public:
  std::list<PlayerView *>		*getByUserId(unsigned long userId, bool const inTr = false) {
    Database::Transaction		*t = Database::getNewTransaction(inTr);
    Database::Query<PlayerView>		query(Database::Query<PlayerView>::User::persistentId == userId);
    Database::Result<PlayerView>	result(Database::getInstance()->getDb()->query<PlayerView>(query));
    std::list<PlayerView *>		*ret = NULL;

    if (result.size()) {
      ret = new std::list<PlayerView *>;
      for (auto it = result.begin() ; it != result.end() ; ++it) {
	ret->push_back(new PlayerView(*it));
      }
    }

    if (t) {
      t->commit();
      delete t;
    }
    return (ret);
  }
};

#endif
