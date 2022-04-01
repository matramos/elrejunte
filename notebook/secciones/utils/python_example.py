import sys, math
input = sys.stdin.readline
 
############ ---- Input Functions ---- ############
def inp():
    return(int(input()))
def inlt():
    return(list(map(int,input().split())))
def insr():
    s = input()
    return(list(s[:len(s) - 1]))
def invr():
    return(map(float,input().split()))
    

n, k = inlt()
intpart = 0
while intpart*intpart <= n:
	intpart += 1
intpart -= 1

if(k == 0):
	print(intpart)
else:
	L = 0
	R = 10**k-1
	aux = 10**k
	
	while(L < R):
		M = (L+R+1)//2
		if intpart**2 * aux**2 + M**2 + 2*intpart*M*aux <= n * aux**2:
			L = M
		else:
			R = M-1
	
	decpart = str(L)
	while(len(decpart) < k):
		decpart = '0'+decpart
	print(f"{intpart}.{decpart}")
