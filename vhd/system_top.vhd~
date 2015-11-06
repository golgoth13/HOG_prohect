-------------------------------------------------------------------------------
-- system_top.vhd
-------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

library UNISIM;
use UNISIM.VCOMPONENTS.ALL;

library work;
use work.packageVGA.all;

entity system_top is
  Port ( processing_system7_0_MIO : inout std_logic_vector(53 downto 0);
		processing_system7_0_PS_SRSTB : in std_logic;
		processing_system7_0_PS_CLK : in std_logic;
		processing_system7_0_PS_PORB : in std_logic;
		processing_system7_0_DDR_Clk : inout std_logic;
		processing_system7_0_DDR_Clk_n : inout std_logic;
		processing_system7_0_DDR_CKE : inout std_logic;
		processing_system7_0_DDR_CS_n : inout std_logic;
		processing_system7_0_DDR_RAS_n : inout std_logic;
		processing_system7_0_DDR_CAS_n : inout std_logic;
		processing_system7_0_DDR_WEB : out std_logic;
		processing_system7_0_DDR_BankAddr : inout std_logic_vector(2 downto 0);
		processing_system7_0_DDR_Addr : inout std_logic_vector(14 downto 0);
		processing_system7_0_DDR_ODT : inout std_logic;
		processing_system7_0_DDR_DRSTB : inout std_logic;
		processing_system7_0_DDR_DQ : inout std_logic_vector(31 downto 0);
		processing_system7_0_DDR_DM : inout std_logic_vector(3 downto 0);
		processing_system7_0_DDR_DQS : inout std_logic_vector(3 downto 0);
		processing_system7_0_DDR_DQS_n : inout std_logic_vector(3 downto 0);
		processing_system7_0_DDR_VRN : inout std_logic;
		processing_system7_0_DDR_VRP : inout std_logic;
		processing_system7_0_I2C0_SDA : inout std_logic;
		processing_system7_0_I2C0_SCL : inout std_logic;
		led_io : inout std_logic_vector(3 downto 0);
		push_io : in std_logic_vector(3 downto 0);
		switch_io : in std_logic_vector(3 downto 0);
		clk : in std_logic;
		RED : out std_logic_vector(4 downto 0);
  		GREEN : out std_logic_vector(5 downto 0);
  		BLUE : out std_logic_vector(4 downto 0);
		VGA_VS : out std_logic;
		VGA_HS : out std_logic;
		CAMERA_DATA : in std_logic_vector(7 downto 0);
    	--CAMERA_PWREN : out std_logic;
		--CAMERA_RST : out std_logic;
		--CAMERA_SCL : inout std_logic;
		--CAMERA_SDA : inout std_logic;		
		CAMERA_XCLK : out std_logic;
		CAMERA_PCLK : in std_logic;
		CAMERA_HS : in std_logic;
		CAMERA_VS : in std_logic
  );
end system_top;

architecture STRUCTURE of system_top is

component system is
	 Port ( processing_system7_0_MIO : inout std_logic_vector(53 downto 0);
			 processing_system7_0_PS_SRSTB : in std_logic;
			 processing_system7_0_PS_CLK : in std_logic;
			 processing_system7_0_PS_PORB : in std_logic;
			 processing_system7_0_DDR_Clk : inout std_logic;
			 processing_system7_0_DDR_Clk_n : inout std_logic;
			 processing_system7_0_DDR_CKE : inout std_logic;
			 processing_system7_0_DDR_CS_n : inout std_logic;
			 processing_system7_0_DDR_RAS_n : inout std_logic;
			 processing_system7_0_DDR_CAS_n : inout std_logic;
			 processing_system7_0_DDR_WEB : out std_logic;
			 processing_system7_0_DDR_BankAddr : inout std_logic_vector(2 downto 0);
			 processing_system7_0_DDR_Addr : inout std_logic_vector(14 downto 0);
			 processing_system7_0_DDR_ODT : inout std_logic;
			 processing_system7_0_DDR_DRSTB : inout std_logic;
			 processing_system7_0_DDR_DQ : inout std_logic_vector(31 downto 0);
			 processing_system7_0_DDR_DM : inout std_logic_vector(3 downto 0);
			 processing_system7_0_DDR_DQS : inout std_logic_vector(3 downto 0);
			 processing_system7_0_DDR_DQS_n : inout std_logic_vector(3 downto 0);
			 processing_system7_0_DDR_VRN : inout std_logic;
			 processing_system7_0_DDR_VRP : inout std_logic;
			 processing_system7_0_I2C0_SDA : inout std_logic;
			 processing_system7_0_I2C0_SCL : inout std_logic);
end component system;

 attribute BOX_TYPE : STRING;
 attribute BOX_TYPE of system : component is "user_black_box";
 
component clk_pll
	 Port ( CLK_IN1 : in STD_LOGIC;
			CLK_OUT1 : out STD_LOGIC;
			CLK_OUT2 : out STD_LOGIC;
			RESET : in STD_LOGIC;
			LOCKED : out STD_LOGIC);
end component clk_pll;

--component Camera_Data_Simu
--    Port ( pclk : in STD_LOGIC;
--			  href : out STD_LOGIC;
--         vs : out STD_LOGIC;
--         data_out : out STD_LOGIC_VECTOR (7 downto 0));
--end component Camera_Data_Simu;

component VGA_generator
    Port ( clk : in STD_LOGIC;
    		btn3 : in STD_LOGIC;								
			Hsync : out STD_LOGIC;
			Vsync : out STD_LOGIC;
			addr : out STD_LOGIC_VECTOR (16 downto 0);
			coord : out coordonnee;
			activeArea : out boolean;
			reset : out STD_LOGIC);
end component VGA_generator;

component Camera_Capture
    Port ( pclk : in STD_LOGIC;
    	   reset : in STD_LOGIC;
         href : in STD_LOGIC;
			vs_cam : in STD_LOGIC;
			data_in : in STD_LOGIC_VECTOR (7 downto 0);
			addr : out STD_LOGIC_VECTOR (16 downto 0);
			data_out : out STD_LOGIC_VECTOR (15 downto 0);
			coord : out coordonnee;
			we : out STD_LOGIC_VECTOR(0 DOWNTO 0));
end component Camera_Capture;

component mem_ram
	 Port ( clka : in STD_LOGIC;
			wea : in STD_LOGIC_VECTOR(0 DOWNTO 0);
    		addra : in STD_LOGIC_VECTOR(16 DOWNTO 0);
    		dina : in STD_LOGIC_VECTOR(15 DOWNTO 0);
    		clkb : in STD_LOGIC;
   		addrb : in STD_LOGIC_VECTOR(16 DOWNTO 0);
   		doutb : out STD_LOGIC_VECTOR(15 DOWNTO 0));
end component mem_ram;

component multiplexer_RGB is
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
			VGA_r : out STD_LOGIC_VECTOR (4 downto 0);
			VGA_g : out STD_LOGIC_VECTOR (5 downto 0);
			VGA_b : out STD_LOGIC_VECTOR (4 downto 0));
end component multiplexer_RGB;

signal clk_VGA, pclk_cam : STD_LOGIC; 
signal we : STD_LOGIC_VECTOR(0 DOWNTO 0);
signal address_cam, address_VGA : STD_LOGIC_VECTOR (16 downto 0);
signal data_cam, data_VGA : STD_LOGIC_VECTOR (15 downto 0);
signal coord_VGA, coord_cam : coordonnee;
signal img_active : boolean;
signal hs, vs : STD_LOGIC; 
signal rst_VGA : STD_LOGIC; 
--signal CAMERA_DATA : STD_LOGIC_VECTOR (7 downto 0);
--signal CAMERA_HS, CAMERA_VS : STD_LOGIC;

begin

system_i: system
	 Port map ( processing_system7_0_MIO => processing_system7_0_MIO,
			 processing_system7_0_PS_SRSTB => processing_system7_0_PS_SRSTB,
			 processing_system7_0_PS_CLK => processing_system7_0_PS_CLK,
			 processing_system7_0_PS_PORB => processing_system7_0_PS_PORB,
			 processing_system7_0_DDR_Clk => processing_system7_0_DDR_Clk,
			 processing_system7_0_DDR_Clk_n => processing_system7_0_DDR_Clk_n,
			 processing_system7_0_DDR_CKE => processing_system7_0_DDR_CKE,
			 processing_system7_0_DDR_CS_n => processing_system7_0_DDR_CS_n,
			 processing_system7_0_DDR_RAS_n => processing_system7_0_DDR_RAS_n,
			 processing_system7_0_DDR_CAS_n => processing_system7_0_DDR_CAS_n,
			 processing_system7_0_DDR_WEB => processing_system7_0_DDR_WEB,
			 processing_system7_0_DDR_BankAddr => processing_system7_0_DDR_BankAddr,
			 processing_system7_0_DDR_Addr => processing_system7_0_DDR_Addr,
			 processing_system7_0_DDR_ODT => processing_system7_0_DDR_ODT,
			 processing_system7_0_DDR_DRSTB => processing_system7_0_DDR_DRSTB,
			 processing_system7_0_DDR_DQ => processing_system7_0_DDR_DQ,
			 processing_system7_0_DDR_DM => processing_system7_0_DDR_DM,
			 processing_system7_0_DDR_DQS => processing_system7_0_DDR_DQS,
			 processing_system7_0_DDR_DQS_n => processing_system7_0_DDR_DQS_n,
			 processing_system7_0_DDR_VRN => processing_system7_0_DDR_VRN,
			 processing_system7_0_DDR_VRP => processing_system7_0_DDR_VRP,
			 processing_system7_0_I2C0_SDA => processing_system7_0_I2C0_SDA,
			 processing_system7_0_I2C0_SCL => processing_system7_0_I2C0_SCL
			 );

pll: clk_pll
	 Port map ( CLK_IN1 => clk,	 -- 125 MHz
			CLK_OUT1 => clk_VGA,		 -- 24 MHz
			CLK_OUT2 => CAMERA_XCLK, -- 24 MHz
			RESET => push_io(3),
			LOCKED => led_io(0)
			);

led_io(1) <= '0';
led_io(2) <= '0';
led_io(3) <= '1';
		
--cam_clk_buf : IBUFG
--	Port map
--   (O => pclk_cam,
--    I => CAMERA_PCLK);
    
--cam_simu: Camera_Data_Simu
--    Port map ( pclk => pclk_cam,
--			    href => CAMERA_HS,
--           vs => CAMERA_VS,
--           data_out => CAMERA_DATA
--			    );

vga: VGA_generator
    Port map ( clk => clk_VGA,
    		  btn3 => push_io(3),
           Hsync => hs,
           Vsync => vs,
			  addr => address_VGA,
			  coord => coord_VGA,
			  activeArea => img_active,
			  reset => rst_VGA
			  );

capture: Camera_Capture
    Port map ( pclk => CAMERA_PCLK,
    		  reset => rst_VGA,
           href => CAMERA_HS,
           vs_cam => CAMERA_VS,
           data_in => CAMERA_DATA,
           addr => address_cam,
           data_out => data_cam,
           coord => coord_cam,
           we => we
			  );
			  
ram: mem_ram
	 Port map ( clka => CAMERA_PCLK,
			  wea => we,
    		  addra => address_cam,
    		  dina => data_cam,
    		  clkb => clk_VGA,
   		  addrb => address_VGA,
   		  doutb => data_VGA
   		  );
   		  
mux: multiplexer_RGB
    Port map ( clk => clk_VGA,
    		  sw0 => switch_io(0),
    		  btn0 => push_io(0),
			  btn1 => push_io(1),	
			  btn2 => push_io(2),
			  coord => coord_VGA,
			  data => data_VGA,
			  activeArea => img_active,
			  Hsync => hs,
			  Vsync => vs,
			  VGA_hs => VGA_HS,
			  VGA_vs => VGA_VS,
			  VGA_r => RED,
			  VGA_g => GREEN,
			  VGA_b => BLUE
			  );

end architecture STRUCTURE;

