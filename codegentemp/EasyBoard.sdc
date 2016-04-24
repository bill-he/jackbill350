# THIS FILE IS AUTOMATICALLY GENERATED
# Project: C:\Users\jthem\Documents\PSoC Creator\PWMExample01\EasyBoard.cydsn\EasyBoard.cyprj
# Date: Wed, 06 Apr 2016 06:03:37 GMT
#set_units -time ns
create_clock -name {WaveDAC_1_Clock(routed)} -period 5000 -waveform {0 2500} [list [get_pins {ClockBlock/dclk_0}]]
create_clock -name {WaveDAC_0_Clock(routed)} -period 5000 -waveform {0 2500} [list [get_pins {ClockBlock/dclk_1}]]
create_clock -name {CyILO} -period 10000 -waveform {0 5000} [list [get_pins {ClockBlock/ilo}] [get_pins {ClockBlock/clk_100k}] [get_pins {ClockBlock/clk_1k}] [get_pins {ClockBlock/clk_32k}]]
create_clock -name {CyIMO} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/imo}]]
create_clock -name {CyPLL_OUT} -period 18.817204301075265 -waveform {0 9.40860215053763} [list [get_pins {ClockBlock/pllout}]]
create_clock -name {CyMASTER_CLK} -period 18.817204301075265 -waveform {0 9.40860215053763} [list [get_pins {ClockBlock/clk_sync}]]
create_generated_clock -name {CyBUS_CLK} -source [get_pins {ClockBlock/clk_sync}] -edges {1 2 3} [list [get_pins {ClockBlock/clk_bus_glb}]]
create_generated_clock -name {WaveDAC_1_Clock} -source [get_pins {ClockBlock/clk_sync}] -edges {1 267 531} -nominal_period 5000 [list [get_pins {ClockBlock/dclk_glb_0}]]
create_generated_clock -name {WaveDAC_0_Clock} -source [get_pins {ClockBlock/clk_sync}] -edges {1 267 531} -nominal_period 5000 [list [get_pins {ClockBlock/dclk_glb_1}]]


# Component constraints for C:\Users\jthem\Documents\PSoC Creator\PWMExample01\EasyBoard.cydsn\TopDesign\TopDesign.cysch
# Project: C:\Users\jthem\Documents\PSoC Creator\PWMExample01\EasyBoard.cydsn\EasyBoard.cyprj
# Date: Wed, 06 Apr 2016 06:03:14 GMT