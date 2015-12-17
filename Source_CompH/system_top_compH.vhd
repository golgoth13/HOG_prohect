-------------------------------------------------------------------------------
-- system_top.vhd
-------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

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
 
 signal		CAMERA_DATA_q : std_logic_vector(7 downto 0);
 signal		CAMERA_HS_q :  std_logic;
 signal		CAMERA_VS_q :std_logic;

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

component mem_lum
	 Port ( clka : in STD_LOGIC;
			wea : in STD_LOGIC_VECTOR(0 DOWNTO 0);
    		addra : in STD_LOGIC_VECTOR(16 DOWNTO 0);
    		dina : in STD_LOGIC_VECTOR(7 DOWNTO 0);
    		clkb : in STD_LOGIC;
   		addrb : in STD_LOGIC_VECTOR(16 DOWNTO 0);
   		doutb : out STD_LOGIC_VECTOR(7 DOWNTO 0));
end component mem_lum;

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

component Comp_H is
	Port ( 
		start : IN STD_LOGIC;
		done : OUT STD_LOGIC;
		Comp_triosy_lz : OUT STD_LOGIC;
		Data_triosy_lz : OUT STD_LOGIC;
		clk : IN STD_LOGIC;
		rst : IN STD_LOGIC;
		Data_rsc_singleport_data_in : OUT STD_LOGIC_VECTOR (7 DOWNTO 0);    --useless
		Data_rsc_singleport_addr : OUT STD_LOGIC_VECTOR (16 DOWNTO 0);      
		Data_rsc_singleport_re : OUT STD_LOGIC;                             --useless
		Data_rsc_singleport_we : OUT STD_LOGIC;                             --useless
		Data_rsc_singleport_data_out : IN STD_LOGIC_VECTOR (7 DOWNTO 0); 
		Comp_rsc_singleport_data_in : OUT STD_LOGIC_VECTOR (7 DOWNTO 0); 
		Comp_rsc_singleport_addr : OUT STD_LOGIC_VECTOR (16 DOWNTO 0); 
		Comp_rsc_singleport_re : OUT STD_LOGIC;                             --useless
		Comp_rsc_singleport_we : OUT STD_LOGIC;
		Comp_rsc_singleport_data_out : IN STD_LOGIC_VECTOR (7 DOWNTO 0));     --useless
end component Comp_H;


signal clk_VGA, pclk_cam : STD_LOGIC; 
signal we : STD_LOGIC_VECTOR(0 DOWNTO 0);
signal address_cam, address_VGA : STD_LOGIC_VECTOR (16 downto 0);
signal data_cam : STD_LOGIC_VECTOR (7 downto 0);
signal data_VGA : STD_LOGIC_VECTOR (15 downto 0);
signal coord_VGA, coord_cam : coordonnee;
signal img_active : boolean;
signal hs, vs : STD_LOGIC; 
signal rst_VGA : STD_LOGIC; 
--signal CAMERA_DATA : STD_LOGIC_VECTOR (7 downto 0);
--signal CAMERA_HS, CAMERA_VS : STD_LOGIC;

-- Added for luminance
signal data_cam_temp : STD_LOGIC_VECTOR (15 downto 0);
signal data_VGA_temp : STD_LOGIC_VECTOR (7 downto 0);

-- Added for comp_H
signal address_in_ond, address_ond_out : STD_LOGIC_VECTOR (16 downto 0);
signal data_in_ond, data_ond_out : STD_LOGIC_VECTOR (7 downto 0);
signal we_ond_out : STD_LOGIC_VECTOR (0 downto 0);
signal start_signal : STD_LOGIC;

-- Test
signal u_a1, u_a2 : STD_LOGIC_VECTOR (16 downto 0);
signal u_d1, u_d2 : STD_LOGIC_VECTOR (7 downto 0);
signal u_r1, u_r2, u_w : STD_LOGIC;

begin

	start_signal <= '1';

	process(data_cam_temp)
	begin 
			data_cam <= (("000" & data_cam_temp(15 downto 11))	-- red
					+ data_cam_temp(10 downto 5)		-- green
					+ data_cam_temp(4 downto 0));		-- blue
	end process;

	process(data_VGA_temp)
	begin
			data_VGA <= data_VGA_temp(6 downto 2) 
					& data_VGA_temp(6 downto 1) 
					& data_VGA_temp(6 downto 2);
	end process;


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
 sync_cam : process(CAMERA_PCLK)
 begin
  if rising_edge(CAMERA_PCLK) then
		CAMERA_DATA_q  <= CAMERA_DATA ;
		CAMERA_HS_q <= CAMERA_HS;
		CAMERA_VS_q <= CAMERA_VS;
  end if;
 end process sync_cam;

capture: Camera_Capture
    Port map ( pclk => CAMERA_PCLK,
    		  reset => rst_VGA,
           href => CAMERA_HS_q,
           vs_cam => CAMERA_VS_q,
           data_in => CAMERA_DATA_q,
           addr => address_cam,
           data_out => data_cam_temp,
           coord => coord_cam,
           we => we
			  );
			  
ram: mem_lum
	 Port map ( clka => CAMERA_PCLK, -- CAMERA_PCLK marche pas, je sais pas pourquoi
	 -- Port <CAMERA_PCLK> has illegal connections.
	 -- This port is connected to an input buffer and other components.
		  wea => we,
    		  addra => address_cam,
    		  dina => data_cam,
    		  clkb => CAMERA_PCLK,
   		  addrb => address_in_ond,
   		  doutb => data_in_ond
   		  );
			  
ram2: mem_lum
	 Port map ( clka => CAMERA_PCLK,
		  wea => we_ond_out,
    		  addra => address_ond_out,
    		  dina => data_ond_out,
    		  clkb => clk_VGA,
   		  addrb => address_VGA,
   		  doutb => data_VGA_temp
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

comp_h1: Comp_H
	Port map ( 
		start => start_signal,
		done => open,
		Comp_triosy_lz => open,
		Data_triosy_lz => open,
		clk => clk_VGA,
		rst => rst_VGA,
		Data_rsc_singleport_data_in => u_d1,			 --useless
		Data_rsc_singleport_addr => address_in_ond,
		Data_rsc_singleport_re => u_r1,                           --useless
		Data_rsc_singleport_we => u_w,                            --useless
		Data_rsc_singleport_data_out => data_in_ond,
		Comp_rsc_singleport_data_in => data_ond_out, 
		Comp_rsc_singleport_addr => address_ond_out, 
		Comp_rsc_singleport_re => u_r2,                           --useless
		Comp_rsc_singleport_we => we_ond_out(0),
		Comp_rsc_singleport_data_out => u_d2			  --useless
		);


end architecture STRUCTURE;

