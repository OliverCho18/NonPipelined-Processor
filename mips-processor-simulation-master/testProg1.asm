add	$3, $2, $1 # $3 = -5872+4324 = -1548 = 0xF9F4
addi $0, $1, 3241 # $0 =  -5872 + 3241 = -2631 =  0xF5B9

addi $4, $2, 0xfffffEBC # $4 = 4324 - 324 = 4000 = 0x0FA0
sub	$6, $3, $0 # $  $6 = 0xF9F4 - 0xF5B9 =  -1548 - -2631 = 1083 = 0x043B
# comment
slt	$7, $3, $4 # $7 = 0x1
slt	$8, $3, $0 # $8 = 0x0
add	$3, $3, $3 # $3 = -1548 + -1548 = -3096 = 0xffffF3E8 