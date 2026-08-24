module memoriaROM #(
    parameter DATA_WIDTH = 32,
    parameter ADDR_WIDTH = 8
) (
    input  logic                    clk,
    input  logic [ADDR_WIDTH-1:0]   addr,
    output logic [DATA_WIDTH-1:0]   q
);

    logic [DATA_WIDTH-1:0] rom [(2**ADDR_WIDTH)-1:0];

    initial begin
        $readmemb("codigo.mif", rom);
    end


	always_ff @(posedge clk) begin
		 q <= rom[addr];
	end

endmodule