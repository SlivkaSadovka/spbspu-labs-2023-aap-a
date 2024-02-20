#include "rectangle.hpp"
#include <stdexcept>
#include "figureFunction.hpp"

rebdev::Rectangle::Rectangle(const point_t & firstAngle, const point_t & secondAngle):
  angles_{firstAngle, secondAngle}
{
  if ((angles_[0].x >= angles_[1].x) || (angles_[0].y >= angles_[1].y))
  {
    throw std::logic_error("rectangle error");
  }
}

double rebdev::Rectangle::getArea() const
{
  return ((angles_[1].x - angles_[0].x) * (angles_[1].y - angles_[0].y));
}

rebdev::rectangle_t rebdev::Rectangle::getFrameRect() const
{
  return getFrameRectangle(angles_, 2);
}

void rebdev::Rectangle::move(const point_t & point)
{
  rectangle_t frameRectangle = getFrameRect();
  move(point.x - frameRectangle.pos.x, point.y - frameRectangle.pos.y);
}

void rebdev::Rectangle::move(double x, double y)
{
  movePoints(x, y, angles_, 2);
}

void rebdev::Rectangle::scale(double k)
{
  scaleFigure(angles_, 2, getFrameRect().pos, k);
}
