----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    16:13:40 02/23/2015 
-- Design Name: 
-- Module Name:    Camera_Capture - Behavioral 
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
use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

library work;
use work.packageVGA.all;

entity Camera_Capture is
    Port ( pclk : in STD_LOGIC;
    		reset : in STD_LOGIC;
			href : in STD_LOGIC;
         vs_cam : in STD_LOGIC;
         data_in : in STD_LOGIC_VECTOR (7 downto 0);
         addr : out STD_LOGIC_VECTOR (16 downto 0);
         data_out : out STD_LOGIC_VECTOR (15 downto 0);
			coord : out coordonnee;
         we : out STD_LOGIC_VECTOR(0 DOWNTO 0));
end Camera_Capture;

architecture Behavioral of Camera_Capture is
type FSM_type is (AttenteFrame, NewFrame, GetHighFirst, GetLowWrite, GetHigh);
signal etat_d, etat_q : FSM_type;
signal data_d, data_q : STD_LOGIC_VECTOR(7 downto 0) := (others => '0');
signal Hcnt_d, Hcnt_q : integer := 0;
signal Vcnt_d, Vcnt_q : integer := 0;
   
begin

	sync: process(pclk, reset)
	begin
		if reset = '1' then
			etat_q <= AttenteFrame;
			Hcnt_q <= 0;
			Vcnt_q <= 0;
			data_q <= (others => '0');
		elsif rising_edge(pclk) then
			Hcnt_q <= Hcnt_d;
			Vcnt_q <= Vcnt_d;
			etat_q <= etat_d;
			data_q <= data_d;
		end if;
	end process;
	
	comb: process(etat_q, Hcnt_q, Vcnt_q, href, vs_cam, data_q, data_in)
	variable pixel : coordonnee;
	begin
		
		etat_d <= etat_q;
		Hcnt_d <= Hcnt_q;
		Vcnt_d <= Vcnt_q;
		etat_d <= etat_q;
		data_d <= data_q;
		
		we <= "0";
		data_out <= (others => '0');
				
		pixel.x := std_logic_vector(to_unsigned(Hcnt_q,10));
		pixel.y := std_logic_vector(to_unsigned(Vcnt_q,9));
		coord.x <= pixel.x;
		coord.y <= pixel.y;
		addr <= pixel.y(8 downto 1) & pixel.x(9 downto 1);
   
		case etat_q is
			when AttenteFrame => -- Attente du signal vs
				Hcnt_d <= 0;
				Vcnt_d <= 0;
				data_out <= (others => '0');
				if vs_cam = '1' then
					etat_d <= NewFrame;
				end if;
			
			when NewFrame => -- RAZ coordonnées pixel, addresse et data de sortie
				Hcnt_d <= 0;
				Vcnt_d <= 0;
				data_out <= (others => '0');
				if vs_cam = '0' then
					etat_d <= GetHighFirst;
				end if;
			
			when GetHighFirst => -- Capture premier octet poids fort RGB de la ligne
				data_d <= data_in;
				if href = '1' then
					etat_d <= GetLowWrite;
				end if;
				
			when GetLowWrite => -- Capture octet poids faible RGB: gggb bbbb
				pixel.x := std_logic_vector(to_unsigned(Hcnt_q,10));
				pixel.y := std_logic_vector(to_unsigned(Vcnt_q,9));
				coord.x <= pixel.x;
				coord.y <= pixel.y;
				addr <= pixel.y(8 downto 1) & pixel.x(9 downto 1); -- Calcul case mémoire stockage du pixel
				data_out(15 downto 0) <= data_in(7 downto 0) & data_q(7 downto 0);
				we <= "1";			-- Autorisation d'écriture				
				etat_d <= GetHigh;
							
			when GetHigh => -- Capture octet poids fort RGB: rrrr rggg
				data_d <= data_in;
				if href = '1' then
					if (Hcnt_q < HD) then
						Hcnt_d <= Hcnt_q+1;						
					else								-- Attente début nouveau frame
						Hcnt_d <= 0;
					end if;					
					etat_d <= GetLowWrite;
				elsif href = '0' then
					if (Vcnt_q < VD) then 		-- Début nouvelle ligne
						Hcnt_d <= 0;
						Vcnt_d <= Vcnt_q+1;
						etat_d <= GetHighFirst;
					else
						etat_d <= AttenteFrame; -- Attente début nouveau frame						
					end if;
				end if;
					
		end case;
	end process;
		
end Behavioral;


