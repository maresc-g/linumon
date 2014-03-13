//
// ExperienceCurveRepository.hpp for ExperienceCurveRepository in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Wed Mar 12 21:00:41 2014 alexis mestag
// Last update Wed Mar 12 21:01:58 2014 alexis mestag
//

#ifndef				__EXPERIENCECURVEREPOSITORY_HPP__
# define			__EXPERIENCECURVEREPOSITORY_HPP__

# include			"Database/Repositories/Repository.hpp"
# include			"Stats/ExperienceCurve-odb.hxx"

template<>
class				Repository<ExperienceCurve> : public BaseRepository<ExperienceCurve>
{
  friend class			Singleton<Repository<ExperienceCurve> >;

private:
  Repository() : BaseRepository() {}
  virtual ~Repository() {}

public:
  ExperienceCurve			*getByName(std::string const &name, bool const inTr = false) {
    Database::Transaction		*t = Database::getNewTransaction(inTr);
    Database::Query<ExperienceCurve>	query(Database::Query<ExperienceCurve>::name == name);
    Database::Result<ExperienceCurve>	result(Database::getInstance()->getDb()->query<ExperienceCurve>(query));
    ExperienceCurve			*ret = NULL;

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
