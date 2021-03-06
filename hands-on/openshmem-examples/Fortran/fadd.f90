!
!
! Copyright (c) 2011 - 2014
!   University of Houston System and Oak Ridge National Laboratory.
! 
! All rights reserved.
! 
! Redistribution and use in source and binary forms, with or without
! modification, are permitted provided that the following conditions
! are met:
! 
! o Redistributions of source code must retain the above copyright notice,
!   this list of conditions and the following disclaimer.
! 
! o Redistributions in binary form must reproduce the above copyright
!   notice, this list of conditions and the following disclaimer in the
!   documentation and/or other materials provided with the distribution.
! 
! o Neither the name of the University of Houston System, Oak Ridge
!   National Laboratory nor the names of its contributors may be used to
!   endorse or promote products derived from this software without specific
!   prior written permission.
! 
! THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
! "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
! LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
! A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
! HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
! SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
! TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
! PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
! LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
! NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
! SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
!


!
! expected output on 2 PEs:
!
! 0: old = -1, dst = 66
! 1: old = 22, dst = 22
!

program fadd

  include 'mpp/shmem.fh'

  integer :: num_pes, my_pe

  integer, save :: dst
  integer me, old

  call start_pes(0)
  me = my_pe()

  old = -1;
  dst = 22;
  call shmem_barrier_all()

  if (me == 1) then
     old = shmem_int4_fadd(dst, 44, 0);
  end if
  call shmem_barrier_all()

  if (me == 0) then
     if (old == (-1) .and. dst == 66) then
        print *, 'OK'
     else
        print *, 'FAIL'
     end if
  end if

end program fadd
