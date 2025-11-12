
#include <cmath>
#include <cstdlib>
#include <iostream>


// -------------------------------------------------------------------------
struct Point
{
  float X, Y, Z;
  float distanceTo( const Point& b ) const
    {
      float x = X - b.X;
      float y = Y - b.Y;
      float z = Z - b.Z;
      return( std::sqrt( ( x * x ) + ( y * y ) + ( z * z ) ) );
    }

    /*Para que el map pueda ordenar las claves es necesario sobreescribir el operador <, ya que como la clave es un tipo de 
        dato definido por el usuario el map no sabe cómo ordenarlo. Así que se ordenará por coordenada.
        Con esta sobrecarga el map podrá comprobar si una coordenada B < A o si B = A o si B > A
    */
    bool operator<(const Point& other) const {
        if (X != other.X) return X < other.X;
        if (Y != other.Y) return Y < other.Y;
        return Z < other.Z;
    }

    bool operator==(const Point& other) const {
    // Dos puntos son iguales si y solo si sus tres coordenadas son iguales.
    return (X == other.X && Y == other.Y && Z == other.Z);
    }
};