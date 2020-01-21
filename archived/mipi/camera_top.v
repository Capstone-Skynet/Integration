module camera_top(	input CLOCK_50,
					output unsigned [7:0] VGA_R, VGA_G, VGA_B,
					output VGA_CLK, VGA_HS, VGA_VS, VGA_BLANK_N, VGA_SYNC_N);
	
	wire clk, clk_25;
	assign clk = CLOCK_50;

	assign VGA_SYNC_N = 1'b0;
	assign VGA_CLK = clk_25;

	clock_divider cd1(	.in_clk	(clk),
						.reset	(0),
						.outclk	(clk_25));


	wire [9:0] Hout, Vout;
	reg [7:0] red, green, blue;
	reg [7:0] c1,c2,c3;
	

	Graphics_Controller gc ( 	.Clock				(clk_25),
								.Reset				(1'b1),
								.Red				(red),
								.Green				(green),
								.Blue				(blue),
								.VScrollOffset 		(10'b0),
								.HScrollOffset 		(10'b0), 
								.H_Sync_out			(VGA_HS),
								.V_Sync_out			(VGA_VS),
								.VideoBlanking_L	(VGA_BLANK_N),
								.Red_out			(VGA_R),
								.Green_out			(VGA_G),
								.Blue_out			(VGA_B),
								.Column_out			(Hout),
								.Row_out			(Vout);
	
	
	reg [27:0] clk_counter = 28'b0;
	reg [11:0] miniute_clk = 12'b0;
	always @(posedge clk) begin
		if (clk_counter == 28'd50000000) begin
			clk_counter <= 28'b0;
			miniute_clk <= miniute_clk + 12'b1;
		end else begin
			clk_counter <= clk_counter + 28'b1;
		end
	end

	// four sectors
	always @(*) begin
		if (Hout < 10'd160) begin
			red = c1;
			green = c2;
			blue = c3;
		end else if (Hout < 10'd320) begin
			red = c3;
			green = c1;
			blue = c2;
		end	else if (Hout < 10'd480) begin
			red = c2;
			green = c3;
			blue = c1;
		end else begin
			red = c1;
			green = c2;
			blue = c3;
		end
	end
	
	//change colour of each sector every second
	always @(*) begin
		case(miniute_clk[1:0])
			2'b00: begin
				c1 = 8'b11111111;
				c2 = 8'b0;
				c3 = 8'b0;
			end
			
			2'b01: begin
				c1 = 8'b0;
				c2 = 8'b11111111;
				c3 = 8'b0;
			end

			default: begin
				c1 = 8'b0;
				c2 = 8'b0;
				c3 = 8'b11111111;
			end
	end

endmodule