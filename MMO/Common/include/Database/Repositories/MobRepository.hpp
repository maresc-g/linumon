//
// MobRepository.hpp for MobRepository in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Mon Mar 10 18:59:26 2014 alexis mestag
// Last update Mon Mar 10 20:35:48 2014 alexis mestag
//

#ifndef				__MOBREPOSITORY_HH__
# define			__MOBREPOSITORY_HH__

# include			"Database/Repositories/Repository.hpp"
# include			"Entities/Mob-odb.hxx"

template<>
class				Repository<Mob> : public BaseRepository<Mob>
{
  friend class			Singleton<Repository<Mob> >;

private:
  Repository() : BaseRepository() {}
  virtual ~Repository() {}

public:
  virtual void			smartUpdate(Mob &m, bool const inTr = false) {
    Database::Transaction	*t = Database::getNewTransaction(inTr);

    BaseRepository<Mob>::smartUpdate(m, !inTr ? !inTr : inTr);

    if (t) {
      t->commit();
      delete t;
    }
  }
};

#endif
