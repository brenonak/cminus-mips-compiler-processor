module ULAcontrol(
    input logic [3:0] aluop,        // Vem da unidade de controle
    input logic [5:0] funct,        // Vem da instrucao

    output logic [3:0] controleULA_out,  // Vai para a ULA
    output logic jumpreg
);

    // Parametros para os codigos de operacao da ULA
    localparam ULA_ADD = 4'b0000;
    localparam ULA_SUB = 4'b0001;
    localparam ULA_MUL = 4'b0010;
    localparam ULA_DIV = 4'b0011;
    localparam ULA_AND = 4'b0100;
    localparam ULA_OR  = 4'b0101;
    localparam ULA_NOR = 4'b0110;
    localparam ULA_SLL = 4'b0111;
    localparam ULA_SLR = 4'b1000;
    localparam ULA_BEQ = 4'b1001;
    localparam ULA_BNE = 4'b1010; 
    localparam ULA_BLT = 4'b1011; 
    localparam ULA_BGT = 4'b1100;
    localparam ULA_BLE = 4'b1101; 
    localparam ULA_BGE = 4'b1110;

    // Parametros para os codigos ALUOp
    localparam ALUOP_TIPO_R = 4'b0000;
    localparam ALUOP_SOMA   = 4'b0001;
    localparam ALUOP_SUB    = 4'b0010;
    localparam ALUOP_AND    = 4'b0011;
    localparam ALUOP_OR     = 4'b0100;
    localparam ALUOP_SLT    = 4'b0101;
    localparam ALUOP_SGT    = 4'b0110;
    localparam ALUOP_SLE    = 4'b0111;
    localparam ALUOP_SGE    = 4'b1000;
    localparam ALUOP_BEQ    = 4'b1001;
    localparam ALUOP_BNE    = 4'b1010;

    always_comb begin

        // Valores padrao
        jumpreg = 1'b0;
        controleULA_out = 4'b0000;

        case (aluop)
            ALUOP_TIPO_R:   // tipoR, decodificar FUNCT
                case (funct)
                    6'b000000: controleULA_out = ULA_ADD;
                    6'b000001: controleULA_out = ULA_SUB; 
                    6'b000010: controleULA_out = ULA_MUL; 
                    6'b000011: controleULA_out = ULA_DIV; 
                    6'b000100: controleULA_out = ULA_AND; 
                    6'b000101: controleULA_out = ULA_OR; 
                    6'b000110: controleULA_out = ULA_NOR;

                    6'b000111: begin             // JR
                        jumpreg = 1'b1;
                        controleULA_out = 4'b0000;  // A ULA não é usada para calcular resultado
                    end

                    6'b001000: controleULA_out = ULA_SLL; 
                    6'b001001: controleULA_out = ULA_SLR;
                    default: controleULA_out = 4'b0000; // Operação R-type não definida
                endcase
  
            // Sintaxe de 'case item' corrigida para os casos a seguir
            ALUOP_SOMA: controleULA_out = ULA_ADD; // Para ADDI, LW, SW
            ALUOP_SUB:  controleULA_out = ULA_SUB; // Para SUBI, BEQ, BNE
            ALUOP_AND:  controleULA_out = ULA_AND; // Para ANDI
            ALUOP_OR:   controleULA_out = ULA_OR;  // Para ORI
            ALUOP_SLT:  controleULA_out = ULA_BLT; // Para BLT
            ALUOP_SGT:  controleULA_out = ULA_BGT; // Para BGT
            ALUOP_SLE:  controleULA_out = ULA_BLE; // Para BLE
            ALUOP_SGE:  controleULA_out = ULA_BGE; // Para BGE
            ALUOP_BEQ: controleULA_out = ULA_BEQ;  // Para BEQ
            ALUOP_BNE: controleULA_out = ULA_BNE;  // Para BNE

            default:
                controleULA_out = 4'b0000;
        endcase
    end

endmodule