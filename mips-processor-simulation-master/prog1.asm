# comment
beq	$1, $2, 0x200   ## comment
beq	$1, $2, 0x1e00
add	$3, $4, $8   # another comment
addi	$2, $1, 0x64
sub	$2, $3, $9
slt	$1, $2, $10 #comment
slt	$1, $2, $3
lw	$1, 0X2bc($2)

sw  $17, 500($4)