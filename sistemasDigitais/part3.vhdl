library ieee;
use ieee.std.logic.1164.all;

entity part3 is
generic(width: positive := 18);
	port( SW : in std_logic_vector(width-1 downto 0);
	      LEDR: out std_logic_vector(width-1 downto 0);
	      ctrl,U,V,W,X,Y: in std_logic_vector(2 downto 0);
	      LEDG: out std_logic_vector(2 downto 0)
	);
end entity;

architecture behavior of part3 is
begin
	pinos: for i in (width-1 downto 0) generate
	LEDR[i] <= SW[i];
	end generate;

	threeBitWide: for j in (2 downto 0) generate
	U[j] = SW[j];
	V[j] = SW[3+j];
	W[j] = SW[6+j];
	X[j] = SW[9+j];
	Y[j] = SW[12+j];
	ctrl[j] = SW[15+j];
	end generate;

	LEDG <= U when ctrl="000" else
		V when ctrl="001" else
		W when ctrl="010" else
		X when ctrl="011" else
		Y when ctrl="100" else
		"000";
end architecture;
