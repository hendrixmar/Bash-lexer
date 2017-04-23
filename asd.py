from numpy import inf, linalg

x =0

A = array([[10,-1,2,0],[-1,11-1,3],[2,-1,10,-1],[0,3,-1, 8]])

b = array([6,25,-11,15])
vec = array([0,0,0,0])
n = 4
while(1):
	for i in range(n):
		for j in range(n):
			if(j == i):
				continue

			vec[i] += (-a[i][j])/a[i][i]*vec[j]

		vec += b
