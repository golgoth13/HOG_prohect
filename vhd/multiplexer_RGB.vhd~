-------------------------------------------------------------------------------
-- multiplexer_RGB.vhd
-------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.NUMERIC_STD.ALL;

library work;
use work.packageVGA.all;

entity multiplexer_RGB is
    Port ( clk : in STD_LOGIC;
    		sw0 : in STD_LOGIC;
    		btn0 : in STD_LOGIC;							
			btn1 : in STD_LOGIC;
			btn2 : in STD_LOGIC;
			coord : in coordonnee;
			data  : in STD_LOGIC_VECTOR (15 downto 0);
			activeArea : in boolean;
			Hsync : in STD_LOGIC;
			Vsync : in STD_LOGIC;
			VGA_hs : out STD_LOGIC;
			VGA_vs : out STD_LOGIC;
			VGA_r : out STD_LOGIC_VECTOR (4 downto 0) := (others => '0');
			VGA_g : out STD_LOGIC_VECTOR (5 downto 0) := (others => '0');
			VGA_b : out STD_LOGIC_VECTOR (4 downto 0) := (others => '0'));
end multiplexer_RGB;

architecture Behavioral of multiplexer_RGB is
signal data_d, data_q : STD_LOGIC_VECTOR (15 downto 0);
signal red_d, red_q : STD_LOGIC_VECTOR (4 downto 0);
signal green_d, green_q : STD_LOGIC_VECTOR (5 downto 0);
signal blue_d, blue_q : STD_LOGIC_VECTOR (4 downto 0);
signal hs_d, hs_q, vs_d, vs_q : STD_LOGIC;

begin
	
	process(clk)
	begin
		if rising_edge(clk) then
			red_q <= red_d;
			green_q <= green_d;
			blue_q <= blue_d;
			hs_q <= hs_d;
			vs_q <= vs_d;
			data_q <= data_d;
   	end if;
   	
   end process;
   
	process(red_q, green_q, blue_q, hs_q, vs_q, data_q, activeArea, sw0, btn0, btn1, btn2, hsync, vsync, coord, data)
	begin
	
		red_d <= red_q;
		green_d <= green_q;
		blue_d <= blue_q;
		hs_d <= Hsync;
		vs_d <= Vsync;
		data_d <= data;
		VGA_r <= red_q;
		VGA_g <= green_q;
		VGA_b <= blue_q;
		VGA_hs <= hs_q;
		VGA_vs <= vs_q;
		
		if activeArea then
			if (btn0 = '1' or sw0 = '1') then 		-- Affichage image mémoire
				red_d <= data_q(15 downto 11); 
   			green_d <= data_q(10 downto 5);
   			blue_d <= data_q(4 downto 0);
			elsif btn1 = '1' then 	-- Génération mire 1
				red_d <= coord.x(3 downto 1)&"00"; 
   			green_d <= coord.x(6 downto 4)&"000";
   			blue_d <= coord.x(9 downto 7)&"00";
			elsif btn2 = '1' then	-- Génération mire 2
				red_d <= coord.y(6 downto 5)&"000"; 
   			green_d <= coord.y(4 downto 3)&"0000";
   			blue_d <= coord.y(2 downto 1)&"000";
			end if;
   	else 
   		red_d <= "00000"; 
   		green_d <= "000000";
   		blue_d <= "00000";
   	end if;
   	
   end process;
   
end Behavioral;


