#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>

#define �� 0.0001
#define h 0.0000001

using namespace std;

double fx(int num, double x);
double dfx(int num,double x);

int main(){
	int i = 0, j = 0, k = 0;
	int num=0;
	double x0 = 0.0;
	double x = 0.0,next_x=0.0;


	cout << "�j���[�g���@" << endl;
	cout << "����I��ł�������" << endl;
	cout << "1. 3atan(x-1)+x/4" << endl;
	cout << "2. x^2-5" << endl;
	while (1){
		cin >> num;
		if (num == 1 || num == 2) break;
		cout << "1,2�œ��͂��Ă�������" << endl;
	}
	
	cout << "x0����͂��Ă�������" << endl;
	cout << "x0����� x0=";
	cin >> x0;
	x = x0;
	while (1) {
		next_x = x - (fx(num,x) / dfx(num,x));
		if (�� > abs(next_x - x)) break;
		i++;
		if (i == 1000) {
			cout << "�������s" << endl;
		}
		x = next_x;
	}

	cout << "����" << next_x << endl;
	cout << "������" << i << endl;


	getchar();
	getchar();
}


double  fx(int num ,double x){
	double ans;
	if (num == 1){
		ans = 3 * atan(x - 1) + x / 4;
	}
	else {
		ans = x*x - 5;
	}
	return ans;
}

double dfx(int num,double x){
	double ans;
	ans = (fx(num, x + h) - fx(num, x)) / h;
	return ans;
}
