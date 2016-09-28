library ieee;
use ieee.std.logic.1164.all;

entity part1 is
	port( SW : in std_logic_vector(17 downto 0);
	      LEDR: out std_logic_vector(17 downto 0)
	);
end entity;

architecture behavior of part1 is
begin
	pinos: for i in (17 downto 0) generate
	LEDR[i] <= SW[i];
	end generate;
end architecture;
