#pragma once

struct Point2f
{
	Point2f(float px, float py)
	{
		x = px; y = py;
	}
	float x{}, y{};

	Point2f operator+ (const Point2f& other) const
	{
		return Point2f(x + other.x, y + other.y);
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