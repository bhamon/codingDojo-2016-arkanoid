#include <cmath>
#include "Calculator.h"
#include "Ball.h"
#include "HitRecord.h"
#include "Brick.h"
#include "Racket.h"
#include "Vector2.h"
#include "Point2.h"
#include "Normal2.h"
#include "Field.h"

void
Calculator::move(Ball& ball, float factor)
{
	ball.position() += ball.getVelocity() * factor;
}

void
Calculator::bounce(Ball& ball, const math::Normal2<float>& normal)
{
	math::Vector2<float> projection(normal * (normal * -ball.getVelocity()));
	math::Vector2<float> perpendicular(ball.getVelocity() + projection);

	ball.setVelocity(projection + perpendicular);
}

bool
Calculator::hit(const Ball& ball, const Brick& brick, HitRecord& hitRecord)
{
	bool hit = false;
	HitRecord localHitRecord;

	if(Calculator::hit(ball, brick.getPosition() + math::Vector2<float>(-Brick::WIDTH / 2.0f, -Brick::HEIGHT / 2.0f), brick.getPosition() + math::Vector2<float>(+Brick::WIDTH / 2.0f, -Brick::HEIGHT / 2.0f), localHitRecord) && localHitRecord.getRollback() > hitRecord.getRollback())
	{
		hitRecord = localHitRecord; 
		hit = true;
	}

	if(Calculator::hit(ball, brick.getPosition() + math::Vector2<float>(+Brick::WIDTH / 2.0f, -Brick::HEIGHT / 2.0f), brick.getPosition() + math::Vector2<float>(+Brick::WIDTH / 2.0f, +Brick::HEIGHT / 2.0f), localHitRecord) && localHitRecord.getRollback() > hitRecord.getRollback())
	{
		hitRecord = localHitRecord;
		hit = true;
	}

	if(Calculator::hit(ball, brick.getPosition() + math::Vector2<float>(+Brick::WIDTH / 2.0f, +Brick::HEIGHT / 2.0f), brick.getPosition() + math::Vector2<float>(-Brick::WIDTH / 2.0f, +Brick::HEIGHT / 2.0f), localHitRecord) && localHitRecord.getRollback() > hitRecord.getRollback())
	{
		hitRecord = localHitRecord;
		hit = true;
	}

	if(Calculator::hit(ball, brick.getPosition() + math::Vector2<float>(-Brick::WIDTH / 2.0f, +Brick::HEIGHT / 2.0f), brick.getPosition() + math::Vector2<float>(-Brick::WIDTH / 2.0f, -Brick::HEIGHT / 2.0f), localHitRecord) && localHitRecord.getRollback() > hitRecord.getRollback())
	{
		hitRecord = localHitRecord;
		hit = true;
	}

	return hit;
}

bool
Calculator::hit(const Ball& ball, const Racket& racket, const Field& field, HitRecord& hitRecord)
{
	bool hit = false;
	HitRecord localHitRecord;

	//float y = field.getHeight() - Racket::OFFSET;

	//point en bas a gauche
	math::Point2<float> pt1(racket.getPosition().getX() - Racket::WIDTH / 2, racket.getPosition().getY() + Racket::HEIGHT / 2);
	//point en bas a droite
	math::Point2<float> pt2(racket.getPosition().getX() + Racket::WIDTH / 2, racket.getPosition().getY() + Racket::HEIGHT / 2);
	//point en haut a gauche
	math::Point2<float> pt3(racket.getPosition().getX() - Racket::WIDTH / 2, racket.getPosition().getY() - Racket::HEIGHT / 2);
	//point en haut a droite
	math::Point2<float> pt4(racket.getPosition().getX() + Racket::WIDTH / 2, racket.getPosition().getY() - Racket::HEIGHT / 2);

	// collision au dessus de la raquette
	if(Calculator::hit(ball,  pt3, pt4, localHitRecord) && localHitRecord.getRollback() > hitRecord.getRollback())
	{
		hitRecord = localHitRecord;
		hit = true;
	}

	// collision au dessous de la raquette
	if(Calculator::hit(ball, pt1, pt2, localHitRecord) && localHitRecord.getRollback() > hitRecord.getRollback())
	{
		hitRecord = localHitRecord;
		hit = true;
	}

	// collision à gauche de la raquette
	if(Calculator::hit(ball, pt1, pt3, localHitRecord) && localHitRecord.getRollback() > hitRecord.getRollback())
	{
		hitRecord = localHitRecord;
		hit = true;
	}

	// collision à droite de la raquette
	if(Calculator::hit(ball, pt4, pt2, localHitRecord) && localHitRecord.getRollback() > hitRecord.getRollback())
	{
		hitRecord = localHitRecord;
		hit = true;
	}

	return hit;
}

bool
Calculator::hit(const Ball& ball, const math::Point2<float>& start, const math::Point2<float>& end, HitRecord& hitRecord)
{
	// Checks if the ball crosses the line.
	std::tuple<math::Point2<float>, math::Point2<float>> ibs;
	if(!computeCircleSegmentIntersection(ball.getPosition(), Ball::RADIUS, start, end, ibs))
	{
		return false;
	}

	// The middle point along the line.
	math::Point2<float> middle(std::get<0>(ibs) +(std::get<1>(ibs) -std::get<0>(ibs)) / 2.0f);
	// The intersection point of the ball along its velocity vector and the brick edge.
	math::Point2<float> intersection;
	// No need to test if there is an intersection here as it's always true in our case because the ball crossed the brick edge.
	computeLineLineIntersection(
		ball.getPosition() - ball.getVelocity(),
		ball.getPosition(),
		start,
		end,
		intersection
	);

	// The vector between the ball center and the intersection point, directed towards the ball center for future use.
	math::Vector2<float> vbi(ball.getPosition() - intersection);
	// The distance between the ball center and the intersection point.
	float dbi = vbi.getMagnitude();
	// The vector between the ball center and the middle point, directed towards the middle point for future use.
	math::Vector2<float> vbm(middle - ball.getPosition());
	// The distance between the ball center and the middle point.
	float dbm = vbm.getMagnitude();
	// Thalès theorem to find the rollback length along the velocity vector so that the line will be a tangent of the ball.
	float rollback = Ball::RADIUS * dbi / dbm - dbi;

	// The magnitude of the velocity vector to normalize the rollback factors.
	float mv = ball.getVelocity().getMagnitude();
	// Checking that rollback is within the bounds.
	if(rollback <= 0.0f || rollback >= mv)
	{
		return false;
	}

	// Normalized vBI (the same as -ball.getVelocity().getNormalized(), but cheaper to compute).
	math::Vector2<float> vbiUnit(vbi / dbi);
	// The new ball position after the rollback.
	math::Point2<float> newPosition(ball.getPosition() + vbiUnit * rollback);

	// Normalized vBM (perpendicular to the brick edge, thus perfect to go from the new ball center to the hit point).
	math::Vector2<float> vbmUnit(vbm / dbm);
	// The hit point.
	math::Point2<float> hitPoint(newPosition + vbmUnit * Ball::RADIUS);

	// At this stage, the hit point is along the edge line, but can be outside the segment range.
	// The vector between the edge start and the hit point, directed toward the hit point.
	math::Vector2<float> vsh(hitPoint - start);
	// The vector between the edge start and the edge end, directed toward the edge end.
	math::Vector2<float> ves(end - start);
	// The dot product will hold the direction of the hit point against the edge start along the edge line.
	float dot = vsh * ves;
	if(dot < 0.0f)
	{
		// We are before the edge start on the line, use the start point as the hit point.
		hitRecord.setHitPoint(start);

		// Compute the new ball position such that the distance between the hit point and the sphere center equals the radius.
		// No need to test if there is an intersection here as it's always true in our case because the ball is against the brick corner.
		std::tuple<math::Point2<float>, math::Point2<float>> icv;
		computeCircleSegmentIntersection(
			start,
			Ball::RADIUS,
			ball.getPosition(),
			intersection,
			icv
		);

		hitRecord.setNewPosition(std::get<0>(icv));
		hitRecord.setNormal((hitRecord.getNewPosition() - start).getNormalized());
		hitRecord.setRollback((hitRecord.getNewPosition() - ball.getPosition()).getMagnitude() / mv);
	}
	else if(dot > ves.getSquaredMagnitude())
	{
		// We are after the edge end on the line., use the end point as the hit point.
		hitRecord.setHitPoint(end);

		// Compute the new ball position such that the distance between the hit point and the sphere center equals the radius.
		// No need to test if there is an intersection here as it's always true in our case because the ball is against the brick corner.
		std::tuple<math::Point2<float>, math::Point2<float>> icv;
		computeCircleSegmentIntersection(
			end,
			Ball::RADIUS,
			ball.getPosition(),
			intersection,
			icv
		);

		hitRecord.setNewPosition(std::get<0>(icv));
		hitRecord.setNormal((hitRecord.getNewPosition() - end).getNormalized());
		hitRecord.setRollback((hitRecord.getNewPosition() - ball.getPosition()).getMagnitude() / mv);
	}
	else
	{
		// We are still between the two edge points.
		hitRecord.setHitPoint(hitPoint);
		hitRecord.setNormal((end - start).getRightHand().normalize());
		hitRecord.setNewPosition(newPosition);
		hitRecord.setRollback(rollback / mv);
	}

	return true;
}

bool
Calculator::computeCircleSegmentIntersection(const math::Point2<float>& center, float radius, const math::Point2<float>& start, const math::Point2<float>& end, std::tuple<math::Point2<float>, math::Point2<float>>& result)
{
	math::Vector2<float> ves(end - start);
	math::Vector2<float> vsc(start - center);

	float a = ves * ves;
	float b = 2.0f * vsc * ves;
	float c = vsc * vsc - radius * radius;

	float discriminant = b * b - 4.0f * a * c;
	if(discriminant < 0.0f)
	{
		return false;
	}

	discriminant = std::sqrt(discriminant);

	// The two solutions along the line.
	float t1 = (-b - discriminant) / (2.0f * a);
	float t2 = (-b + discriminant) / (2.0f * a);

	// Check if it's inside the segment section.
	bool hit1 = t1 >= 0.0f && t1 <= 1.0f;
	bool hit2 = t2 >= 0.0f && t2 <= 1.0f;

	result = std::make_tuple(
		math::Point2<float>(start + ves * t1),
		math::Point2<float>(start + ves * t2)
	);

	// If at least one matches, there is a solution.
	return hit1 || hit2;
}

bool
Calculator::computeLineLineIntersection(const math::Point2<float>& p1, const math::Point2<float>& p2, const math::Point2<float>& p3, const math::Point2<float>& p4, math::Point2<float>& result)
{
	float dx1 = p1.getX() - p2.getX();
	float dx2 = p3.getX() - p4.getX();
	float dy1 = p1.getY() - p2.getY();
	float dy2 = p3.getY() - p4.getY();
	float d = dx1 * dy2 - dy1 * dx2;
	if(d == 0.0f)
	{
		return false;
	}

	float pre = p1.getX() * p2.getY() - p1.getY() * p2.getX();
	float post = p3.getX() * p4.getY() - p3.getY() * p4.getX();
	result = math::Point2<float>(
		(pre * dx2 - dx1 * post) / d,
		(pre * dy2 - dy1 * post) / d
	);

	return true;
}
