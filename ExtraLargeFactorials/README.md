# Find factorials of large numbers (much larger than what 64 bit numbers can provide).

It uses the procedure of multiplying the entire multiplier with each digit of multiplicant, putting its first digit to a new array and adding the rest to the next digit of multiplicant multiplied by the multiplier. Finally, it adds the remaining part of the rest to the array itself.
