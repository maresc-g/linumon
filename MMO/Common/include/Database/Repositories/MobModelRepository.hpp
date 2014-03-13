//
// MobModelRepository.hpp for MobModelRepository in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Thu Mar 13 12:27:15 2014 alexis mestag
// Last update Thu Mar 13 12:28:17 2014 alexis mestag
//

#ifndef				__MOBMODELREPOSITORY_HPP__
# define			__MOBMODELREPOSITORY_HPP__

# include			"Database/Repositories/Repository.hpp"
# include			"Entities/MobModel-odb.hxx"

template<>
class				Repository<MobModel> : public BaseRepository<MobModel>
{
  friend class			Singleton<Repository<MobModel> >;

private:
  Repository() : BaseRepository() {}
  virtual ~Repository() {}

public:
  MobModel			*getByName(std::string const &name, bool const inTr = false) {
    Database::Transaction	*t = Database::getNewTransaction(inTr);
    Database::Query<MobModel>	query(Database::Query<MobModel>::name == name);
    Database::Result<MobModel>	result(Database::getInstance()->getDb()->query<MobModel>(query));
    MobModel			*ret = NULL;

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
