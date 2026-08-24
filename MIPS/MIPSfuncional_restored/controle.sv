module controle(
    input logic [5:0] opcode,

    output logic [1:0] regdst,
    output logic regwrite,
    output logic alusrc,
    output logic [1:0] memtoreg,
    output logic memread,
    output logic memwrite,
    output logic branch,
    output logic jump,
    output logic in_signal,
    output logic out_signal,
    output logic halt,
    output logic [3:0] aluop
);

    // Parametros para os opcodes
    localparam OP_TIPO_R = 6'b000000;
    localparam OP_ADDI = 6'b000001;
    localparam OP_SUBI = 6'b000010;
    localparam OP_ANDI = 6'b000011;
    localparam OP_ORI = 6'b000100;
    localparam OP_LW = 6'b000101;
    localparam OP_SW = 6'b000110;
    localparam OP_BEQ = 6'b000111;
    localparam OP_BNE = 6'b001000;
    localparam OP_BLT = 6'b001001;
    localparam OP_BGT = 6'b001010;
    localparam OP_BLE = 6'b001011;
    localparam OP_BGE = 6'b001100;
    localparam OP_IN = 6'b001101;
    localparam OP_OUT = 6'b001110;
    localparam OP_J = 6'b010000;
    localparam OP_JAL = 6'b010001;
    localparam OP_NOP = 6'b010010;
    localparam OP_HALT = 6'b010011;

    // Parametros para ALUOp
    localparam ALUOP_TIPO_R = 4'b0000;
    localparam ALUOP_SOMA = 4'b0001;
    localparam ALUOP_SUB = 4'b0010;
    localparam ALUOP_AND = 4'b0011;
    localparam ALUOP_OR = 4'b0100;
    localparam ALUOP_SLT = 4'b0101;
    localparam ALUOP_SGT = 4'b0110;
    localparam ALUOP_SLE = 4'b0111;
    localparam ALUOP_SGE = 4'b1000;
    localparam ALUOP_BEQ = 4'b1001;
    localparam ALUOP_BNE = 4'b1010;


    always_comb begin
        
        regdst = 2'b11; // NADA
        regwrite = 1'b0;
        alusrc = 1'b0;
        memtoreg = 2'b00; 
        memread = 1'b0;
        memwrite = 1'b0;
        branch = 1'b0;
        jump = 1'b0;
        in_signal = 1'b0;
        out_signal = 1'b0;
        halt = 1'b0;
        aluop = 4'b0000;

        case (opcode)
            OP_TIPO_R: begin
                regdst = 2'b01;
                regwrite = 1'b1;
                aluop = ALUOP_TIPO_R;
            end
            OP_ADDI: begin
                regdst = 2'b00;
                regwrite = 1'b1;
                alusrc = 1'b1;
                aluop = ALUOP_SOMA;
            end
            OP_SUBI: begin
                regdst = 2'b00;
                regwrite = 1'b1;
                alusrc = 1'b1;
                aluop = ALUOP_SUB;
            end
            OP_ANDI: begin
                regdst = 2'b00;
                regwrite = 1'b1;
                alusrc = 1'b1;
                aluop = ALUOP_AND;
            end
            OP_ORI: begin
                regdst = 2'b00;
                regwrite = 1'b1;
                alusrc = 1'b1;
                aluop = ALUOP_OR;
            end
            OP_LW: begin
                regdst = 2'b00;
                regwrite = 1'b1;
                alusrc = 1'b1;
                memtoreg = 2'b01;
                memread  = 1'b1;
                aluop = ALUOP_SOMA;
            end
            OP_SW: begin
                alusrc = 1'b1;
                memwrite = 1'b1;
                aluop = ALUOP_SOMA;
            end
            OP_BEQ: begin
                branch = 1'b1;
                alusrc = 1'b0;
                aluop = ALUOP_BEQ;
            end
            OP_BNE: begin
                branch = 1'b1;
                alusrc = 1'b0;
                aluop = ALUOP_BNE;
            end
            OP_BLT: begin
                branch = 1'b1;
                alusrc = 1'b0;
                aluop = ALUOP_SLT;
            end
            OP_BGT: begin
                branch = 1'b1;
                alusrc = 1'b0;
                aluop = ALUOP_SGT;
            end
            OP_BLE: begin
                branch = 1'b1;
                alusrc = 1'b0;
                aluop = ALUOP_SLE;
            end
            OP_BGE: begin
                branch = 1'b1;
                alusrc = 1'b0;
                aluop = ALUOP_SGE;
            end
            OP_IN: begin
                regdst = 2'b00;
                regwrite = 1'b1;
                memtoreg = 2'b11;
                in_signal = 1'b1;
            end
            OP_OUT: begin
                out_signal = 1'b1;
            end
            OP_J: begin
                jump = 1'b1;
            end
            OP_JAL: begin
                regdst = 2'b10;
                regwrite = 1'b1;
                memtoreg = 2'b10;
                jump = 1'b1;
            end
            OP_NOP: begin
                // Nenhum sinal precisa ser ativado
            end
            OP_HALT: begin
                halt = 1'b1;
            end
            default: begin
            end
        endcase
    end

endmodule