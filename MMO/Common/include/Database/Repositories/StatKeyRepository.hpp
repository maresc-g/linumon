//
// StatKeyRepository.hpp for StatKeyRepository in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Wed Feb 26 00:07:09 2014 alexis mestag
// Last update Wed Mar 12 20:59:00 2014 alexis mestag
//

#ifndef				__STATKEYREPOSITORY_HPP__
# define			__STATKEYREPOSITORY_HPP__

# include			"Database/Repositories/Repository.hpp"
# include			"Stats/StatKey-odb.hxx"

template<>
class				Repository<StatKey> : public BaseRepository<StatKey>
{
  friend class			Singleton<Repository<StatKey> >;

private:
  Repository() : BaseRepository() {}
  virtual ~Repository() {}

public:
  StatKey			*getByName(std::string const &name, bool const inTr = false) {
    Database::Transaction	*t = Database::getNewTransaction(inTr);
    Database::Query<StatKey>	query(Database::Query<StatKey>::name == name);
    Database::Result<StatKey>	result(Database::getInstance()->getDb()->query<StatKey>(query));
    StatKey			*ret = NULL;

    if (result.size())
      ret = result.begin().load();

    if (t) {
      t->commit();
      delete t;
    }
    return (ret);
  }
};

#endif
