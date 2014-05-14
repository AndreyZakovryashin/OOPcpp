#include <iostream>
#include <string>
#include "figures.h"

double static const pi = 3.1415926535897932;

Named::Named()
{
}
Named::Named(std::string _name)
{
	name = _name;
}

void Printable::Print() const
{
	std::cout << name << std::endl;
}

Shape::Shape()
{
}
Shape::Shape(std::string _name) : Named(_name)
{
	++count;
}
unsigned int Shape::GetCount()
{
	return count;
}
Shape::~Shape()
{
	--count;
}

Point::Point()
{
}
Point::Point(std::string _name, double _x, double _y) : Shape(_name)
{
	x = _x;
	y = _y;
}
double Point::GetX() const
{
	return x;
}
double Point::GetY() const
{
	return y;
}	
void Point::Print() const
{
	std::cout << name << ", x = " << x << ", y = " << y << std::endl;
}

Circle::Circle(std::string _name, double _x, double _y, double _radius) : Point (_name, _x, _y)
{
	radius = _radius;
}
double Circle::GetArea() const
{
	return pi * radius * radius;
}
void Circle::Print() const
{
	std::cout << name << ", x = " << x << ", y = " << y << ", radius = " << radius
			  << ", area = " << GetArea() << std::endl;
}

Rect::Rect(std::string _name, double _xtop, double _ytop, double _xlength, double _ylength) : Shape(_name)
{
	xtop = _xtop;
	ytop = _ytop;
	xlength = _xlength;
	ylength = _ylength;
}
double Rect::GetArea() const
{
	return xlength * ylength;
}
void Rect::Print() const
{
	std::cout << name << ", xtop = " << xtop << ", ytop = " << ytop << ", xlength = " << xlength 
				<< ", ylength = " << ylength <<  ", area = " << GetArea() << std::endl;
}

Square::Square(std::string _name, double _xtop, double _ytop, double _length) : Rect(_name, _xtop, _ytop, _length, _length)
{
	length = xlength;
	Rect(_name, _xtop, _ytop, _length, _length);
}
void Square::Print() const
{
	std::cout << name << ", xtop = " << xtop << ", ytop = " << ytop << ", length = " << length 
				<<  ", area = " << GetArea() << std::endl;
}

Polyline::Polyline(std::string _name) : Shape(_name) 
{
	length = 0;
}	

void Polyline::AddPoint(const Point & _point) 
{
	if(points.Empty())
		length = 0;
	else
		length += sqrt((_point.GetX() - points.GetValueLast()->GetX()) * (_point.GetX() - points.GetValueLast()->GetX()) 
			+ (_point.GetY() - points.GetValueLast()->GetY()) * (_point.GetY() - points.GetValueLast()->GetY()));
	points.AddToEnd(_point); 
	delete & _point;
}
double Polyline::GetLength() const
{
	return length;
}
void Polyline::Print() const
{
	std::cout << name << ", length = " << length << std::endl;
	for(unsigned int i = 0; i < points.GetCount(); ++i)
		points.GetValue(i)->Print();
}

unsigned int Shape::count = 0;

int main()
{
	XList<Shape> * figures = new XList<Shape>();
	Point * point1 = new Point("Point1", 10, 10);
	Circle * circle1 = new Circle("Circle1", 20, 10, 5);
	Rect * rect1 = new Rect("Rect1", 15, 25, 25, 30);
	Square * square1 = new Square("Square1", 30, 25, 10);
	Polyline * polyline1 = new Polyline("polyline1");
	Point * p1 = new Point("p1", 1, 0);
	Point * p2 = new Point("p2", 5, 10);
	Point * p3 = new Point("p3", -100, 10);
	polyline1->AddPoint(* p1);
	polyline1->AddPoint(* p2);
	polyline1->AddPoint(* p3);

	figures->AddToTop(* point1);
	figures->AddToTop(* circle1);
	figures->AddToTop(* rect1);
	figures->AddToTop(* square1);
	figures->AddToTop(* polyline1);
	std::cout << Shape::GetCount() << std::endl;

	for(unsigned int i = 0; i < figures->GetCount(); ++i)
	{
		figures->GetValue(i)->Print();
	}
	try 
	{
		figures->GetValue(figures->GetCount() + 1)->Print();
	}
	catch(std::string & error)
	{
		std::cerr << error << std::endl;
	}	

	figures->RemoveAll();

	std::cout << Shape::GetCount() << std::endl;

	try 
	{
		figures->GetLast();
	}
	catch(std::string & error)
	{
		std::cerr << error << std::endl;
	}		
	return 0;
}