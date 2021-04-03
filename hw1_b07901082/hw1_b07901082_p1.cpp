#include <iostream>

using namespace std;

int main()
{
	int i , n , d ;
	cout << "Total number n = ";
	cin >> n ;
	cout <<"\n"<< "code d = ";
	cin >> d ;
	cout << "\n";
	for(i=1;i<=n-1;i++)
	{
		if(i%d==0)
		{
			cout << "*" << " , " ;
		}
		else cout << i << " , ";	
	}
	
	if (n%d==0) cout << "*";
	else cout << n ;
	return 0;
}	
