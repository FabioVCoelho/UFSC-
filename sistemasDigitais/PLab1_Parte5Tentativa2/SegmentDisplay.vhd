library ieee;
use ieee.std_logic_1164.all;

entity SegmentDisplay is
	port(	
		Hex0,Hex1,Hex2,Hex3,Hex4,Hex5: out std_logic_vector(6 downto 0)
	);
end entity;

architecture behavior of SegmentDisplay is
component decod7Seg
	port (
			C: in std_logic_vector(2 downto 0);
			F: out std_logic_vector(6 downto 0)
			);
end component;

begin
	L5 : decod7Seg port map ("000", Hex5);
	L4 : decod7Seg port map ("001", Hex4);
	L3 : decod7Seg port map ("010", Hex3);
	L2 : decod7Seg port map ("010", Hex2);
	L1 : decod7Seg port map ("011", Hex1);
	L0 : decod7Seg port map ("111", Hex0);
end;
