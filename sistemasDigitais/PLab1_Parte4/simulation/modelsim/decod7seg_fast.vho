-- Copyright (C) 1991-2013 Altera Corporation
-- Your use of Altera Corporation's design tools, logic functions 
-- and other software and tools, and its AMPP partner logic 
-- functions, and any output files from any of the foregoing 
-- (including device programming or simulation files), and any 
-- associated documentation or information are expressly subject 
-- to the terms and conditions of the Altera Program License 
-- Subscription Agreement, Altera MegaCore Function License 
-- Agreement, or other applicable license agreement, including, 
-- without limitation, that your use is for the sole purpose of 
-- programming logic devices manufactured by Altera and sold by 
-- Altera or its authorized distributors.  Please refer to the 
-- applicable agreement for further details.

-- VENDOR "Altera"
-- PROGRAM "Quartus II 64-Bit"
-- VERSION "Version 13.0.1 Build 232 06/12/2013 Service Pack 1 SJ Web Edition"

-- DATE "04/26/2016 13:38:04"

-- 
-- Device: Altera EP2C35F672C6 Package FBGA672
-- 

-- 
-- This VHDL file should be used for ModelSim-Altera (VHDL) only
-- 

LIBRARY CYCLONEII;
LIBRARY IEEE;
USE CYCLONEII.CYCLONEII_COMPONENTS.ALL;
USE IEEE.STD_LOGIC_1164.ALL;

ENTITY 	decod7seg IS
    PORT (
	C : IN std_logic_vector(2 DOWNTO 0);
	F : OUT std_logic_vector(6 DOWNTO 0)
	);
END decod7seg;

-- Design Ports Information
-- F[0]	=>  Location: PIN_D14,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 24mA
-- F[1]	=>  Location: PIN_B11,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 24mA
-- F[2]	=>  Location: PIN_B14,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 24mA
-- F[3]	=>  Location: PIN_B12,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 24mA
-- F[4]	=>  Location: PIN_R25,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 24mA
-- F[5]	=>  Location: PIN_K23,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 24mA
-- F[6]	=>  Location: PIN_C12,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 24mA
-- C[0]	=>  Location: PIN_C13,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: Default
-- C[2]	=>  Location: PIN_D13,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: Default
-- C[1]	=>  Location: PIN_C11,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: Default


ARCHITECTURE structure OF decod7seg IS
SIGNAL gnd : std_logic := '0';
SIGNAL vcc : std_logic := '1';
SIGNAL unknown : std_logic := 'X';
SIGNAL devoe : std_logic := '1';
SIGNAL devclrn : std_logic := '1';
SIGNAL devpor : std_logic := '1';
SIGNAL ww_devoe : std_logic;
SIGNAL ww_devclrn : std_logic;
SIGNAL ww_devpor : std_logic;
SIGNAL ww_C : std_logic_vector(2 DOWNTO 0);
SIGNAL ww_F : std_logic_vector(6 DOWNTO 0);
SIGNAL \comb~0_combout\ : std_logic;
SIGNAL \comb~1_combout\ : std_logic;
SIGNAL \F[0]$latch~combout\ : std_logic;
SIGNAL \comb~2_combout\ : std_logic;
SIGNAL \comb~3_combout\ : std_logic;
SIGNAL \F[1]$latch~combout\ : std_logic;
SIGNAL \F[2]$latch~combout\ : std_logic;
SIGNAL \comb~4_combout\ : std_logic;
SIGNAL \Equal3~0_combout\ : std_logic;
SIGNAL \F[3]$latch~combout\ : std_logic;
SIGNAL \comb~5_combout\ : std_logic;
SIGNAL \F[0]~0_combout\ : std_logic;
SIGNAL \F[6]$latch~combout\ : std_logic;
SIGNAL \C~combout\ : std_logic_vector(2 DOWNTO 0);

BEGIN

ww_C <= C;
F <= ww_F;
ww_devoe <= devoe;
ww_devclrn <= devclrn;
ww_devpor <= devpor;

-- Location: PIN_C11,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: Default
\C[1]~I\ : cycloneii_io
-- pragma translate_off
GENERIC MAP (
	input_async_reset => "none",
	input_power_up => "low",
	input_register_mode => "none",
	input_sync_reset => "none",
	oe_async_reset => "none",
	oe_power_up => "low",
	oe_register_mode => "none",
	oe_sync_reset => "none",
	operation_mode => "input",
	output_async_reset => "none",
	output_power_up => "low",
	output_register_mode => "none",
	output_sync_reset => "none")
-- pragma translate_on
PORT MAP (
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	devoe => ww_devoe,
	oe => GND,
	padio => ww_C(1),
	combout => \C~combout\(1));

-- Location: PIN_C13,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: Default
\C[0]~I\ : cycloneii_io
-- pragma translate_off
GENERIC MAP (
	input_async_reset => "none",
	input_power_up => "low",
	input_register_mode => "none",
	input_sync_reset => "none",
	oe_async_reset => "none",
	oe_power_up => "low",
	oe_register_mode => "none",
	oe_sync_reset => "none",
	operation_mode => "input",
	output_async_reset => "none",
	output_power_up => "low",
	output_register_mode => "none",
	output_sync_reset => "none")
-- pragma translate_on
PORT MAP (
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	devoe => ww_devoe,
	oe => GND,
	padio => ww_C(0),
	combout => \C~combout\(0));

-- Location: PIN_D13,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: Default
\C[2]~I\ : cycloneii_io
-- pragma translate_off
GENERIC MAP (
	input_async_reset => "none",
	input_power_up => "low",
	input_register_mode => "none",
	input_sync_reset => "none",
	oe_async_reset => "none",
	oe_power_up => "low",
	oe_register_mode => "none",
	oe_sync_reset => "none",
	operation_mode => "input",
	output_async_reset => "none",
	output_power_up => "low",
	output_register_mode => "none",
	output_sync_reset => "none")
-- pragma translate_on
PORT MAP (
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	devoe => ww_devoe,
	oe => GND,
	padio => ww_C(2),
	combout => \C~combout\(2));

-- Location: LCCOMB_X30_Y35_N8
\comb~0\ : cycloneii_lcell_comb
-- Equation(s):
-- \comb~0_combout\ = (\C~combout\(0) & !\C~combout\(2))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000011001100",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datab => \C~combout\(0),
	datad => \C~combout\(2),
	combout => \comb~0_combout\);

-- Location: LCCOMB_X30_Y35_N26
\comb~1\ : cycloneii_lcell_comb
-- Equation(s):
-- \comb~1_combout\ = (!\C~combout\(0) & !\C~combout\(2))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000000110011",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datab => \C~combout\(0),
	datad => \C~combout\(2),
	combout => \comb~1_combout\);

-- Location: LCCOMB_X30_Y35_N16
\F[0]$latch\ : cycloneii_lcell_comb
-- Equation(s):
-- \F[0]$latch~combout\ = (!\comb~0_combout\ & ((\F[0]$latch~combout\) # (\comb~1_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011001100110000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datab => \comb~0_combout\,
	datac => \F[0]$latch~combout\,
	datad => \comb~1_combout\,
	combout => \F[0]$latch~combout\);

-- Location: LCCOMB_X30_Y35_N12
\comb~2\ : cycloneii_lcell_comb
-- Equation(s):
-- \comb~2_combout\ = (\C~combout\(2)) # (\C~combout\(1) $ (\C~combout\(0)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111111101100110",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \C~combout\(1),
	datab => \C~combout\(0),
	datad => \C~combout\(2),
	combout => \comb~2_combout\);

-- Location: LCCOMB_X30_Y35_N30
\comb~3\ : cycloneii_lcell_comb
-- Equation(s):
-- \comb~3_combout\ = (!\C~combout\(2) & (\C~combout\(1) $ (\C~combout\(0))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000001100110",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \C~combout\(1),
	datab => \C~combout\(0),
	datad => \C~combout\(2),
	combout => \comb~3_combout\);

-- Location: LCCOMB_X30_Y35_N10
\F[1]$latch\ : cycloneii_lcell_comb
-- Equation(s):
-- \F[1]$latch~combout\ = (\comb~2_combout\ & ((\comb~3_combout\) # (\F[1]$latch~combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1010101010001000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \comb~2_combout\,
	datab => \comb~3_combout\,
	datad => \F[1]$latch~combout\,
	combout => \F[1]$latch~combout\);

-- Location: LCCOMB_X30_Y35_N4
\F[2]$latch\ : cycloneii_lcell_comb
-- Equation(s):
-- \F[2]$latch~combout\ = (\comb~2_combout\ & ((\F[2]$latch~combout\) # (\comb~3_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1010101010100000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \comb~2_combout\,
	datac => \F[2]$latch~combout\,
	datad => \comb~3_combout\,
	combout => \F[2]$latch~combout\);

-- Location: LCCOMB_X30_Y35_N0
\comb~4\ : cycloneii_lcell_comb
-- Equation(s):
-- \comb~4_combout\ = (!\C~combout\(2) & ((\C~combout\(1)) # (\C~combout\(0))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000011101110",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \C~combout\(1),
	datab => \C~combout\(0),
	datad => \C~combout\(2),
	combout => \comb~4_combout\);

-- Location: LCCOMB_X30_Y35_N2
\Equal3~0\ : cycloneii_lcell_comb
-- Equation(s):
-- \Equal3~0_combout\ = (\C~combout\(1)) # ((\C~combout\(0)) # (\C~combout\(2)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111111111101110",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \C~combout\(1),
	datab => \C~combout\(0),
	datad => \C~combout\(2),
	combout => \Equal3~0_combout\);

-- Location: LCCOMB_X30_Y35_N22
\F[3]$latch\ : cycloneii_lcell_comb
-- Equation(s):
-- \F[3]$latch~combout\ = (!\comb~4_combout\ & ((\F[3]$latch~combout\) # (!\Equal3~0_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011001100000011",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datab => \comb~4_combout\,
	datac => \Equal3~0_combout\,
	datad => \F[3]$latch~combout\,
	combout => \F[3]$latch~combout\);

-- Location: LCCOMB_X30_Y35_N6
\comb~5\ : cycloneii_lcell_comb
-- Equation(s):
-- \comb~5_combout\ = (\C~combout\(1) & !\C~combout\(2))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000010101010",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \C~combout\(1),
	datad => \C~combout\(2),
	combout => \comb~5_combout\);

-- Location: LCCOMB_X30_Y35_N28
\F[0]~0\ : cycloneii_lcell_comb
-- Equation(s):
-- \F[0]~0_combout\ = (\C~combout\(1)) # (\C~combout\(2))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111111110101010",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \C~combout\(1),
	datad => \C~combout\(2),
	combout => \F[0]~0_combout\);

-- Location: LCCOMB_X30_Y35_N24
\F[6]$latch\ : cycloneii_lcell_comb
-- Equation(s):
-- \F[6]$latch~combout\ = (\F[0]~0_combout\ & ((\comb~5_combout\) # (\F[6]$latch~combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111101000000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \comb~5_combout\,
	datac => \F[6]$latch~combout\,
	datad => \F[0]~0_combout\,
	combout => \F[6]$latch~combout\);

-- Location: PIN_D14,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 24mA
\F[0]~I\ : cycloneii_io
-- pragma translate_off
GENERIC MAP (
	input_async_reset => "none",
	input_power_up => "low",
	input_register_mode => "none",
	input_sync_reset => "none",
	oe_async_reset => "none",
	oe_power_up => "low",
	oe_register_mode => "none",
	oe_sync_reset => "none",
	operation_mode => "output",
	output_async_reset => "none",
	output_power_up => "low",
	output_register_mode => "none",
	output_sync_reset => "none")
-- pragma translate_on
PORT MAP (
	datain => \F[0]$latch~combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	devoe => ww_devoe,
	oe => VCC,
	padio => ww_F(0));

-- Location: PIN_B11,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 24mA
\F[1]~I\ : cycloneii_io
-- pragma translate_off
GENERIC MAP (
	input_async_reset => "none",
	input_power_up => "low",
	input_register_mode => "none",
	input_sync_reset => "none",
	oe_async_reset => "none",
	oe_power_up => "low",
	oe_register_mode => "none",
	oe_sync_reset => "none",
	operation_mode => "output",
	output_async_reset => "none",
	output_power_up => "low",
	output_register_mode => "none",
	output_sync_reset => "none")
-- pragma translate_on
PORT MAP (
	datain => \F[1]$latch~combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	devoe => ww_devoe,
	oe => VCC,
	padio => ww_F(1));

-- Location: PIN_B14,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 24mA
\F[2]~I\ : cycloneii_io
-- pragma translate_off
GENERIC MAP (
	input_async_reset => "none",
	input_power_up => "low",
	input_register_mode => "none",
	input_sync_reset => "none",
	oe_async_reset => "none",
	oe_power_up => "low",
	oe_register_mode => "none",
	oe_sync_reset => "none",
	operation_mode => "output",
	output_async_reset => "none",
	output_power_up => "low",
	output_register_mode => "none",
	output_sync_reset => "none")
-- pragma translate_on
PORT MAP (
	datain => \F[2]$latch~combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	devoe => ww_devoe,
	oe => VCC,
	padio => ww_F(2));

-- Location: PIN_B12,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 24mA
\F[3]~I\ : cycloneii_io
-- pragma translate_off
GENERIC MAP (
	input_async_reset => "none",
	input_power_up => "low",
	input_register_mode => "none",
	input_sync_reset => "none",
	oe_async_reset => "none",
	oe_power_up => "low",
	oe_register_mode => "none",
	oe_sync_reset => "none",
	operation_mode => "output",
	output_async_reset => "none",
	output_power_up => "low",
	output_register_mode => "none",
	output_sync_reset => "none")
-- pragma translate_on
PORT MAP (
	datain => \F[3]$latch~combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	devoe => ww_devoe,
	oe => VCC,
	padio => ww_F(3));

-- Location: PIN_R25,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 24mA
\F[4]~I\ : cycloneii_io
-- pragma translate_off
GENERIC MAP (
	input_async_reset => "none",
	input_power_up => "low",
	input_register_mode => "none",
	input_sync_reset => "none",
	oe_async_reset => "none",
	oe_power_up => "low",
	oe_register_mode => "none",
	oe_sync_reset => "none",
	operation_mode => "output",
	output_async_reset => "none",
	output_power_up => "low",
	output_register_mode => "none",
	output_sync_reset => "none")
-- pragma translate_on
PORT MAP (
	datain => GND,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	devoe => ww_devoe,
	oe => VCC,
	padio => ww_F(4));

-- Location: PIN_K23,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 24mA
\F[5]~I\ : cycloneii_io
-- pragma translate_off
GENERIC MAP (
	input_async_reset => "none",
	input_power_up => "low",
	input_register_mode => "none",
	input_sync_reset => "none",
	oe_async_reset => "none",
	oe_power_up => "low",
	oe_register_mode => "none",
	oe_sync_reset => "none",
	operation_mode => "output",
	output_async_reset => "none",
	output_power_up => "low",
	output_register_mode => "none",
	output_sync_reset => "none")
-- pragma translate_on
PORT MAP (
	datain => GND,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	devoe => ww_devoe,
	oe => VCC,
	padio => ww_F(5));

-- Location: PIN_C12,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 24mA
\F[6]~I\ : cycloneii_io
-- pragma translate_off
GENERIC MAP (
	input_async_reset => "none",
	input_power_up => "low",
	input_register_mode => "none",
	input_sync_reset => "none",
	oe_async_reset => "none",
	oe_power_up => "low",
	oe_register_mode => "none",
	oe_sync_reset => "none",
	operation_mode => "output",
	output_async_reset => "none",
	output_power_up => "low",
	output_register_mode => "none",
	output_sync_reset => "none")
-- pragma translate_on
PORT MAP (
	datain => \F[6]$latch~combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	devoe => ww_devoe,
	oe => VCC,
	padio => ww_F(6));
END structure;


