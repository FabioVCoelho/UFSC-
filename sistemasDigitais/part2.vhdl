library ieee;
use ieee.std.logic.1164.all;

entity part2 is
generic(width: positive := 8);
	port(SW : in std_logic_vector(17 downto 0);
	     ctrl: in std_logic;
	     LEDR: out std_logic_vector(17 downto 0);
	     LEDG : out std_logic_vector(width-1 downto 0)
	    );
end entity;

architecture behavior of part2 is
begin
	pinos: for i in (17 downto 0) generate
	LEDR[i] <= SW[i];
	end generate;

	multiplexadorDeOitoBits : for i in (width-1 downto 0) generate
	LEDG[i] <= (not(ctrl) and SW[i]) or (ctrl and SW[8+i]);
	end generate;
end architecture;
