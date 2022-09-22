.data
.globl main

main:
li $t1,0
move $t0, $t1
li $t2,2
add $t2,$t0,$t2
move $t1, $t2
$LOOP1:
$CONT1:
li $t2,0
bne $t1, $t2, $EXIT1
nop
li $t3,0
bne $t0, $t3, $If_FALSE4
nop
li $t4,1
add $t4,$t0,$t4
move $t0, $t4
j $CONT1
nop
J $If_EXIT5
nop
$If_FALSE4:
$If_EXIT5:
li $t3,1
sub $t3,$t1,$t3
move $t1, $t3
j $LOOP1
nop
$EXIT1:
$EXIT_FUNC1:
jr $ra
nop

.data
