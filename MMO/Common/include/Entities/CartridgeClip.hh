//
// CartridgeClip.hh for CartridgeClip in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Wed Mar 26 01:14:04 2014 alexis mestag
// Last update Wed Mar 26 02:45:43 2014 alexis mestag
//

#ifndef				__CARTRIDGECLIP_HH__
# define			__CARTRIDGECLIP_HH__

# include			<map>
# include			<list>
# include			"Entities/Cartridge.hh"
# include			"Utility/Wrapper.hpp"

class				CartridgeClip : public ContainerWrapper<std::list<Cartridge *> >
{
public:
  typedef std::map<Cartridge::efficiency_type, unsigned int>	summary_type;

private:
  summary_type			*_sum;

public:
  CartridgeClip();
  virtual ~CartridgeClip();

  CartridgeClip(CartridgeClip const &rhs);

  CartridgeClip			&operator=(CartridgeClip const &rhs);

private:
  void				emptyClip();
  // summary_type const		&getSum() const;
  // void				setSum(summary_type const &sum);

public:
  void				addCartridge(Cartridge const &cartridge);
  Cartridge			*getNextCartridge(); // Removes one cartridge from the container

  container_type const		&getClip() const;
  void				setClip(container_type const &c);

public:
  summary_type const		&getClipSummary() const;
  void				setClipFromSummary(summary_type const &c);
};

#endif
