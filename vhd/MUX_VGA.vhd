----------------------------------------------------------------------------------
-- Company:        ENSIMAG
-- Engineer:       Hans Julien, Perraud Frédéric
-- 
-- Create Date:    16:12:44 17/05/2015 
-- Design Name: 
-- Module Name:    MUX_VGA 
-- Project Name:   pedestre detection HLS
-- Target Devices: 
-- Tool versions: 
-- Description: 
--
-- Dependencies: 
--
-- Revision: 
-- Revision 0.01 - File Created
-- Additional Comments: 
--
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.NUMERIC_STD.ALL;

library work;
use work.packageVGA.all;

entity MUX_VGA is
  
  port (
    dataIn1 : IN std_logic_vector(7 downto 0);   -- Ram_vga
    dataIn2 : IN std_logic_vector(7 downto 0);  -- Ram_Hog
    Sel     : IN std_logic;
    dataOut : OUT std_logic_vector(7 downto 0);
    );
  
end MUX_VGA;

architecture Behavioral of MUX_VGA is

  begin
    process (dataIn1,dataIn2)
    begin
      if Sel then
        dataOut <= dataIn2;
      else
        dataOut <= dataIn1;
      end if;

    end process;     

end Behavioral;
    
