# include <iostream> 
using namespace std;

int main()
{
	cout << "This program will convert decimal numbers to base-n system.\n" 
	<< "Please give me a pair of numbers as follow: DecNumber Base\n" ;
	int a , n , r , i , c , e ;
	int *d =  new int [i] ;

    while  (1)
	{
	cout << "input:  ";
	cin >> a >> n ;
	e = a ;
	cout << "\n" ;
	i=0;
	
	while(a>n)
	{
		r = a % n ;
		a = (a - r) / n ;
		*(d+i) = r ;
		i=i+1;
	}
	if(a==n)  *(d+i) = 1 ;
	
	c = i ;
	cout << "\n" ;
	
	cout << "( " << dec << e << " )_10 = (" ;
	
	for(i=c;i>=0;i--)
	{
		cout << hex << *(d+i) ;
	}
	
	cout << ")_"<< n <<" " << endl ;
    }
	return 0;
} 
