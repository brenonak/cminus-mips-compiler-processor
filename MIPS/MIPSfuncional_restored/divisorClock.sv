module divisorClock #(
    parameter DIVISOR = 5_000_000 // Divide 50MHz para 10Hz por padrão
) (
    input  logic clk_in,
    output logic clk_out
);
    logic [$clog2(DIVISOR)-1:0] counter = 0;

    always_ff @(posedge clk_in) begin
        if (counter >= (DIVISOR - 1))
            counter <= 0;
        else
            counter <= counter + 1;
    end

    assign clk_out = (counter < DIVISOR/2) ? 1'b1 : 1'b0;
endmodule