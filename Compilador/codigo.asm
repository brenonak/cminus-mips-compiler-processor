    ADDI $sp, $zero, 255
    J main

minloc:
    SUBI $sp, $sp, 1
    SW $ra, 0($sp)
    SUBI $sp, $sp, 12
    LW $t0, 14($sp)
    SW $t0, 9($sp)
    LW $s0, 14($sp)
    LW $t0, 15($sp)
    ADD $s0, $s0, $t0
    LW $t0, 0($s0)
    SW $t0, 0($sp)
    LW $t0, 0($sp)
    SW $t0, 10($sp)
    ADDI $t0, $zero, 1
    SW $t0, 1($sp)
    LW $t0, 14($sp)
    LW $t1, 1($sp)
    ADD $t2, $t0, $t1
    SW $t2, 2($sp)
    LW $t0, 2($sp)
    SW $t0, 11($sp)
L0:
    LW $t0, 11($sp)
    LW $t1, 13($sp)
    BGE $t0, $t1, L1
    LW $s0, 11($sp)
    LW $t0, 15($sp)
    ADD $s0, $s0, $t0
    LW $t0, 0($s0)
    SW $t0, 4($sp)
    LW $t0, 4($sp)
    LW $t1, 10($sp)
    BGE $t0, $t1, L2
    LW $s0, 11($sp)
    LW $t0, 15($sp)
    ADD $s0, $s0, $t0
    LW $t0, 0($s0)
    SW $t0, 6($sp)
    LW $t0, 6($sp)
    SW $t0, 10($sp)
    LW $t0, 11($sp)
    SW $t0, 9($sp)
L2:
    ADDI $t0, $zero, 1
    SW $t0, 7($sp)
    LW $t0, 11($sp)
    LW $t1, 7($sp)
    ADD $t2, $t0, $t1
    SW $t2, 8($sp)
    LW $t0, 8($sp)
    SW $t0, 11($sp)
    J L0
L1:
    LW $v0, 9($sp)
    ADDI $sp, $sp, 12
    LW $ra, 0($sp)
    ADDI $sp, $sp, 1
    JR $ra
    ADDI $sp, $sp, 12
    LW $ra, 0($sp)
    ADDI $sp, $sp, 1
    JR $ra

sort:
    SUBI $sp, $sp, 1
    SW $ra, 0($sp)
    SUBI $sp, $sp, 11
    LW $t0, 13($sp)
    SW $t0, 8($sp)
L4:
    ADDI $t0, $zero, 1
    SW $t0, 0($sp)
    LW $t0, 12($sp)
    LW $t1, 0($sp)
    SUB $t2, $t0, $t1
    SW $t2, 1($sp)
    LW $t0, 8($sp)
    LW $t1, 1($sp)
    BGE $t0, $t1, L5
    SUBI $sp, $sp, 3
    LW $t0, 17($sp)
    SW $t0, 2($sp)
    LW $t0, 11($sp)
    SW $t0, 1($sp)
    LW $t0, 15($sp)
    SW $t0, 0($sp)
    JAL minloc
    ADDI $sp, $sp, 3
    SW $v0, 3($sp)
    LW $t0, 3($sp)
    SW $t0, 9($sp)
    LW $s0, 9($sp)
    LW $t0, 14($sp)
    ADD $s0, $s0, $t0
    LW $t0, 0($s0)
    SW $t0, 4($sp)
    LW $t0, 4($sp)
    SW $t0, 10($sp)
    LW $s0, 8($sp)
    LW $t0, 14($sp)
    ADD $s0, $s0, $t0
    LW $t0, 0($s0)
    SW $t0, 5($sp)
    LW $t0, 5($sp)
    LW $s0, 9($sp)
    LW $t1, 14($sp)
    ADD $s0, $s0, $t1
    SW $t0, 0($s0)
    LW $t0, 10($sp)
    LW $s0, 8($sp)
    LW $t1, 14($sp)
    ADD $s0, $s0, $t1
    SW $t0, 0($s0)
    ADDI $t0, $zero, 1
    SW $t0, 6($sp)
    LW $t0, 8($sp)
    LW $t1, 6($sp)
    ADD $t2, $t0, $t1
    SW $t2, 7($sp)
    LW $t0, 7($sp)
    SW $t0, 8($sp)
    J L4
L5:
    ADDI $sp, $sp, 11
    LW $ra, 0($sp)
    ADDI $sp, $sp, 1
    JR $ra

main:
    SUBI $sp, $sp, 1
    SW $ra, 0($sp)
    SUBI $sp, $sp, 17
    ADDI $t0, $zero, 0
    SW $t0, 0($sp)
    LW $t0, 0($sp)
    SW $t0, 16($sp)
L6:
    ADDI $t0, $zero, 10
    SW $t0, 1($sp)
    LW $t0, 16($sp)
    LW $t1, 1($sp)
    BGE $t0, $t1, L7
    IN $v0
    SW $v0, 3($sp)
    LW $t0, 3($sp)
    LW $s0, 16($sp)
    ADDI $s0, $s0, 0
    SW $t0, 0($s0)
    ADDI $t0, $zero, 1
    SW $t0, 4($sp)
    LW $t0, 16($sp)
    LW $t1, 4($sp)
    ADD $t2, $t0, $t1
    SW $t2, 5($sp)
    LW $t0, 5($sp)
    SW $t0, 16($sp)
    J L6
L7:
    ADDI $t0, $zero, 0
    SW $t0, 6($sp)
    ADDI $t0, $zero, 10
    SW $t0, 7($sp)
    SUBI $sp, $sp, 3
    ADDI $t0, $zero, 0
    SW $t0, 2($sp)
    LW $t0, 9($sp)
    SW $t0, 1($sp)
    LW $t0, 10($sp)
    SW $t0, 0($sp)
    JAL sort
    ADDI $sp, $sp, 3
    SW $v0, 8($sp)
    ADDI $t0, $zero, 0
    SW $t0, 9($sp)
    LW $t0, 9($sp)
    SW $t0, 16($sp)
L8:
    ADDI $t0, $zero, 10
    SW $t0, 10($sp)
    LW $t0, 16($sp)
    LW $t1, 10($sp)
    BGE $t0, $t1, L9
    LW $s0, 16($sp)
    ADDI $s0, $s0, 0
    LW $t0, 0($s0)
    SW $t0, 12($sp)
    LW $t0, 12($sp)
    OUT $t0
    ADDI $t0, $zero, 1
    SW $t0, 14($sp)
    LW $t0, 16($sp)
    LW $t1, 14($sp)
    ADD $t2, $t0, $t1
    SW $t2, 15($sp)
    LW $t0, 15($sp)
    SW $t0, 16($sp)
    J L8
L9:
    HALT
