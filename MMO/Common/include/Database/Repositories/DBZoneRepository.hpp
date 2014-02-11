//
// DBZoneRepository.hpp for DBZoneRepository in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Mon Feb 10 15:24:18 2014 alexis mestag
// Last update Mon Feb 10 15:44:07 2014 alexis mestag
//

#ifndef				__DBZONEREPOSITORY_HPP__
# define			__DBZONEREPOSITORY_HPP__

# include			"Database/Repositories/Repository.hpp"
# include			"Entities/DBZone-odb.hxx"

template<>
class				Repository<DBZone> : public BaseRepository<DBZone>
{
  friend class			Singleton<Repository<DBZone> >;

private:
  Repository() : BaseRepository() {}
  virtual ~Repository() {}

public:
  DBZone			*getByName(std::string const &name) {
    Database::Transaction	t(Database::getInstance()->getDb()->begin());
    Database::Query<DBZone>	query(Database::Query<DBZone>::name == name);
    Database::Result<DBZone>	result(Database::getInstance()->getDb()->query<DBZone>(query));
    DBZone			*ret = NULL;

    if (result.size())
      ret = result.begin().load();

    t.commit();
    return (ret);
  }
};

#endif
