from random import randint as rn

f = open("input","w")

T = 100
zero_based = False
Q = 10000
min_value = 10**4
max_value = 10**7
f.write('{:}\n'.format(T))
for x in xrange(T):
	N = rn(1,500)
	f.write('{:}\n'.format(N))
	f.write('{:}\n'.format(' '.join([str(rn(min_value,max_value)) for y in xrange(N)])))
	f.write('{:}\n'.format(Q))
	for y in xrange(Q):
		a = rn(0 if zero_based else 1, N-1 if zero_based else N)
		b = rn(0 if zero_based else 1, N-1 if zero_based else N)
		if a > b: a,b=b,a
		if rn(0,1)==0:
			v = rn(1,1000000)
			f.write('{:} {:} {:} {:}\n'.format(0,a,b,v))
		else:
			f.write('{:} {:} {:}\n'.format(1,a,b))

f.close()


# f = open("input","r")
# o = open("waited","w")

# T = int(f.readline())
# #print T
# for t in xrange(T):
# 	N = int(f.readline())
# 	#print N
# 	d = f.readline()
# 	#print d[:-1]
# 	arr = [0]+[int(i) for i in d.split(' ')]
# 	Q = int(f.readline())
# 	#print Q
# 	for q in xrange(Q):

# 		l = [int(i) for i in f.readline().split(' ')]
# 		#print ' '.join([str(i) for i in l])
# 		if (len(l) == 3):
# 			o.write('{:}\n'.format(sum(arr[int(l[1]) : int(l[2]+1)])))
# 		else:
# 			for i in xrange(l[1],l[2]+1):
# 				arr[i]=l[3]
# o.close()
# f.close()
