// Somya Mehta
// 190001058
#include <bits/stdc++.h>
using namespace std;

int num=5;
int matrix[100][6];

void input()
{
	for (int i = 0; i < num; i++) {
		cout << "Enter Pid: ";
		cin >> matrix[i][0];
		cout << "Enter Arrival Time: ";
		cin >> matrix[i][1];
		cout << "Enter Burst Time: ";
		cin >> matrix[i][2];
	}
}

void Scheduler()
{
	int temp, val;
	matrix[0][3] = matrix[0][1] + matrix[0][2];
	matrix[0][5] = matrix[0][3] - matrix[0][1];
	matrix[0][4] = matrix[0][5] - matrix[0][2];

	for (int i = 1; i < num; i++) {
		temp = matrix[i - 1][3];
		int low = matrix[i][2];
		for (int j = i; j < num; j++) {
			if (temp >= matrix[j][1] && low >= matrix[j][2]) {
				low = matrix[j][2];
				val = j;
			}
		}
		matrix[val][3] = temp + matrix[val][2];
		matrix[val][5] = matrix[val][3] - matrix[val][1];
		matrix[val][4] = matrix[val][5] - matrix[val][2];
		for (int k = 0; k < 6; k++) {
			swap(matrix[val][k], matrix[i][k]);
		}
	}
}

int main()
{
	cout<<"Shortest Job first Algo\n";
	input();
	for (int i = 0; i < num; i++) {
		for (int j = 0; j < num - i - 1; j++) {
			if (matrix[j][1] >= matrix[j + 1][1]) {
				for (int k = 0; k < num; k++) {
					swap(matrix[j][k], matrix[j + 1][k]);
				}
			}
		}
	}
	Scheduler();
	printf("\nPID\tArrival\tBurst\tWaiting\tTurnaround\n");
    for (int i = 0; i < num; i++) {
        printf("%d\t%d\t%d\t%d\t%d\n", matrix[i][0], matrix[i][1], matrix[i][2], matrix[i][4], matrix[i][5]);
    }
  
  float avg_wt = 0, avg_turn = 0;
	for (int i = 0; i < num; i++) {
    avg_wt += matrix[i][4];
    avg_turn += matrix[i][5];
	}

    printf("\nAverage waiting time: %f\nAverage turn around time: %f\n",avg_wt / 5.0,avg_turn / 5.0);
}

