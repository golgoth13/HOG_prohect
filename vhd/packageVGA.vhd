-------------------------------------------------------------------------------
-- packageVGA.vhd		Bibliothèque VGA
-------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

package packageVGA is

constant HM: integer := 799;		-- Taille max horizontale
constant HD: integer := 640;		-- Taille image horizontale
constant HF: integer := 16;		-- Front porch horizontal
constant HB: integer := 48;		-- Back porch horizontal
constant HP: integer := 96;		-- Pulse horizontal
constant VM: integer := 523;		-- Taille max verticale
constant VD: integer := 480;		-- Taille image verticale
constant VF: integer := 11;		-- Front porch vertical
constant VB: integer := 31;		-- Back porch vertical
constant VP: integer := 2;			-- Pulse vertical

type coordonnee is
record
	x : STD_LOGIC_VECTOR (9 downto 0);
	y : STD_LOGIC_VECTOR (8 downto 0);
end record;

end packageVGA;
