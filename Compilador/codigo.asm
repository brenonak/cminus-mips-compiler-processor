    ADDI $sp, $zero, 255
    J main

maximo:
    SUBI $sp, $sp, 1
    SW $ra, 0($sp)
    SUBI $sp, $sp, 11
    ADDI $t0, $zero, 0
    SW $t0, 0($sp)
    LW $s0, 0($sp)
    LW $t0, 13($sp)
    ADD $s0, $s0, $t0
    LW $t0, 0($s0)
    SW $t0, 1($sp)
    LW $t0, 1($sp)
    SW $t0, 9($sp)
    ADDI $t0, $zero, 1
    SW $t0, 2($sp)
    LW $t0, 2($sp)
    SW $t0, 10($sp)
L0:
    LW $t0, 10($sp)
    LW $t1, 12($sp)
    BGE $t0, $t1, L1
    LW $s0, 10($sp)
    LW $t0, 13($sp)
    ADD $s0, $s0, $t0
    LW $t0, 0($s0)
    SW $t0, 4($sp)
    LW $t0, 4($sp)
    LW $t1, 9($sp)
    BLE $t0, $t1, L2
    LW $s0, 10($sp)
    LW $t0, 13($sp)
    ADD $s0, $s0, $t0
    LW $t0, 0($s0)
    SW $t0, 6($sp)
    LW $t0, 6($sp)
    SW $t0, 9($sp)
L2:
    ADDI $t0, $zero, 1
    SW $t0, 7($sp)
    LW $t0, 10($sp)
    LW $t1, 7($sp)
    ADD $t2, $t0, $t1
    SW $t2, 8($sp)
    LW $t0, 8($sp)
    SW $t0, 10($sp)
    J L0
L1:
    LW $v0, 9($sp)
    ADDI $sp, $sp, 11
    LW $ra, 0($sp)
    ADDI $sp, $sp, 1
    JR $ra
    ADDI $sp, $sp, 11
    LW $ra, 0($sp)
    ADDI $sp, $sp, 1
    JR $ra

minimo:
    SUBI $sp, $sp, 1
    SW $ra, 0($sp)
    SUBI $sp, $sp, 11
    ADDI $t0, $zero, 0
    SW $t0, 0($sp)
    LW $s0, 0($sp)
    LW $t0, 13($sp)
    ADD $s0, $s0, $t0
    LW $t0, 0($s0)
    SW $t0, 1($sp)
    LW $t0, 1($sp)
    SW $t0, 9($sp)
    ADDI $t0, $zero, 1
    SW $t0, 2($sp)
    LW $t0, 2($sp)
    SW $t0, 10($sp)
L4:
    LW $t0, 10($sp)
    LW $t1, 12($sp)
    BGE $t0, $t1, L5
    LW $s0, 10($sp)
    LW $t0, 13($sp)
    ADD $s0, $s0, $t0
    LW $t0, 0($s0)
    SW $t0, 4($sp)
    LW $t0, 4($sp)
    LW $t1, 9($sp)
    BGE $t0, $t1, L6
    LW $s0, 10($sp)
    LW $t0, 13($sp)
    ADD $s0, $s0, $t0
    LW $t0, 0($s0)
    SW $t0, 6($sp)
    LW $t0, 6($sp)
    SW $t0, 9($sp)
L6:
    ADDI $t0, $zero, 1
    SW $t0, 7($sp)
    LW $t0, 10($sp)
    LW $t1, 7($sp)
    ADD $t2, $t0, $t1
    SW $t2, 8($sp)
    LW $t0, 8($sp)
    SW $t0, 10($sp)
    J L4
L5:
    LW $v0, 9($sp)
    ADDI $sp, $sp, 11
    LW $ra, 0($sp)
    ADDI $sp, $sp, 1
    JR $ra
    ADDI $sp, $sp, 11
    LW $ra, 0($sp)
    ADDI $sp, $sp, 1
    JR $ra

main:
    SUBI $sp, $sp, 1
    SW $ra, 0($sp)
    SUBI $sp, $sp, 13
    ADDI $t0, $zero, 0
    SW $t0, 0($sp)
    LW $t0, 0($sp)
    SW $t0, 12($sp)
L8:
    ADDI $t0, $zero, 5
    SW $t0, 1($sp)
    LW $t0, 12($sp)
    LW $t1, 1($sp)
    BGE $t0, $t1, L9
    IN $v0
    SW $v0, 3($sp)
    LW $t0, 3($sp)
    LW $s0, 12($sp)
    ADDI $s0, $s0, 0
    SW $t0, 0($s0)
    ADDI $t0, $zero, 1
    SW $t0, 4($sp)
    LW $t0, 12($sp)
    LW $t1, 4($sp)
    ADD $t2, $t0, $t1
    SW $t2, 5($sp)
    LW $t0, 5($sp)
    SW $t0, 12($sp)
    J L8
L9:
    ADDI $t0, $zero, 5
    SW $t0, 6($sp)
    SUBI $sp, $sp, 2
    ADDI $t0, $zero, 0
    SW $t0, 1($sp)
    LW $t0, 8($sp)
    SW $t0, 0($sp)
    JAL maximo
    ADDI $sp, $sp, 2
    SW $v0, 7($sp)
    LW $t0, 7($sp)
    OUT $t0
    ADDI $t0, $zero, 5
    SW $t0, 9($sp)
    SUBI $sp, $sp, 2
    ADDI $t0, $zero, 0
    SW $t0, 1($sp)
    LW $t0, 11($sp)
    SW $t0, 0($sp)
    JAL minimo
    ADDI $sp, $sp, 2
    SW $v0, 10($sp)
    LW $t0, 10($sp)
    OUT $t0
    HALT
