#include <iostream>
#include <cstdlib>

using namespace std;

long rCalcPoly(int x, const int c[], int degree);
void rShowPoly(int x, const int c[], int degree, long value);
// write prototype for rShowPolyAux here
void rShowPolyAux(int x, const int c[], int degree, long value, int term);

int main()
{
   int coeff[] = {-1, 8, -4, 7, 0, -3, -6, 2, 5};

   rShowPoly( -2, coeff, 0, rCalcPoly(-2, coeff, 0) );
   rShowPoly( -1, coeff, 0, rCalcPoly(-1, coeff, 0) );
   rShowPoly( 0, coeff, 0, rCalcPoly(0, coeff, 0) );
   rShowPoly( 1, coeff, 0, rCalcPoly(1, coeff, 0) );
   rShowPoly( 2, coeff, 0, rCalcPoly(2, coeff, 0) );
   cout << endl;
   rShowPoly( -2, coeff, 1, rCalcPoly(-2, coeff, 1) );
   rShowPoly( -1, coeff, 1, rCalcPoly(-1, coeff, 1) );
   rShowPoly( 0, coeff, 1, rCalcPoly(0, coeff, 1) );
   rShowPoly( 1, coeff, 1, rCalcPoly(1, coeff, 1) );
   rShowPoly( 2, coeff, 1, rCalcPoly(2, coeff, 1) );
   cout << endl;
   rShowPoly( -2, coeff, 3, rCalcPoly(-2, coeff, 3) );
   rShowPoly( -1, coeff, 3, rCalcPoly(-1, coeff, 3) );
   rShowPoly( 0, coeff, 3, rCalcPoly(0, coeff, 3) );
   rShowPoly( 1, coeff, 3, rCalcPoly(1, coeff, 3) );
   rShowPoly( 2, coeff, 3, rCalcPoly(2, coeff, 3) );
   cout << endl;
   rShowPoly( -2, coeff, 5, rCalcPoly(-2, coeff, 5) );
   rShowPoly( -1, coeff, 5, rCalcPoly(-1, coeff, 5) );
   rShowPoly( 0, coeff, 5, rCalcPoly(0, coeff, 5) );
   rShowPoly( 1, coeff, 5, rCalcPoly(1, coeff, 5) );
   rShowPoly( 2, coeff, 5, rCalcPoly(2, coeff, 5) );
   cout << endl;
   rShowPoly( -2, coeff, 8, rCalcPoly(-2, coeff, 8) );
   rShowPoly( -1, coeff, 8, rCalcPoly(-1, coeff, 8) );
   rShowPoly( 0, coeff, 8, rCalcPoly(0, coeff, 8) );
   rShowPoly( 1, coeff, 8, rCalcPoly(1, coeff, 8) );
   rShowPoly( 2, coeff, 8, rCalcPoly(2, coeff, 8) );
   cout << endl;

   return EXIT_SUCCESS;
}

// write definition for rCalcPoly here
long rCalcPoly(int x, const int c[], int degree)
{
   if (degree == 0)
      return c[0];

   return (c[0] + x * rCalcPoly(x, c + 1, degree - 1));
}

// write definition for rShowPoly here
void rShowPoly(int x, const int c[], int degree, long value)
{
   rShowPolyAux(x, c, degree, value, degree);
}

// write definition for rShowPolyAux here
void rShowPolyAux(int x, const int c[], int degree, long value, int term)
{
   if (degree == 0 && term == 0)
   {
      cout << "p(x,n) = p(" << x << "," << term << ") = " << c[0] << "x^0 "
           << "= " << value << endl;

      return;
   }
   else if (degree == 0)
   {
      cout << "p(x,n) = p(" << x << "," << term << ") = " << c[0] << "x^0 ";

      return;
   }

   rShowPolyAux(x, c, degree - 1, value, term);

   // for positive coefficients
   if (c[degree] > 0)
      cout << "+";

   cout << c[degree] << "x^" << degree << " ";

   if (degree == term)
      cout << " = " << value << endl;
}
