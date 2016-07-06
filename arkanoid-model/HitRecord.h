#ifndef HIT_RECORD_H
#define HIT_RECORD_H

#include "Point2.h"
#include "Normal2.h"

class HitRecord
{
	private:
	math::Point2<float> _hitPoint;
	math::Normal2<float> _normal;
	math::Point2<float> _newPosition;
	float _rollback;

	public:
	HitRecord();
	~HitRecord();

	const math::Point2<float> getHitPoint() const;
	const math::Normal2<float> getNormal() const;
	const math::Point2<float> getNewPosition() const;
	float getRollback() const;

	void setHitPoint(const math::Point2<float>& hitPoint);
	void setNormal(const math::Normal2<float>& normal);
	void setNewPosition(const math::Point2<float>& newPosition);
	void setRollback(float rollback);

	math::Point2<float>& hitPoint();
	math::Normal2<float>& normal();
	math::Point2<float>& newPosition();
	float& rollback();
};

#endif
