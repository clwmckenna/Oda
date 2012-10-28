#!/bin/python
lim = int(raw_input("Enter a number: "))
print 1,1,

a = 1
b = 1

for i in xrange(lim-2):
	a,b = b,a
	b = a+b
	print b,
print