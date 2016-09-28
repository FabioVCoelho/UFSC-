library ieee;
use ieee.std_logic_1164.all;

entity decod7SegHex is
	port (
			HEX0: out std_logic_vector(6 downto 0);
			SW: in std_logic_vector(2 downto 0)
			);
end entity;

architecture behavior of decod7SegHex is
	component decod7seg
		port (
				C : in std_logic_vector(2 downto 0);
				F : out std_logic_vector(6 downto 0)
				);
	end component;
begin
	L0 : decod7seg port map (SW, HEX0);
end;