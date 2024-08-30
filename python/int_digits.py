
# We count the number of times its divisible by 10
def count_digits(_n: int):
    n = abs(_n)
    # Edge Case
    if _n == 0:  print(f"digits in '{_n}':  1"); return 1;
    counter = 0
    while int(n) > 1:
      counter += 1
      n //= 10
    print(f"digits in '{int(_n)}':  {counter}")
    return counter

for x in [-50, -1, 0, 1, 50, 55.51239]:
    count_digits(x)
    count_digits(x*10)
    count_digits(x*100)
