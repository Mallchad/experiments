
import time

foo = []

# Start timing
start = time.time_ns()
# 100 million
for i in range(0, 100000000):
    foo.append( 1)

# Stop Timing
end = time.time_ns() - start

seconds = end / 1e9
print( f"Time Taken For Loop: {seconds} s" )

bar = []
# Start Timing
start = time.time_ns()

bar = [1] * 100000000

end = time.time_ns() - start
seconds = end / 1e9
print( f"Time Taken List multiply: {seconds}s" )


# Start Timing
start = time.time_ns()

map( lambda x: x + 69, foo )

end = time.time_ns() - start
seconds = end / 1e9
print( f"Time Taken List map function: {seconds}s" )
print( f"Mapped value example element {foo[50123123]}" )
