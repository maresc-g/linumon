//
// Cartridge.hh for Cartridge in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Wed Mar 26 01:27:40 2014 alexis mestag
// Last update Wed Mar 26 02:36:21 2014 alexis mestag
//

#ifndef				__CARTRIDGE_HH__
# define			__CARTRIDGE_HH__

class				Cartridge
{
public:
  typedef double		efficiency_type;
private:
  efficiency_type		_efficiency;

public:
  Cartridge(double const efficiency = 1.0);
  Cartridge(Cartridge const &rhs);
  virtual ~Cartridge();

  Cartridge			&operator=(Cartridge const &rhs);
  bool				operator==(Cartridge const &rhs) const;
  bool				operator!=(Cartridge const &rhs) const;
  bool				operator<(Cartridge const &rhs) const;
  bool				operator>=(Cartridge const &rhs) const;
  bool				operator>(Cartridge const &rhs) const;
  bool				operator<=(Cartridge const &rhs) const;

public:
  efficiency_type		getEfficiency() const;
  void				setEfficiency(efficiency_type const eff);
};

#endif
