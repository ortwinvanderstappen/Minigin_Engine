#pragma once

struct Point2f
{
	float x{}, y{};
	
	Point2f() :
		Point2f(0.f, 0.f)
	{}

	Point2f(float px, float py)
	{
		x = px; y = py;
	}

	Point2f operator+ (const Point2f& other) const
	{
		return Point2f(x + other.x, y + other.y);
	}

	Point2f operator*(float scalar) const
	{
		return Point2f(x * scalar, y * scalar);
	}

	float Distance(const Point2f& other) const
	{
		return abs(Length() - other.Length());
	}

	float Length() const
	{
		return static_cast<float>(sqrt(x*x + y*y));
	}
};

struct Point2i
{
	Point2i() {};
	Point2i(int px, int py)
	{
		x = px;
		y = py;
	}

	int x{}, y{};
};

struct Recti
{
	Recti() {}

	Recti(int px, int py, int width, int height)
	{
		x = px; y = py;
		w = width; h = height;
	}

	int x{}; int y{};
	int w{}; int h{};
};

struct Rectf
{
	Rectf() {}
	Rectf(float px, float py, float width, float height)
	{
		x = px; y = py;
		w = width; h = height;
	}

	float x{}; float y{};
	float w{}; float h{};
};

struct Color3i
{
	int r{}; int g{}; int b{};
};

struct Color3f
{
	float r{}; float g{}; float b{};
};