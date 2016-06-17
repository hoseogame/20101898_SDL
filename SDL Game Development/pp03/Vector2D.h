#pragma once
#include<math.h>
class Vector2D
{
public:

	Vector2D( float x, float y ) : m_x( x ), m_y( y ) {}
	Vector2D(): m_x(0), m_y(0)
	{
	}

	float getX() { return m_x; }

	float getY() { return m_y; }

	void setX( float x ) { m_x = x; }

	void setY( float y ) { m_y = y; }

	float length() { return sqrt( m_x * m_x + m_y * m_y ); }

	void normalize()

	{

		float l = length();

		if ( l > 0 ) // we never want to attempt to divide by 0

		{

			(*this) *= 1 / l;

		}

	}

	Vector2D operator+( const Vector2D& v2 ) const;
	friend Vector2D& operator+=( Vector2D& v1, const Vector2D& v2 );
	Vector2D operator*( float scalar );
	Vector2D& operator*=( float scalar );
	Vector2D operator-( const Vector2D& v2 ) const;
	friend Vector2D& operator-=( Vector2D& v1, const Vector2D& v2 );
	Vector2D operator/( float scalar );
	Vector2D& operator/=( float scalar );

	~Vector2D();

private:

	float m_x;

	float m_y;
};

