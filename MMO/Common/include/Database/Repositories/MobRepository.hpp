//
// MobRepository.hpp for MobRepository in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Mon Mar 10 18:59:26 2014 alexis mestag
// Last update Wed Mar 12 21:40:23 2014 alexis mestag
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
    bool			isInTr = (t || inTr) ? true : false;

    if (m.isInBattle())
      m.leaveBattle();

    /*
    ** Updating Stats
    */
    Repository<Stat>		*rStat = &Database::getRepository<Stat>();
    for (auto it = m.getStats().begin() ; it != m.getStats().end() ; ++it) {
      rStat->smartUpdate(**it, isInTr);
    }

    /*
    ** Updating Current Stats
    */
    for (auto it = m.getRawCurrentStats().begin() ; it != m.getRawCurrentStats().end() ; ++it) {
      rStat->smartUpdate(**it, isInTr);
    }

    /*
    ** Updating Equipments
    */
    // Repository<Stuff>		*rStuff = &Database::getRepository<Stuff>();
    // for (auto it = m.getEquipment().begin() ; it != m.getEquipment().end() ; ++it) {
    //   rStuff->smartUpdate(**it, isInTr);
    // }

    BaseRepository<Mob>::smartUpdate(m, isInTr);

    if (t) {
      t->commit();
      delete t;
    }
  }
};

#endif
