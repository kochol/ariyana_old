#pragma once

namespace ari
{
	template <class T>
	struct Rect
	{
		Rect() : top(0), left(0), right(0), bottom(0) { }

		Rect(const T _top, const T _left, const T _bottom, const T _right):
			top(_top), left(_left), bottom(_bottom), right(_right) { }

		void Set(const T _top, const T _left, const T _bottom, const T _right)
		{
			top    = _top;
			left   = _left;
			right  = _right;
			bottom = _bottom;
		}

		union
		{
			T p[4];
			struct 
			{
				T	top,
					left,
					bottom,
					right;
			};
		};
	};

	typedef Rect<int>   RectI;
	typedef Rect<float> RectF;

} // ari
