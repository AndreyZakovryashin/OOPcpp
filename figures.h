class Named
{
public:
	Named();
	Named(std::string _name);
protected:
	std::string name;
};

class Printable : public virtual Named
{
public:
	virtual void Print() const;
};

//Printable - for Print(), Named - for constructor.
class Shape : public Printable, public virtual Named
{
public:
	Shape();
	Shape(std::string _name);
	static unsigned int GetCount();
	~Shape();
private:
	static unsigned int count;
};


class Point : public Shape
{
public:
	Point();
	Point(std::string _name, double _x, double _y);
	void Print() const;
	double GetX() const; //for Polyline::length
	double GetY() const;
protected:
	double x, y;
};

class Circle : public Point
{
public:
	Circle();
	Circle(std::string _name, double _x, double _y, double _radius);
	double GetArea() const;
	void Print() const;
private:
	double radius;
};

class Rect : public Point
{
public:
	Rect();
	Rect(std::string _name, double _x, double _y, double _width, double _height);
	double GetArea() const;
	void Print() const;
protected:
	double width, height;
};

class Square : public Rect
{
public:
	Square();
	Square(std::string _name, double _x, double _y, double _length);
	void Print() const;
private:
	double length;
};

class Polyline : public Shape
{
public:
	Polyline();
	Polyline(std::string _name);
	void AddPoint(const Point & _point);
	double GetLength() const;
	void Print() const;
private:
	XList <Point> points;
	double length;
};


