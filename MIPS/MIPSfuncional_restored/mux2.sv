module mux2 (
    input logic selecao,
    input logic [31:0] entrada1,
    input logic [31:0] entrada2,

    output logic [31:0] saida
);

always_comb begin
    case (selecao)
        1'b0: saida = entrada1;
        1'b1: saida = entrada2;
        
        default: saida = 32'b0;
    endcase
end

endmodule