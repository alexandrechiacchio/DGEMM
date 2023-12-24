subroutine print_matrix(n,A)
  implicit none
  integer, intent(in) :: n
  real(8), intent(in) :: A(n, n)

  integer :: i

  do i = 1, n
    print *, A(i, 1:n)
  end do

end subroutine print_matrix


program DGEMM
  use, intrinsic :: iso_fortran_env, only: sp=>real32, dp=>real64
  ! implicit none

  integer :: sz
  integer :: start, stop
  real(dp), allocatable, dimension(:,:):: A, B, C
  character(len=20) :: arg_value

  ! Retrieve the first command-line argument (as a character)
  call get_command_argument(1, value=arg_value)

  ! Convert the character value to an integer
  read(arg_value, *, iostat=ierr) sz
  if (ierr /= 0) then
     write(*,*) "Error: Invalid integer value provided."
     stop
  end if

  allocate(A(sz,sz))
  allocate(B(sz,sz))
  allocate(C(sz,sz))

  do i = 1, size(a, 2)
    do j = 1, size(a, 1)
      A(j, i) = (j-1)*sz + (i)
    end do
  end do
  do i = 1, size(a, 2)
    do j = 1, size(a, 1)
      B(j, i) = sz*sz - ((j-1)*sz + i) + 1
    end do
  end do


  call SYSTEM_CLOCK(start)
  C = matmul(A, B)
  ! call sleep(1)
  call SYSTEM_CLOCK(stop)

  print *, 'Total time = ', (stop - start), 'ms'


  ! print *, 'A'
  ! call print_matrix(sz, A)
  ! print *, 'B'
  ! call print_matrix(sz, B)
  ! print *, 'C'
  ! call print_matrix(sz, C)



end program DGEMM