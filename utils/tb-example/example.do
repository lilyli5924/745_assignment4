onbreak {resume}

transcript on

if {[file exists rtl_work]} {
	vdel -lib rtl_work -all
}
vlib rtl_work
vmap work rtl_work

# load designs
vlog -sv -svinputport=var -work rtl_work example.v
vlog -sv -svinputport=var -work rtl_work tb_example.v

# specify library for simulation
vsim -novopt -t 100ps -L altera_mf_ver -lib rtl_work tb_example

# Clear previous simulation
restart -f

# activate waveform simulation
view wave

# add signals to waveform
add wave clock
add wave uut/G0
add wave uut/G1
add wave uut/G2
add wave uut/G3
add wave uut/G5
add wave uut/G6
add wave uut/G7
add wave uut/G17

# format signal names in waveform
configure wave -signalnamewidth 1

# run complete simulation
run -all

simstats
