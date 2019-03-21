# Code Examples

1. Hello world

```
main = print "Hello world" $ return 0 $$
```

2. Variables

```
main = var = 2 + 4 * 6 / 8 $ print var $ return 0 $$
```

3. Arrays/Lists

```
main = var = [ 1 .. 10 ] $ print var.2 $ return 0 $$
main = var = [ 1, 2, 3, 4 ] $ print var.1 $ return 0 $$
```

4. Maps/Dictionaries

```
main = var = { "one": "1" } $ print var->one $ return 0 $$
```

5. Functions

```
hello to = print "Hello " + to

main = hello "World" $ return 0 $$
```

6. Conditionals

```
main args = args.len == 1 | print "One" | print "Not one" $$ return 0 $$
```

7. Multi-line Conditionals

```
main args =
	args.len == 1 ?
		print "One"
	: args.len == 2 ?
		print "Two"
	:
		print "Not one or two" $$
	return 0 $$
```

8. Loops

```
main args = args.len == 2 | [ 1 .. 10 | print args.1 ] $$ return 0 $$
```

9. Loops - Multiple statements

```
main args = [ 1 .. 10 | print "Hello:" $ print args.1 ] $ return 0 $$

# infinite loop
main = [ | print "Hello!" ] $ return 0 $$
```

10. Loops - Multiple lines

```
main args =
	[ x <- 0 .. args.len |
		print "Arg " + x + ":"
		print args.@x
	]
	return 0 $$
```

11. Variable assignment using conditionals

```
main =
	var = args.len > 1 | "Greater than one" | "Less than or equal to one" $$
	print var
	return 0 $$
```

12. Variables using conditionals - Multiple lines

```
main =
	var = args.len > 1 |
		"Greater than one" |
		"Less the One" $$
	print var
	return 0 $$
```

13. Structures & Objects

*Without parenthesis the print function call would be ambiguous*
```
struct C = a = 5 $$ mult_five n = return a * n $$
main = c = C $ print ( c.mult_five 10 ) $$

OR

struct C =
	a = 5 $$
mult_five c n =
	return c.a * n $$
main =
	c = C
	print ( c.mult_five 10 ) $$
```
