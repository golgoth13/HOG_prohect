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
-- Revision 0.02 - File Created
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
    addrOut2 : out std_logic_vector (12 downto 0) := (others => '0');
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
    variable pixel : coordonnee;
    if activeIn then
      
      if (int_x >= FFX and int_x <= FLX) then
        if (int_y >= FFY and int_y <= FLY) then
          if (int_x >= SFX and int_x <= SLX) then
            if (int_y >= SFY and int_y <= SLY) then  --cas d'un recouvrement
              outSel <= '1';
              int_x := int_x - SFX;
              int_y := int_y - SFY;
              pixel.x := std_logic_vector(to_unsigned(int_x,7));
              pixel.y := std_logic_vector(to_unsigned(int_y,6)); 
              addrOut2 <=  pixel.y(5 downto 0) & pixel.x(6 downto 0); 
              activeOut <= activeIn;
            else
              outSel <= '0';
              int_x := int_x - FFX;
              int_y := int_y - FFY;
              pixel.x := std_logic_vector(to_unsigned(int_x,10));
              pixel.y := std_logic_vector(to_unsigned(int_y,9)); 
              addrOut1 <=  pixel.y(8 downto 0) & pixel.x(9 downto 0);
              activeOut <= activeIn;
            end if;

          else
            outSel <= '0';
            int_x := int_x - FFX;
            int_y := int_y - FFY;
            pixel.x := std_logic_vector(to_unsigned(int_x,10));
            pixel.y := std_logic_vector(to_unsigned(int_y,9)); 
            addrOut1 <=  pixel.y(8 downto 0) & pixel.x(9 downto 0);
            activeOut <= activeIn; 
            
          end if;    
          outSel <= '0';
          int_x := int_x - FFX;
          int_y := int_y - FFY;
          pixel.x := std_logic_vector(to_unsigned(int_x,10));
          pixel.y := std_logic_vector(to_unsigned(int_y,9)); 
          addrOut1 <=  pixel.y(8 downto 0) & pixel.x(9 downto 0);
          activeOut <= activeIn;
          
        else
          if (int_x >= SFX and int_x <= SLX) then
            if (int_y >= SFY and int_y <= SLY) then  --cas de la deuxième image
                                                     --au dessus ou en dessous
              outSel <= '1';
              int_x := int_x - SFX;
              int_y := int_y - SFY;
              pixel.x := std_logic_vector(to_unsigned(int_x,7));
              pixel.y := std_logic_vector(to_unsigned(int_y,6)); 
              addrOut2 <=  pixel.y(5 downto 0) & pixel.x(6 downto 0);
              activeOut <= activeIn;
            else
              activeOut <= '0';
            end if;

          else
            activeOut <= '0';   
          end if;
        end if;

      else
        if (int_x >= SFX and int_x <= SLX) then
            if (int_y >= SFY and int_y <= SLY) then  --cas de la deuxième image
                                                     --à gauche ou à droite
              outSel <= '1';
              int_x := int_x - SFX;
              int_y := int_y - SFY;
              pixel.x := std_logic_vector(to_unsigned(int_x,7));
              pixel.y := std_logic_vector(to_unsigned(int_y,6)); 
              addrOut2 <=  pixel.y(5 downto 0) & pixel.x(6 downto 0);              
              activeOut <= activeIn;
            else
              activeOut <= '0';
            end if;

          else
            activeOut <= '0';   
          end if;
      end if;
     end if;
      
  end process;

end Behavioral; 
