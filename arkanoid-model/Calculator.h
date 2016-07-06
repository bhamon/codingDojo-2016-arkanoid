#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <tuple>

namespace math { template<class T> class Point2; }
namespace math { template<class T> class Normal2; }
class Brick;
class Ball;
class HitRecord;

class Calculator
{
	public:
	/*
		@desc				Move the ball by its velocity vector for the provided factor.
		@param ball			The Ball.
		@param factor		The factor to apply to the velocity vector.
	*/
	static void move(Ball &ball, float factor);

	/*
		@desc				Bounce the ball velocity vector against an imaginary wall represented by the provided normal.
		@param ball			The ball.
		@param normal		The wall normal.
	*/
	static void bounce(Ball& ball, const math::Normal2<float>& normal);

	/*
		@desc					Tests if the ball hits the provided  brick.
								We make the assumption that the overall movement is negligible over the brick min(width, height).
								Thus we don't check if the ball is inside the brick (aka. if there is a collision, the ball cross one of the brick's edges).
		@param ball				The ball.
		@param brick			The brick to consider.
		@param hitRecord		The hit record in case of collision.
		@returns				The collision state of the ball against the provided brick.
	*/
	static bool hit(const Ball& ball, const Brick& brick, HitRecord& hitRecord);

	/*
		@desc					Tests whether the ball hit with the provided (start , end) segment or not.
								If the circle crosses the segment line, the two resulting points will be returned even if the function returns false.
		@param ball				The ball.
		@param start			The start point of the segemnt.
		@param end				The end point of the segment.
		@param hitRecord		The hit record in case of collision.
		@returns				The collision state of the ball against the provided segment.
	*/
	static bool hit(const Ball& ball, const math::Point2<float>& start, const math::Point2<float>& end, HitRecord& hitRecord);

	/*
		@desc				Computes the intersection points of a circle and a line with a segment restriction.
							The circle equation is infered from its center and radius.
							The line equation is infered from the two points (start, end).
		@param center		The circle center.
		@param radius		The circle radius.
		@param start		The segment start point.
		@param end			The segment end point.
		@param result		The intersection points along the line in case of match.
		@return				True if the circle crosses the segment, false otherwise.
	*/
	static bool computeCircleSegmentIntersection(const math::Point2<float>& center, float radius, const math::Point2<float>& start, const math::Point2<float>& end, std::tuple<math::Point2<float>, math::Point2<float>>& result);

	/*
		@desc				Computes the intersection point of two lines.
							The lines equations are respectively infered from two points: (p1, p2) for the first line and (p3, p4) for the second one.
		@param p1			A point on the first line.
		@param p2			A point on the first line.
		@param p3			A point on the second line.
		@param p4			A point on the second line.
		@param result		The intersection point in case of match.
		@returns			True if the two lines cross each other, false otherwise (if the two lines are parallel or p1 = p2 or p3 = p4).
	*/
	static bool computeLineLineIntersection(const math::Point2<float>& p1, const math::Point2<float>& p2, const math::Point2<float>& p3, const math::Point2<float>& p4, math::Point2<float>& result);
};


#endif