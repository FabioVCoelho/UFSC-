library ieee;
use ieee.std_logic_1164.all;

entity rotate is
generic (width: integer:= 8);
port (
    inpt: in std_logic_vector(width-1 downto 0);
    ctrl: in std_logic;
    outp: out std_logic_vector(width-1 downto 0)
);
end;

architecture behavior of rotate is
begin
    outp <= inpt(width-2 downto 0) & inpt(width-1) when ctrl='0' else
            inpt(0) & inpt(width-1 downto 1);
end;