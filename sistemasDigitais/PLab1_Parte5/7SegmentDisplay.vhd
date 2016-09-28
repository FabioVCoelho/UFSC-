library ieee;
use ieee.std_logic_1164.all;

entity SegmentDisplay is
	port(	
			SW : in std_logic_vector(17 downto 0);
			LEDR : out std_logic_vector(17 downto 0);
			LEDG : out std_logic_vector(7 downto 0);
			Hex0: out std_logic_vector(6 downto 0)
	);
end entity;

architecture behavior of SegmentDisplay is
signal entradaDecod : std_logic_vector(2 downto 0);
component decod7SegHex
	port (
			HEX0: out std_logic_vector(6 downto 0);
			SW: in std_logic_vector(2 downto 0)
			);
end component;

component Mux8Bit
		port (
				SW : in std_logic_vector(17 downto 0);
				M : out std_logic_vector (7 downto 0)
				);
end component;
begin
	L0 : port map Mux8Bit(SW, entradaDecod);
	L1 : port map decod7SegHex(Hex0, entradaDecod);
	LEDR <= SW;
	LEDG <= entradaDecod;
end;