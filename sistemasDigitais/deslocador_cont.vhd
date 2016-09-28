library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity deslocador_cont is
generic(width:integer :=8);
port(
    inpt: in unsigned(width-1 downto 0);
    op: in unsigned(1 downto 0);
    outp: out unsigned(width-1 downto 0)
    );
end entity;

architecture deslocador of deslocador_cont is
begin
    outp <= unsigned(inpt) when op="00" else
            unsigned(std_logic_vector(inpt(width-2 downto 0)) & '0') when op="01" else
            unsigned(std_logic_vector(inpt(width-3 downto 0)) & "00") when op="10" else
            unsigned(std_logic_vector(inpt(width-4 downto 0)) & "000");
end deslocador;
