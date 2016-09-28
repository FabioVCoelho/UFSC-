library ieee;
use ieee.std_logic_1164.all;
entity decodificador2x4 is
    port(
        inpt: in std_logic_vector(1 downto 0);
        enable: in std_logic;
        outp: out std_logic_vector(3 downto 0)
        );
end decodificador2x4;
architecture decoder of decodificador2x4 is
begin
   outp <= "0000" when enable='0' else
           "0001" when inpt="00" else
           "0010" when inpt="01" else
           "0100" when inpt="10" else
           "1000";
end decoder;