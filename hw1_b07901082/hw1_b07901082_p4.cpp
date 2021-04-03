#include <iostream>
using namespace std ;

int t[10][10];
int num[10001];
int order[10001];
int found[10001];

int main()
{
	cout << "Please enter the input information (n+3 lines):" << endl;
	int n, m, counttime = 0;
	cin >> n >> m;
	for(int i = 0; i < n+1; i++)
		for(int j = 0; j < n+1; j++)
			cin >> t[i][j];
	for(int i = 1; i <= n; i++)
		cin >> num[i];
	int cnt = 1, flag = 1; 
	int nowx = 0, coda = m;
	while(flag){
		if(cnt == n+1) flag = 0;
		int time = 66666666, index = -1;
		for(int i = 1; i <= n; i++)
		{
			if(found[i]) continue;
			if(coda >= num[i]){
				if(time > t[nowx][i]){
					index = i;
					time = t[nowx][i];
				}
			}
		}
		if(index == -1){
			counttime += t[nowx][0];
			nowx = 0;
			coda = m;
		}
		else {
			counttime += t[nowx][index];
			order[cnt] = index;
			found[index] = 1;
			nowx = index;
			cnt++;
			coda -= num[index];
		}
	}
	cout << "Delivery order:" ;
	for(int i = 1; i <= n; i++)
		cout << " " << order[i];
	cout << "\n" << "Total time: " << counttime << endl;
}
