----------------------------------------------------------------------------------
-- Company:        ENSIMAG
-- Engineer:       Hans Julien, Perraud Frédéric
-- 
-- Create Date:    16:12:44 11/05/2015 
-- Design Name: 
-- Module Name:    VGA_source_controller 
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

entity VGA_source_controller is
  
  port (                              
    addrIn : in std_logic_vector(16 downto 0);
    activeIn : in boolean;
    activeOut : out boolean;
    addrOut1 : out  std_logic_vector (16 downto 0) := (others => '0');
    addrOut2 : out std_logic_vector (7 downto 0) := (others => '0');
    outSel : out std_logic := '0';
    );

end VGA_source_controller;

architecture Behavioral of VGA_source_controller is
signal int_x,int_y : integer :=0;



begin

  -- purpose: determine la source de l'image en fonction des coordonnée 
  -- type   : combinational
  -- inputs : addrIn
  -- outputs: addrout1 ou addrout2 et outSel pour la sélection du mux
  process (addrIn)
  begin  -- process
    int_x := to_integer(unsigned(addrIn(9 downto 0)));
    int_y := to_integer(unsigned(addrIn(16 downto 10)));
    if activeIn then
      
      if (int_x >= FFX and int_x <= FLX) then
        if (int_y >= FFY and int_y <= FLY) then
          if (int_x >= SFX and int_x <= SLX) then
            if (int_y >= FFY and int_y <= FLY) then  --cas d'un recouvrement
              outSel <= '1';
              activeOut <= activeIn;
              else
                outSel <= '0';
                activeOut <= activeIn;
            end if;

          else
            outSel <= '0';
            activeOut <= activeIn; 
           
          end if;    
          outSel <= '0';
          activeOut <= activeIn;
        end if;
      else
         if (int_x >= SFX and int_x <= SLX) then
            if (int_y >= FFY and int_y <= FLY) then  --cas de la deuxième image
                                                     --au dessus ou en dessous
              outSel <= '1';
              activeOut <= activeIn;
              else
                activeOut <= '0';
            end if;

         else
           activeOut <= '0';   
         end if;

    else
     --to be continued
    end if;
    
  end process;

end Behavioral; 
