#include <stdio.h>
int main() {
	int n;
	int i, j, temp, set, s;
	int a[1002];
	int b[1002];
	int lengr, lengl;
	scanf("%d", &n);
	a[0] = 0;
	a[n + 1] = 0;
	for (i = 1; i <= n; ++i) {
		scanf("%d", a + i);
		b[i] = i;
	}
	//paixu
	for (i = 1; i <= n; ++i) {
		for (j = i; j <= n; ++j) {
			if (a[b[i]]>a[b[j]]) {
				temp = b[i];
				b[i] = b[j];
				b[j] = temp;
			}
		}
	}
	s = n*a[b[1]];
	for (i = 2; i <= n; ++i) {
		lengr = n - b[i];
		lengl = b[i]-1;
		for (j = 1; j<i; ++j) {
			temp = b[j] - b[i];
			if (a[b[i]] != a[b[j]]) {
				if (temp>0) {
					--temp;
					lengr = lengr<temp ? lengr : temp;
				}
				else {
					temp = 0 - temp - 1;
					lengl = lengl<temp ? lengl : temp;
				}
			}
		}
		temp = a[b[i]] * (lengr + lengl + 1);
		if (temp>s) {
			s = temp;
		}
	}
	printf("%d", s);
	return 0;
}
