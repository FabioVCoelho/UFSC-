library ieee;
use ieee.std_logic_1164.all;

entity Multiplexador5 is
	port(
	SWEM: in std_logic_vector (17 downto 0);
	M: out std_logic_vector (2 downto 0)
	);
end entity;

architecture behavior of Multiplexador5 is
signal U,V,W,X,Y,sel: std_logic_vector(2 downto 0);
begin
	U <= SWEM (14 downto 12);
	V <= SWEM (11 downto 9);
	W <= SWEM (8 downto 6);
	X <= SWEM (5 downto 3);
	Y <= SWEM (2 downto 0);
	sel <= SWEM (17 downto 15);
	
	M <= 	U when sel="000" else
			V when sel="001" else
			W when sel="010" else
			X when sel="011" else
			Y;
end architecture;