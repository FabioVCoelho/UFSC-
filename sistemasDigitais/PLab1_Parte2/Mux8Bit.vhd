library ieee;
use ieee.std_logic_1164.all;

entity Mux8Bit is
	port (SW : in std_logic_vector(17 downto 0);
			LEDR : out std_logic_vector (7 downto 0)
		 );
end entity;

architecture arq of Mux8Bit is
	
	component multiplexador_2x1
	port (S : in std_logic;
			X : in std_logic;
			Y : in std_logic;
			M : out std_logic
		 );
	end component;
	signal signalOut :std_logic_vector(7 downto 0);
	signal X : std_logic_vector(7 downto 0);
	signal Y : std_logic_vector(7 downto 0);
	
begin
	X <= SW(7 downto 0);
	Y <= SW(15 downto 8);
	L0 : multiplexador_2x1 port map(SW(17), X(0), Y(0), signalOut(0));
	L1 : multiplexador_2x1 port map(SW(17), X(1), Y(1), signalOut(1));
	L2 : multiplexador_2x1 port map(SW(17), X(2), Y(2), signalOut(2));
	L3 : multiplexador_2x1 port map(SW(17), X(3), Y(3), signalOut(3));
	L4 : multiplexador_2x1 port map(SW(17), X(4), Y(4), signalOut(4));
	L5 : multiplexador_2x1 port map(SW(17), X(5), Y(5), signalOut(5));
	L6 : multiplexador_2x1 port map(SW(17), X(6), Y(6), signalOut(6));
	L7 : multiplexador_2x1 port map(SW(17), X(7), Y(7), signalOut(7));
	LEDR <= signalOut;
end architecture;