//
// PlayerRepository.hpp for PlayerRepository in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Mon Feb  3 17:41:44 2014 alexis mestag
// Last update Thu Mar 13 13:23:45 2014 alexis mestag
//

#ifndef				__PLAYERREPOSITORY_HPP__
# define			__PLAYERREPOSITORY_HPP__

# include			"Database/Database.hpp"
# include			"Database/Repositories/Repository.hpp"
# include			"Database/Repositories/MobRepository.hpp"
# include			"Entities/Player-odb.hxx"

template<>
class				Repository<Player> : public BaseRepository<Player>
{
  friend class			Singleton<Repository<Player> >;

private:
  Repository() : BaseRepository() {}
  virtual ~Repository() {}

public:
  virtual void			smartUpdate(Player &p, bool const inTr = false) {
    Database::Transaction	*t = Database::getNewTransaction(inTr);
    bool			isInTr = (t || inTr) ? true : false;

    std::cout << "=================================> Smart Updating " << &p << " (needed " << this->getById(p.getPersistentId()) << ")" << std::endl;

    /*
    ** Updating Inventory
    */
    p.getInventory().serializationInventory();

    /*
    ** Updating Talents
    */
    Repository<Talent>		*rt = &Database::getRepository<Talent>();
    for (auto it = p.getTalents().begin() ; it != p.getTalents().end() ; ++it) {
      rt->smartUpdate(**it, isInTr);
    }

    /*
    ** Updating Stats
    */
    Repository<Stat>		*rStat = &Database::getRepository<Stat>();
    for (auto it = p.getStats().begin() ; it != p.getStats().end() ; ++it) {
      rStat->smartUpdate(**it, isInTr);
    }

    /*
    ** Updating Jobs
    */
    Repository<Job>		*rj = &Database::getRepository<Job>();
    for (auto it = p.getJobs().begin() ; it != p.getJobs().end() ; ++it) {
      rj->smartUpdate(**it, isInTr);
    }

    /*
    ** Updating Mobs
    */
    Repository<Mob>		*rm = &Database::getRepository<Mob>();
    for (auto it = p.getDigitaliser().begin() ; it != p.getDigitaliser().end() ; ++it) {
      rm->smartUpdate(**it, isInTr);
    }

    BaseRepository<Player>::smartUpdate(p, isInTr);

    /***
    **** The code above is correct
    ***/

    /*
    ** Updating Equipments
    */
    // Repository<Stuff>		*rStuff = &Database::getRepository<Stuff>();
    // for (auto it = p.getEquipment().begin() ; it != p.getEquipment().end() ; ++it) {
    //   rStuff->smartUpdate(**it, isInTr);
    // }

    if (t) {
      t->commit();
      delete t;
    }
  }
};

#endif
