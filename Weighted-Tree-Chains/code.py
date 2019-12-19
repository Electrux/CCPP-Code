#!/usr/bin/env python3

class Branch:
	def __init__(self, par):
		self.key = None
		self.par = par
		self.count = 0
		# maps letter to Branch class
		self.map = dict()

	def insert(self, val):
		if self.key == None:
			self.key = val[0]
		self.count += 1

		if len(val) == 1: return

		next = val[1:]
		if next[0] not in self.map:
			self.map[next[0]] = Branch(self.key)
		self.map[next[0]].insert(next)

	def get_longest_chains(self, val, prefix, lst = []):
		if self.count >= val:
			prefix += str(self.key)
		else:
			if len(prefix) > 0 and prefix not in lst:
				lst.append(prefix)
			return
		for m in self.map:
			self.map[m].get_longest_chains(val, prefix, lst)
		else:
			if len(prefix) > 0 and prefix not in lst:
				lst.append(prefix)

	def disp(self):
		print(self)
		for k in self.map:
			self.map[k].disp()

	def __str__(self):
		if self.par == None:
			return str(self.key) + '(' + str(self.count) + ')'
		return str(self.par) + ' -> ' + str(self.key) + '(' + str(self.count) + ')'

class Tree:
	def __init__(self):
		self.map = dict()

	def insert(self, val):
		if val[0] not in self.map:
			self.map[val[0]] = Branch(None)
		self.map[val[0]].insert(val)

	def get_longest_chains(self, val):
		lst = []
		for m in self.map:
			self.map[m].get_longest_chains(val, '', lst)
		return lst

	def disp(self):
		for m in self.map:
			self.map[m].disp()

t = Tree()

#t.insert([1, 2])
#t.insert([1, 3, 2])
#t.insert([1, 3, 1])
#t.insert([1, 3, 4])

t.insert('BP')
t.insert('BP')
t.insert('BPM')
t.insert('BE')
t.insert('DE')
t.insert('DE')
t.insert('DE')
t.insert('DE')

lst = []

weight = int(input('Enter required weight: '))

t.disp()

lst = t.get_longest_chains(weight)
lst.sort(key = lambda x: len(x), reverse = True)
print('Longest chains of weight', weight, 'are:', lst)
