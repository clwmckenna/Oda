#!/bin/python
lim = int(raw_input())
print 1,1,

a = 1
b = 1

for i in xrange(lim):
	a,b = b,a
	b = a+b
	print b,
print