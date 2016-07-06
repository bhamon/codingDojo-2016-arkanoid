#include "HitRecord.h"

HitRecord::HitRecord()
	: _hitPoint()
	, _normal()
	, _newPosition()
	, _rollback(0.0f)
{
}

HitRecord::~HitRecord()
{
}

const math::Point2<float> HitRecord::getHitPoint() const
{
	return _hitPoint;
}

const math::Normal2<float> HitRecord::getNormal() const
{
	return _normal;
}

const math::Point2<float> HitRecord::getNewPosition() const
{
	return _newPosition;
}

float HitRecord::getRollback() const
{
	return _rollback;
}

void HitRecord::setHitPoint(const math::Point2<float>& hitPoint)
{
	_hitPoint = hitPoint;
}

void HitRecord::setNormal(const math::Normal2<float>& normal)
{
	_normal = normal;
}

void HitRecord::setNewPosition(const math::Point2<float>& newPosition)
{
	_newPosition = newPosition;
}

void HitRecord::setRollback(float rollback)
{
	_rollback = rollback;
}

math::Point2<float>& HitRecord::hitPoint()
{
	return _hitPoint;
}

math::Normal2<float>& HitRecord::normal()
{
	return _normal;
}

math::Point2<float>& HitRecord::newPosition()
{
	return _newPosition;
}

float& HitRecord::rollback()
{
	return _rollback;
}
