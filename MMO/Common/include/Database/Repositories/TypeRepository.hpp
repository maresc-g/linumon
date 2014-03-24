//
// TypeRepository.hpp for TypeRepository in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Sun Mar 23 14:34:02 2014 alexis mestag
// Last update Sun Mar 23 14:34:30 2014 alexis mestag
//

#ifndef				__TYPEREPOSITORY_HPP__
# define			__TYPEREPOSITORY_HPP__

# include			"Database/Repositories/Repository.hpp"
# include			"Entities/Type-odb.hxx"

template<>
class				Repository<Type> : public BaseRepository<Type>
{
  friend class			Singleton<Repository<Type> >;

private:
  Repository() : BaseRepository() {}
  virtual ~Repository() {}

public:
  Type			*getByName(std::string const &name, bool const inTr = false) {
    Database::Transaction	*t = Database::getNewTransaction(inTr);
    Database::Query<Type>	query(Database::Query<Type>::name == name);
    Database::Result<Type>	result(Database::getInstance()->getDb()->query<Type>(query));
    Type			*ret = NULL;

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
