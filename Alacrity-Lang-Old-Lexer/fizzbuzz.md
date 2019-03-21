# FizzBuzz code

```
main =
	start = num input.
	end = num input.

	[ x <- start .. end |
		res = ""
		x % 3 == 0 ? res += "Fizz" $$
		x % 5 == 0 ? res += "Buzz" $$
		print res.len == 0 ? x : res $$
	]
	return 0 $$
```
