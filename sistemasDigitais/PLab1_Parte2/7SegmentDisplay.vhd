library ieee;
use ieee.std_logic_1164.all;

entity 7SegmentDisplay is
	port(
	sw: in std_logic_vector (17 downto 0);
	m: out std_logic_vector (2 downto 0);
	ledr: out std_logic_vector (17 downto 0);
	ledg: out std_logic_vector (2 downto 0)
	);
end entity;