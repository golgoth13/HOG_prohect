----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    16:12:44 02/18/2015 
-- Design Name: 
-- Module Name:    VGA_generator - Behavioral 
-- Project Name: 
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

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity VGA_generator is
    Port ( clk : in STD_LOGIC;
    		btn3 : in STD_LOGIC;							
			Hsync : out STD_LOGIC := '0';
			Vsync : out STD_LOGIC := '0';
			addr : out STD_LOGIC_VECTOR (16 downto 0) := (others => '0');
			coord : out coordonnee;
			activeArea : out boolean;
			reset : out STD_LOGIC);
end VGA_generator;

architecture Behavioral of VGA_generator is
signal Hcnt, Vcnt : integer := 0;
signal int_x, int_y : integer := 0;	
signal Hsync_temp, Vsync_temp : STD_LOGIC := '0';
signal activeArea_h, activeArea_v : boolean;

constant Hstart_img : integer := HP+HB;
constant Hend_img : integer := HP+HB+HD-1;
constant Vstart_img : integer := VP+VB;
constant Vend_img : integer := VP+VB+VD-1;

begin
	
-- Compteur et génération addresses
	process(clk)
	variable pixel : coordonnee;
	begin
		if rising_edge(clk) then
			reset <= btn3;
			if (Hcnt <= HM) then
				Hcnt <= Hcnt+1;
			else
				Hcnt <= 0;
				if (Vcnt <= VM) then
					Vcnt <= Vcnt+1;
				else
					Vcnt <= 0;
				end if;
			end if;
			Hsync <= Hsync_temp;
			Vsync <= Vsync_temp;
			pixel.x := std_logic_vector(to_unsigned(int_x,10)); -- Affectation immédiate
			pixel.y := std_logic_vector(to_unsigned(int_y,9));
			coord.x <= pixel.x; -- Mise à jour des coordonnées du pixel de l'image
			coord.y <= pixel.y;
			addr <= pixel.y(8 downto 1) & pixel.x(9 downto 1); -- Envoi de l'adresse de la case mémoire à lire
			activeArea <= activeArea_v and activeArea_h;
		end if;
	end process;

	process(Hcnt)
	begin
		if (Hcnt >= Hstart_img and Hcnt <= Hend_img) then -- 144 <= Hcnt <= 783
			activeArea_h <= true;
			int_x <= Hcnt-Hstart_img; -- Décompte de horizontal pulse et backporch
		else
			activeArea_h <= false;
			int_x <= 0;
		end if;
	end process;

	process(Vcnt)
	begin
		if (Vcnt >= Vstart_img and Vcnt <= Vend_img) then -- 33 <= Vcnt <= 512
			activeArea_v <= true;
			int_y <= Vcnt-Vstart_img; -- Décompte de vertical pulse et backporch
		else
        	activeArea_v <= false;
       	int_y <= 0;
		end if;
	end process;  

-- Génération Hsync
	process(Hcnt)
	begin
		if (Hcnt >= HP and Hcnt <= HM) then -- 96 <= Hcnt <= 799
			Hsync_temp <= '1';
		else
			Hsync_temp <= '0';
		end if;
	end process;

-- Génération Vsync
	process(Vcnt)
	begin
		if (Vcnt >= VP and Vcnt <= VM) then -- 2 <= Vcnt <= 523
			Vsync_temp <= '1';
		else
			Vsync_temp <= '0';
		end if;  		
	end process;
	
end Behavioral;

