#ifndef CATEGORY_HPP
#define CATEGORY_HPP


// Entity/scene node category, used to dispatch commands
namespace Category
{
	enum Type
	{
		None				= 0,
		Scene				= 1 << 0, //00000001 = 1
		PlayerAircraft		= 1 << 1, //00000010 = 2
		AlliedAircraft		= 1 << 2, //00000100 = 4
		EnemyAircraft		= 1 << 3, //00001000 = 8
	};
}

#endif //CATEGORY_HPP