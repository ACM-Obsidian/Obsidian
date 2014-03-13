import sys
fp = open('automaton.in', 'r')
n = int(fp.read().strip())
fp.close()
fp = open('automaton.out', 'w')
k = 0
while 2**k+k <= n: k += 1
A = 2**(n-k+1)
for i in range(0, k): A += 2**(2**i)-1
left = 2**(n-k)
right = 2**(2**(k-1))-1
if left < right:
	B = 2**(k+2**(k-1)-2)
else:
	B = 2**(k+2**(k-1)-2)
	left -= right
	c = 2**k
	t = 1
	u = 1
	for i in range(1, c+1):
		t = t * (c-i+1) / i
		if i <= c/2+1: u = u * (c/2-i+1) / i
		cnt = min(left, t-u)
		left -= cnt
		B += cnt * i
fp.write(str(A)+' '+str(B)+'\n')
fp.close()
