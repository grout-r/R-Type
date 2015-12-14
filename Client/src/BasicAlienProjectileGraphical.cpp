#include "BasicAlienProjectileGraphical.h"

BasicAlienProjectileGrapical::BasicAlienProjectileGrapical(sf::Vector2f speed, sf::Vector2i pos, float coeff) :
	BasicAlienProjectile(speed, pos, coeff), GraphicalItem()
{
	_sprite->setTexture(*(ac->getShot(BASICALIENSHOT)));
	_sprite->setPosition(
		(_pos.x / SCREENRATIO) - (SHOT_ASSET_SIZE_Y / 2),
		(_pos.y / SCREENRATIO) - (SHOT_ASSET_SIZE_X / 2)
		);

}

bool BasicAlienProjectileGrapical::update()
{
  bool	ret;

  ret = BasicAlienProjectile::update();
	_sprite->setPosition(
		(_pos.x / SCREENRATIO) - (SHOT_ASSET_SIZE_Y / 2),
		(_pos.y / SCREENRATIO) - (SHOT_ASSET_SIZE_Y / 2)
		);
	return (ret);
}