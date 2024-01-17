#include "triangle.hpp"
#include <cmath>
#include <algorithm>
#include <stdexcept>



#include <iostream>
strelyaev::Triangle::Triangle(point_t p1, point_t p2, point_t p3):
  p1_(p1),
  p2_(p2),
  p3_(p3)
{
  double determinant = p1_.x * (p2_.y - p3_.y) - p2_.x * (p1_.y - p3_.y) + p3_.x * (p1_.y - p2_.y);
  if (determinant == 0)
  {
    throw std::invalid_argument("Invalid points for TRIANGLE");
  }
}

double strelyaev::Triangle::getDistance(const point_t p1, const point_t p2) const
{
  return std::sqrt(std::pow(p2.x - p1.x, 2) + std::pow(p2.y - p1.y, 2));
}


double strelyaev::Triangle::getArea() const
{
  double a = Triangle::getDistance(p1_, p2_);
  double b = Triangle::getDistance(p2_, p3_);
  double c = Triangle::getDistance(p3_, p1_);
  double half_per = (a + b + c) / 2.0;
  return std::sqrt(half_per * (half_per - a) * (half_per - b) * (half_per - c));
}

strelyaev::rectangle_t strelyaev::Triangle::getFrameRect() const
{
  double up = std::max(p1_.y, std::max(p2_.y, p3_.y));
  double down = std::min(p1_.y, std::min(p2_.y, p3_.y));
  double right = std::max(p1_.x, std::max(p2_.x, p3_.x));
  double left = std::min(p1_.x, std::min(p2_.x, p3_.x));
  point_t r_p1 = {left, down};
  point_t r_p2 = {left, up};
  point_t r_p3 = {right, up};
  point_t r_p4 = {right, down};
  double height = up - down;
  double width = right - left;
  double r_center_x = (r_p1.x + r_p2.x + r_p3.x + r_p4.x) / 4;
  double r_center_y = (r_p1.y + r_p2.y + r_p3.y + r_p4.y) / 4;
  point_t r_center = {r_center_x, r_center_y};
  rectangle_t rect = {width, height, r_center};
  return rect;

}

void strelyaev::Triangle::move(const point_t point)
{
  double tr_center_x = (p1_.x + p2_.x + p3_.x) / 3;
  double tr_center_y = (p1_.y + p2_.y + p3_.y) / 3;
  point_t tr_center = {tr_center_x, tr_center_y};
  double dx = point.x - tr_center.x;
  double dy = point.y - tr_center.y;
  p1_.x += dx;
  p2_.x += dx;
  p3_.x += dx;
  p1_.y += dy;
  p2_.y += dy;
  p3_.y += dy;
}



void strelyaev::Triangle::move(double dx, double dy)
{
  p1_.x += dx;
  p2_.x += dx;
  p3_.x += dx;
  p1_.y += dy;
  p2_.y += dy;
  p3_.y += dy;
}

void strelyaev::Triangle::scale(double k)
{
  double tr_center_x = (p1_.x + p2_.x + p3_.x) / 3;
  double tr_center_y = (p1_.y + p2_.y + p3_.y) / 3;
  point_t tr_center = {0, 0};

  p1_.x = tr_center.x + (p1_.x - tr_center.x) * k;
  p1_.y = tr_center.y + (p1_.y - tr_center.y) * k;

  p2_.x = tr_center.x + (p2_.x - tr_center.x) * k;
  p2_.y = tr_center.y + (p2_.y - tr_center.y) * k;

  p3_.x = tr_center.x + (p3_.x - tr_center.x) * k;
  p3_.y = tr_center.y + (p3_.y - tr_center.y) * k;
}

