module mux3 (
    input logic [1:0] selecao,
    input logic [31:0] entrada1,
    input logic [31:0] entrada2,
    input logic [31:0] entrada3,

    output logic [31:0] saida
);

always_comb begin
    case (selecao)
        2'b00: saida = entrada1;
        2'b01: saida = entrada2;
        2'b10: saida = entrada3;
        default: saida = 32'b0;
    endcase
end

endmodule
