j 0x400008
add	$3, $4, $8
addi $2, $1, 100
beq	$1, $2, 0x2
beq	$5, $5, 0x40001c 
slt	$1, $2, $10 
slt	$1, $3, $2
sub	$2, $3, $9
lw	$1, 0($11)
sw  $17, 0($11)