library IEEE;
use IEEE.Std_Logic_1164.all;

entity decod7seg is
port (	
		C: in std_logic_vector(2 downto 0);
		F: out std_logic_vector(6 downto 0)
		);
end decod7seg;

architecture decod_bhv of decod7seg is
begin
 F <=    "0001001" when C = "000" else
			"0000110" when C = "001" else 
			"1000111" when C = "010" else
			"1000000" when C = "011" else
			"1111111";
end decod_bhv;