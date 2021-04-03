#include <iostream>
#include <cmath>
using namespace std ;
int main()
{
	char a[17][65]  ;
	int b[4] , c[4] ;
	float x[17][65] , y[17][65] ;
	int i , j ;
	
	for (i=0;i<=16;i++)
	{
		for(j=0;j<=64;j++)
		{
			x[i][j] = (-8) + 0.25 * j ;
			y[i][j] = 4 - 0.5 * i ;
		}
	}
	
	cout << "f(x , y) = 4y - x^2 + 8" << endl ;
	for (i=0;i<=16;i++)
	{
		for (j=0;j<=64;j++)
		{
			if ( 4 * y[i][j] - pow(x[i][j] , 2) + 8 >= 0 ) a[i][j] = '+' ;
			else a[i][j] = '-' ;
		}
	}
	
	for (i=0;i<8;i=i+2) b[i/2] = 4-i/2 ;
	for (i=10;i<=16;i=i+2) c[(i-10)/2] = (i-8) / 2 ;

	for (i=0;i<=7;i++)
	{
		for (j=0;j<=31;j++)
		{
			cout << a[i][j] ;
		}
		if(i%2==0) cout << b[i/2] ;
		else cout << a[i][32] ;
		for (j=33;j<=64;j++)
		{
			cout << a[i][j] ;
		}
		cout << '\n' ;
		
	}
	
	for (j=0;j<=32;j++)
	{
		if (j%4==0) cout << 8-j/4 ;
		else cout << a[8][j] ;
	}
	for (j=33;j<=64;j++)
	{
		if (j%4==0) cout << j/4-8 ;
		else cout << a[8][j] ;
	}
	cout << "\n" ;
	
	for (i=9;i<=16;i++)
	{
		for(j=0;j<=31;j++)
		{
			cout << a[i][j] ;
		}
		if (i%2==0) cout << c[(i-10)/2] ;
		else cout << a[i][32] ;
		for (j=33;j<=64;j++)
		{
			cout << a[i][j] ;
		}
		cout << "\n" ;
	}
	
	cout << "f(x,y) = 8y^2 + x^2 - 40" << endl;

	for (i=0;i<=16;i++)
	{
		for (j=0;j<=64;j++)
		{
			if ( 8 * pow(y[i][j] , 2 ) + pow(x[i][j] , 2) - 40 >= 0 ) a[i][j] = '+' ;
			else a[i][j] = '-' ;
		}
	}
	
	for (i=0;i<=7;i++)
	{
		for (j=0;j<=31;j++)
		{
			cout << a[i][j] ;
		}
		if(i%2==0) cout << b[i/2] ;
		else cout << a[i][32] ;
		for (j=33;j<=64;j++)
		{
			cout << a[i][j] ;
		}
		cout << '\n' ;
		
	}
	
	for (j=0;j<=32;j++)
	{
		if (j%4==0) cout << 8-j/4 ;
		else cout << a[8][j] ;
	}
	for (j=33;j<=64;j++)
	{
		if (j%4==0) cout << j/4-8 ;
		else cout << a[8][j] ;
	}
	cout << "\n" ;
	
	for (i=9;i<=16;i++)
	{
		for(j=0;j<=31;j++)
		{
			cout << a[i][j] ;
		}
		if (i%2==0) cout << c[(i-10)/2] ;
		else cout << a[i][32] ;
		for (j=33;j<=64;j++)
		{
			cout << a[i][j] ;
		}
		cout << "\n" ;
	}
	
	cout << "f(x,y) = (x^2 + 3y^2 - 10)^3 - 50 * x^2 * y^3" << endl;
	
	for (i=0;i<=16;i++)
	{
		for (j=0;j<=64;j++)
		{
			if ( pow ( pow (x[i][j] , 2) + 3 * pow ( y[i][j] , 2) - 10 , 3 ) - 50 * pow ( x[i][j] , 2 ) * pow ( y[i][j] , 3 ) >= 0 ) a[i][j] = '+' ;
			else a[i][j] = '-' ;
		}
	}
	
	for (i=0;i<=7;i++)
	{
		for (j=0;j<=31;j++)
		{
			cout << a[i][j] ;
		}
		if(i%2==0) cout << b[i/2] ;
		else cout << a[i][32] ;
		for (j=33;j<=64;j++)
		{
			cout << a[i][j] ;
		}
		cout << '\n' ;
		
	}
	
	for (j=0;j<=32;j++)
	{
		if (j%4==0) cout << 8-j/4 ;
		else cout << a[8][j] ;
	}
	for (j=33;j<=64;j++)
	{
		if (j%4==0) cout << j/4-8 ;
		else cout << a[8][j] ;
	}
	cout << "\n" ;
	
	for (i=9;i<=16;i++)
	{
		for(j=0;j<=31;j++)
		{
			cout << a[i][j] ;
		}
		if (i%2==0) cout << c[(i-10)/2] ;
		else cout << a[i][32] ;
		for (j=33;j<=64;j++)
		{
			cout << a[i][j] ;
		}
		cout << "\n" ;
	}
	
	return 0 ;
}
