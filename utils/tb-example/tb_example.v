`timescale 1ns/100ps
`default_nettype none

`define HALF_PERIOD 10
`define SIMULATION_TIME 10000
`define DELTA 1

module tb_example;

integer stimuli_file, response_file;
logic clock, G0, G1, G2, G3, G17;
logic [3:0] primary_input;
logic [2:0] pseudo_input;
logic [0:0] primary_output;
logic [2:0] pseudo_output;
integer no_mismatches;
integer no_patterns;
integer return_code;

example uut (	.clock(clock), 
		.G0(G0), 
		.G1(G1), 
		.G2(G2), 
		.G3(G3), 
		.G17(G17)  
);
  
initial begin
	$timeformat(-9, 0, "ns", 10);
	clock = 1'b0;
	{G0, G1, G2, G3} = 4'd0;
	{uut.G5, uut.G6, uut.G7} = 3'd0;
	#`SIMULATION_TIME;
	$display("%t: simulation done with %d failures for %d patterns", $realtime, no_mismatches, no_patterns);
	$stop;
end

initial begin
	stimuli_file = $fopen("example.in", "rb");
	response_file = $fopen("example.out", "rb");
	no_mismatches = 0;
	no_patterns = 0;
	return_code = 0;
	#`SIMULATION_TIME;
	$fclose(stimuli_file);
	$fclose(response_file);
end

always begin
	#`HALF_PERIOD;
	clock = ~clock;
end

always @(posedge clock) begin: read_and_apply_and_compare

	return_code = $fscanf(stimuli_file, "%b\n", {primary_input, pseudo_input});
	if (return_code == -1) begin
		$display("%t: end of stimuli file with %d failures for %d patterns", $realtime, no_mismatches, no_patterns);
		$stop;
	end
	// $display("Applying primary/pseudo-input: %b_%b", primary_input, pseudo_input);

	#`DELTA;
	{G0, G1, G2, G3} = primary_input;
	{uut.G5, uut.G6, uut.G7} = pseudo_input;
	no_patterns++;

	#`DELTA;
	return_code = $fscanf(response_file, "%b\n", {primary_output, pseudo_output});
	if (return_code == -1) begin
		$display("%t: end of response file with %d failures for %d patterns", $realtime, no_mismatches, no_patterns);
		$stop;
	end
	// $display("Expected primary/pseudo-output: %b_%b", primary_output, pseudo_output);
	// $display("Observed primary/pseudo-output: %b_%b", G17, {uut.n34, uut.n37, uut.n40});
	if ((primary_output != {G17}) || (pseudo_output != {uut.n34, uut.n37, uut.n40})) begin
		$write("%t: mismatch in primary/pseudo-output: %b_%b vs %b_%b\n", $realtime, primary_output, pseudo_output, {G17}, {uut.n34, uut.n37, uut.n40});
		no_mismatches++;
	end
end

endmodule
