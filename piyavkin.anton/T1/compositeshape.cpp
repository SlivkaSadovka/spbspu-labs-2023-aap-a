#include "compositeshape.hpp"
#include "inputshape.hpp"
#include "isoscale.hpp"

namespace piyavkin
{
  CompositeShape::CompositeShape():
    CompositeShape(0)
  {}
  CompositeShape::CompositeShape(size_t capacity):
    shapes_(new Shape* [capacity]{}),
    size_(0),
    capacity_(capacity)
  {}
  CompositeShape::~CompositeShape()
  {
    clearMemory(shapes_, size_);
  }
  CompositeShape::CompositeShape(CompositeShape&& cs)
  {
    swap(cs);
  }
  CompositeShape& CompositeShape::operator=(CompositeShape&& cs)
  {
    swap(cs);
    return *this;
  }
  void swap(CompositeShape& cs)
  {
    std::swap(shapes_, cs.shapes_);
    std::swap(size_, cs.size_);
    std::swap(capacity, cs.capacity);
  }
  double CompositeShape::getArea() const
  {
    double sum = 0;
    for (size_t i = 0; i < size_; ++i)
    {
      sum += shapes_[i]->getArea();
    }
    return sum;
  }
  size_t CompositeShape::size() const
  {
    return size_;
  }
  bool CompositeShape::empty() const
  {
    return size_ == 0;
  }
  rectangle_t CompositeShape::getFrameRect() const
  {
    double minX = shapes_[0]->getFrameRect().pos.x - shapes_[0]->getFrameRect().width / 2;
    double minY = shapes_[0]->getFrameRect().pos.y - shapes_[0]->getFrameRect().height / 2;
    double maxX = shapes_[0]->getFrameRect().pos.x + shapes_[0]->getFrameRect().width / 2;
    double maxY = shapes_[0]->getFrameRect().pos.y + shapes_[0]->getFrameRect().height / 2;
    for (size_t i = 1; i < size_; ++i)
    {
      if (minX > shapes_[i]->getFrameRect().pos.x - shapes_[i]->getFrameRect().width / 2)
      {
        minX = shapes_[i]->getFrameRect().pos.x - shapes_[i]->getFrameRect().width / 2;
      }
      else if (maxX < shapes_[i]->getFrameRect().pos.x + shapes_[i]->getFrameRect().width / 2)
      {
        maxX = shapes_[i]->getFrameRect().pos.x + shapes_[i]->getFrameRect().width / 2;
      }
      if (minY > shapes_[i]->getFrameRect().pos.y - shapes_[i]->getFrameRect().height / 2)
      {
        minY = shapes_[i]->getFrameRect().pos.y - shapes_[i]->getFrameRect().height / 2;
      }
      else if (maxY < shapes_[i]->getFrameRect().pos.y + shapes_[i]->getFrameRect().height / 2)
      {
        maxY = shapes_[i]->getFrameRect().pos.y + shapes_[i]->getFrameRect().height / 2;
      }
    }
    return {maxX - minX, maxY - minY, {(maxX + minX) / 2, (maxY + minY) / 2}};
  }
  void CompositeShape::move(double dx, double dy)
  {
    for (size_t i = 0; i < size_; ++i)
    {
      shapes_[i]->move(dx, dy);
    }
  }
  void CompositeShape::move(const point_t& bias)
  {
    point_t pos = getFrameRect().pos;
    move(bias.x - pos.x, bias.y - pos.y);
  }
  void CompositeShape::scale(double k)
  {
    if (k < 0)
    {
      throw std::logic_error("Сoefficient less than 0");
    }
    point_t posComposite = getFrameRect().pos;
    for (size_t i = 0; i < size_; ++i)
    {
      isoScale(shapes_[i], posComposite, k);
    }
  }
  void CompositeShape::push_back(Shape* shape)
  {
    if (capacity_ == size_)
    {
      capacity_ += 10;
      Shape** oldShapes = shapes_;
      shapes_ = new Shape* [capacity_] {};
      if (oldShapes)
      {
        for (size_t i = 0; i < size_; ++i)
        {
          shapes_[i] = oldShapes[i];
        }
        delete[] oldShapes;
      }
    }
    shapes_[size_++] = shape;
  }
  void CompositeShape::pop_back()
  {
    delete shapes_[size_--];
  }
  Shape& CompositeShape::at(size_t i)
  {
    return const_cast< Shape& >(static_cast< const CompositeShape& >(*this).at(i));
  }
  const Shape& CompositeShape::at(size_t i) const
  {
    if (i > size_)
    {
      throw std::logic_error("Segmential fault");
    }
    return *shapes_[i];
  }
  Shape& CompositeShape::operator[](size_t i)
  {
    return *shapes_[i];
  }
  const Shape& CompositeShape::operator[](size_t i) const
  {
    return *shapes_[i];
  }
}
