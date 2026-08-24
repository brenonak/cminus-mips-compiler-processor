module ULA (
	input logic [31:0] A,	// Operando
	input logic [31:0] B,	// Operando
	input logic [3:0] controleULA,	// Codigo da operacao
	input logic [4:0] shamt,	// Shift amount (para instruçoes de deslocamento)
	
	output logic [31:0] result,	// Resultado da operacao
	output logic zero		// Para comparacao
);

always_comb begin

    result = 32'b0;
    zero = 1'b0;

    case (controleULA)
        4'b0000: result = A + B;                     // ADD
        4'b0001: result = A - B;                     // SUB
        4'b0010: result = A * B;                     // MUL
        4'b0011: result = (B != 0) ? (A / B) : 32'd0;  // DIV (sem divisao por zero)

        4'b0100: result = A & B;                     // AND
        4'b0101: result = A | B;                     // OR
        4'b0110: result = ~(A | B);                  // NOR

        4'b0111: result = B << shamt;                // SLL 
        4'b1000: result = B >> shamt;                // SLR

        4'b1001: zero = (A == B);   // BEQ
        4'b1010: zero = (A != B);   // BNE
        4'b1011: zero = (A < B);    // BLT
        4'b1100: zero = (A > B);	// BGT
        4'b1101: zero = (A <= B);	// BLE
        4'b1110: zero = (A >= B);	// BGE

        default: begin
            result = 32'b0;
            zero = 1'b0;
        end

    endcase
end	

endmodule