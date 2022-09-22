.data
.globl ma

ma:
li $t1,3
move $t0, $t1
li $t1,3
add $t0, $t0, $t1
$EXIT_FUNC1:
jr $ra
nop

h:
jal ma
nop
$EXIT_FUNC2:
jr $ra
nop

.data
