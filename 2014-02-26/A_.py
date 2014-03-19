import re
def mult(a, b):
	c = []
	for i in a:
		for j in b:
			c.append(i+j)
	return c
def multi(*args):
	s = args[0]
	for i in range(1, len(args)):
		s = mult(s, args[i])
	return s
tables = {}
fp = open('bersql.in', 'r')
lines = map(lambda x: x.strip(), fp.readlines())
for s in lines:
	command = s.split()[0].upper()
	if command == 'CREATE':
		tablename, cols = re.match(r'CREATE TABLE (\w+) ([^;]*)', s, re.I).groups()
		tablename = 'vani' + tablename
		cols = eval(re.sub(r'\(', '[', re.sub(r'\)', ']', re.sub(r'(\w+)', r"'\1'", cols))))
		tables[tablename] = (cols, [])
	elif command == 'INSERT':
		tablename, vals = re.match(r'INSERT INTO (\w+) VALUES ([^;]*)', s, re.I).groups()
		tablename = 'vani' + tablename
		vals = eval(re.sub(r'\(', '[', re.sub(r'\)', ']', vals)))
		tmpdict = {}
		for i in range(0, len(tables[tablename][0])):
			tmpdict[tables[tablename][0][i]] = vals[i]
		tables[tablename][1].append([tmpdict])
	elif command == 'SELECT':
		cols, tmp1, tablenames, tmp2, conds = re.match(r'SELECT ((\w+\.\w+,\s*)*\w+\.\w+) FROM ((\w+,\s*)*\w+) WHERE ([^;]*)', s, re.I).groups()
		tablenames = re.sub(r'(\w+)', r"vani\1", tablenames)
		tablenames = eval('[' + re.sub(r'(\w+)', r"'\1'", tablenames) + ']')
		tmp = []
		for item in tablenames:
			if not item in tmp: tmp.append(item)
		tablenames = ','.join(tmp)
		cols = re.sub(r'(\w+)\.(\w+)', r"vani\1['\2']", cols)
		funccols = eval('lambda ' + tablenames + ': [' + cols + ']')
		conds = eval('lambda ' + tablenames + ': ' + re.sub(r'\s[Oo][Rr]\s', ' or ', re.sub(r'\s[Aa][Nn][Dd]\s', ' and ', re.sub(r'=', '==', re.sub(r'(\w+)\.(\w+)', r"vani\1['\2']", conds)))))
		tablenames = eval('[' + re.sub(r'(\w+)', r"'\1'", tablenames) + ']')
		rows = multi(*(list(map(lambda x: tables[x][1], tablenames))))
		rows = list(filter(lambda x: conds(*x), rows))
		result = list(map(lambda x: ' '.join(funccols(*x)), rows))
		result.sort()
		result = '\n'.join(result + ['']) + '---'
		print(result)
quit(0)
