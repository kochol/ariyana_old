#pragma once

namespace ari
{
	template <class T>
	struct Rect
	{
		Rect() : x(0), y(0), width(0), height(0) { }

		Rect(const T _x, const T _y, const T _width, const T _height):
			x(_x), y(_y), width(_width), height(_height) { }

		void Set(const T _x, const T _y, const T _width, const T _height)
		{
			x      = _x;
			y      = _y;
			width  = _width;
			height = _height;
		}

		bool operator == (const Rect<T> &v) const
		{
			return (width == v.width && height == v.height && x == v.x && y == v.y);
		}

		bool operator != (const Rect<T> &v) const
		{
			return (width != v.width || height != v.height || x != v.x || y != v.y);
		}

		union
		{
			T p[4];
			struct 
			{
				T	x,
					y,
					width,
					height;
			};
		};
	};

	typedef Rect<uint16_t>	RectU16;
	typedef Rect<int>		RectI;
	typedef Rect<float>		RectF;

} // ari
