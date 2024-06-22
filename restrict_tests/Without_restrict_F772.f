
      program Without_restrict_F77

        INTEGER :: i,j
        INTEGER, PARAMETER :: arr_size=100000000
        INTEGER, DIMENSION(:), ALLOCATABLE :: x
        INTEGER, DIMENSION(:), ALLOCATABLE :: y
        INTEGER, DIMENSION(:), ALLOCATABLE :: z
        real :: start, finish

        ALLOCATE(x(arr_size))
        ALLOCATE(y(arr_size))
        ALLOCATE(z(arr_size))

        DO i=1,arr_size
          x(i) = 3*i
          y(i) = MOD(i,100)*MOD(i,100)
          z(i) = 0
        END DO

        call cpu_time(start)
        DO j=1,100
          DO i=1,arr_size
            z(i) = x(i) + y(i)+j
          END DO
        END DO
        call cpu_time(finish)
        print *, "Time for separate[mus]: ", (finish-start)*1000000

      end program Without_restrict_F77
