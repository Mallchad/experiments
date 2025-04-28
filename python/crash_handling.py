
# This is an experiment to test what kinds of errors can be caught as exceptions in Python
# Catchable errors
# y | type error

foo = None

def main():
    try:
        foo + 1
    except Exception as err:
        print( "Exception occured:", err )

main()
