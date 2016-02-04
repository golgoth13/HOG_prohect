--------------------------------------------------------------------------------
-- Company:        ENSIMAG
-- Engineer:       Hans Julien, Perraud Frédéric
--
-- Create Date:    08:11:44 11/10/2015
-- Design Name:
-- Module Name:    system_top.vhd
-- Project Name:   pedestre detection HLS
-- Target Devices:
-- Tool versions:
-- Description:
--
-- Dependencies:
--
-- Revision:
-- Revision 2.01 - FIle compile and produce output
-- Additional Comments:
--
--------------------------------------------------------------------------------

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_UNSIGNED.all;
--use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.NUMERIC_STD.ALL;

library UNISIM;
use UNISIM.VCOMPONENTS.ALL;

library work;
use work.packageVGA.all;


entity system_top is
  Port ( processing_system7_0_MIO          : inout std_logic_vector(53 downto 0);
         processing_system7_0_PS_SRSTB     : in std_logic;
         processing_system7_0_PS_CLK       : in std_logic;
         processing_system7_0_PS_PORB      : in std_logic;
         processing_system7_0_DDR_Clk      : inout std_logic;
         processing_system7_0_DDR_Clk_n    : inout std_logic;
         processing_system7_0_DDR_CKE      : inout std_logic;
         processing_system7_0_DDR_CS_n     : inout std_logic;
         processing_system7_0_DDR_RAS_n    : inout std_logic;
         processing_system7_0_DDR_CAS_n    : inout std_logic;
         processing_system7_0_DDR_WEB      : out std_logic;
         processing_system7_0_DDR_BankAddr : inout std_logic_vector(2 downto 0);
         processing_system7_0_DDR_Addr     : inout std_logic_vector(14 downto 0);
         processing_system7_0_DDR_ODT      : inout std_logic;
         processing_system7_0_DDR_DRSTB    : inout std_logic;
         processing_system7_0_DDR_DQ       : inout std_logic_vector(31 downto 0);
         processing_system7_0_DDR_DM       : inout std_logic_vector(3 downto 0);
         processing_system7_0_DDR_DQS      : inout std_logic_vector(3 downto 0);
         processing_system7_0_DDR_DQS_n    : inout std_logic_vector(3 downto 0);
         processing_system7_0_DDR_VRN      : inout std_logic;
         processing_system7_0_DDR_VRP      : inout std_logic;
         processing_system7_0_I2C0_SDA     : inout std_logic;
         processing_system7_0_I2C0_SCL     : inout std_logic;
         led_io      : inout std_logic_vector(3 downto 0);
         push_io     : in std_logic_vector(3 downto 0);
         switch_io   : in std_logic_vector(3 downto 0);
         clk         : in std_logic;
         RED         : out std_logic_vector(4 downto 0);
         GREEN       : out std_logic_vector(5 downto 0);
         BLUE        : out std_logic_vector(4 downto 0);
         VGA_VS      : out std_logic;
         VGA_HS      : out std_logic;
         CAMERA_DATA : in std_logic_vector(7 downto 0);		
         CAMERA_XCLK : out std_logic;
         CAMERA_PCLK : in std_logic;
         CAMERA_HS   : in std_logic;
         CAMERA_VS   : in std_logic
         );
end system_top;

architecture STRUCTURE of system_top is

  component system is
    Port ( processing_system7_0_MIO          : inout std_logic_vector(53 downto 0);
           processing_system7_0_PS_SRSTB     : in std_logic;
           processing_system7_0_PS_CLK       : in std_logic;
           processing_system7_0_PS_PORB      : in std_logic;
           processing_system7_0_DDR_Clk      : inout std_logic;
           processing_system7_0_DDR_Clk_n    : inout std_logic;
           processing_system7_0_DDR_CKE      : inout std_logic;
           processing_system7_0_DDR_CS_n     : inout std_logic;
           processing_system7_0_DDR_RAS_n    : inout std_logic;
           processing_system7_0_DDR_CAS_n    : inout std_logic;
           processing_system7_0_DDR_WEB      : out std_logic;
           processing_system7_0_DDR_BankAddr : inout std_logic_vector(2 downto 0);
           processing_system7_0_DDR_Addr     : inout std_logic_vector(14 downto 0);
           processing_system7_0_DDR_ODT      : inout std_logic;
           processing_system7_0_DDR_DRSTB    : inout std_logic;
           processing_system7_0_DDR_DQ       : inout std_logic_vector(31 downto 0);
           processing_system7_0_DDR_DM       : inout std_logic_vector(3 downto 0);
           processing_system7_0_DDR_DQS      : inout std_logic_vector(3 downto 0);
           processing_system7_0_DDR_DQS_n    : inout std_logic_vector(3 downto 0);
           processing_system7_0_DDR_VRN      : inout std_logic;
           processing_system7_0_DDR_VRP      : inout std_logic;
           processing_system7_0_I2C0_SDA     : inout std_logic;
           processing_system7_0_I2C0_SCL     : inout std_logic);
  end component system;

  attribute BOX_TYPE : STRING;
  attribute BOX_TYPE of system : component is "user_black_box";
  
  component clk_pll
    Port ( CLK_IN1  : in STD_LOGIC;
           CLK_OUT1 : out STD_LOGIC;
           CLK_OUT2 : out STD_LOGIC;
           RESET    : in STD_LOGIC;
           LOCKED   : out STD_LOGIC);
  end component clk_pll;


  component VGA_generator
    Port ( clk        : in  STD_LOGIC;
           btn3       : in  STD_LOGIC;	
           Hsync      : out STD_LOGIC;
           Vsync      : out STD_LOGIC;
           addr       : out STD_LOGIC_VECTOR (16 downto 0);
           coord      : out coordonnee;
           activeArea : out boolean;
           reset      : out STD_LOGIC);
  end component VGA_generator;

  component Camera_Capture
    Port ( pclk     : in  STD_LOGIC;
    	   reset    : in  STD_LOGIC;
           href     : in  STD_LOGIC;
           vs_cam   : in  STD_LOGIC;
           data_in  : in  STD_LOGIC_VECTOR (7 downto 0);
           addr     : out STD_LOGIC_VECTOR (16 downto 0);
           data_out : out STD_LOGIC_VECTOR (15 downto 0);
           coord    : out coordonnee;
           we       : out STD_LOGIC_VECTOR(0 DOWNTO 0));
  end component Camera_Capture;

  --utilisée pour stockée l'image de la camera et la sortie de HOG
  component mem_lum
    Port ( clka  : in  std_logic;
           wea   : in  std_logic_vector (0  downto 0);
           addra : in  std_logic_vector (16 downto 0);
           dina  : in  std_logic_vector (7  downto 0);
           clkb  : in  std_logic;
           addrb : in  std_logic_vector (16 downto 0);
           doutb : out std_logic_vector (7  downto 0));
  end component mem_lum;

  component multiplexer_RGB is
    Port ( clk        : in  STD_LOGIC;
           sw0        : in  STD_LOGIC;	
           btn0       : in  STD_LOGIC;					
           btn1       : in  STD_LOGIC;
           btn2       : in  STD_LOGIC;
           coord      : in  coordonnee;
           data       : in  STD_LOGIC_VECTOR (15 downto 0);
           activeArea : in  boolean;
           Hsync      : in  STD_LOGIC;
           Vsync      : in  STD_LOGIC;
           VGA_hs     : out STD_LOGIC;
           VGA_vs     : out STD_LOGIC;
           VGA_r      : out STD_LOGIC_VECTOR (4 downto 0);
           VGA_g      : out STD_LOGIC_VECTOR (5 downto 0);
           VGA_b      : out STD_LOGIC_VECTOR (4 downto 0));
  end component multiplexer_RGB;


  component Main_HOG
    PORT( start                                : in  STD_LOGIC;
          done                                 : out STD_LOGIC;
          actived_rsc_z                        : in  STD_LOGIC;
          mode_rsc_z                           : out STD_LOGIC;
          actived_triosy_lz                    : out STD_LOGIC;
          mode_triosy_lz                       : out STD_LOGIC;
          mem_Ram_Data_triosy_lz               : out STD_LOGIC;
          mem_Ram_Hog_triosy_lz                : out STD_LOGIC;
          clk                                  : in  STD_LOGIC;
          rst                                  : in  STD_LOGIC;
          mem_Ram_Data_rsc_singleport_data_in  : out STD_LOGIC_VECTOR (7 DOWNTO 0);
          mem_Ram_Data_rsc_singleport_addr     : out STD_LOGIC_VECTOR (16 DOWNTO 0);
          mem_Ram_Data_rsc_singleport_re       : out STD_LOGIC;
          mem_Ram_Data_rsc_singleport_we       : out STD_LOGIC;
          mem_Ram_Data_rsc_singleport_data_out : in  STD_LOGIC_VECTOR (7 DOWNTO 0);
          mem_Ram_Hog_rsc_singleport_data_in   : out STD_LOGIC_VECTOR (7 DOWNTO 0);
          mem_Ram_Hog_rsc_singleport_addr      : out STD_LOGIC_VECTOR (16 DOWNTO 0);
          mem_Ram_Hog_rsc_singleport_re        : out STD_LOGIC;
          mem_Ram_Hog_rsc_singleport_we        : out STD_LOGIC;
          mem_Ram_Hog_rsc_singleport_data_out  : in  STD_LOGIC_VECTOR (7 DOWNTO 0)
          );
  end component;

  signal clk_VGA, pclk_cam : STD_LOGIC; 
  signal we,we_hog, we_hog_not : STD_LOGIC_VECTOR(0 DOWNTO 0);
  signal address_cam, address_VGA,address_hog_in, address_hog_out, addr_switch : STD_LOGIC_VECTOR (16 downto 0);
  signal address_cam_tmp, address_hog_in_tmp, address_hog_out_tmp, address_VGA_tmp : STD_LOGIC_VECTOR (16 downto 0);
  signal data_cam, data_VGA : STD_LOGIC_VECTOR (15 downto 0);
  signal coord_VGA, coord_cam : coordonnee;
  signal img_active : boolean;
  signal hs, vs : STD_LOGIC; 
  signal rst_VGA : STD_LOGIC; 
  signal CAMERA_DATA_q : STD_LOGIC_VECTOR (7 downto 0);
  signal CAMERA_HS_q, CAMERA_VS_q : STD_LOGIC;
  signal data_cam_8,data_hog_in,data_switch : std_logic_vector (7 downto 0);
  signal data_VGA_8,data_hog_out,data_hog_out_tmp,data_VGA_8s : std_logic_vector (7 downto 0);
  signal start, done : std_logic;
  
  --fonction permettant le réadressage 
  function map_addr (
    addr : std_logic_vector(16 downto 0) )
    return std_logic_vector is
    
    variable x,y      : integer range 0 to 1024;
    variable addr_res : integer range 0 to 2**17-1;
    variable res      : std_logic_vector(16 downto 0);
    
  begin 
    -- recupere les coordonnée
    x        := to_integer(unsigned(addr(8 downto 0)));
    y        := to_integer(unsigned(addr(16 downto 9)));
    --et les adapte
    addr_res := x+320*y;
    res      := std_logic_vector(to_unsigned(addr_res,17));
    return res;
  end map_addr;

  
begin
  -- changement d'adressage
  address_cam_tmp     <= map_addr(address_cam);
  address_hog_in_tmp  <= map_addr(address_hog_in);
  address_hog_out_tmp <= map_addr(address_hog_out);
  address_VGA_tmp     <= map_addr(address_VGA);
  data_hog_out_tmp    <= data_hog_out(7 downto 0);
  --necessaire pour intégrer le module Catapult C 
  we_hog_not          <= not(we_hog);


  
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
    Port map ( CLK_IN1  => clk,	        -- 125 MHz
               CLK_OUT1 => clk_VGA,	-- 24 MHz
               CLK_OUT2 => CAMERA_XCLK, -- 24 MHz
               RESET    => push_io(3),
               LOCKED   => led_io(0)
               );

  
  vga: VGA_generator
    Port map ( clk        => clk_VGA,
               btn3       => push_io(3),
               Hsync      => hs,
               Vsync      => vs,
               addr       => address_VGA,
               coord      => coord_VGA,
               activeArea => img_active,
               reset      => rst_VGA
               );

  sync_cam : process(CAMERA_PCLK)
  begin
    if rising_edge(CAMERA_PCLK) then
      CAMERA_DATA_q <= CAMERA_DATA ;
      CAMERA_HS_q   <= CAMERA_HS;
      CAMERA_VS_q   <= CAMERA_VS;
    end if;
  end process sync_cam;

  --module permettant le passage de l'image caméra couleur en niveau de gris
  rgb_to_gray : process(data_cam)
  begin
    data_cam_8 <= ("000" & data_cam(15 downto 11)) +
                  data_cam(10 downto 5)            +
                  data_cam(4  downto 0);
  end process rgb_to_gray;

  --module permettant de coder une nimage en niveau de grix vers un format VGA
  gray_to_rgb : process(data_VGA_8)
  begin
    data_VGA   <= data_VGA_8(6 downto 2) &
                  data_VGA_8(6 downto 1) &
                  data_VGA_8(6 downto 2);
   end process gray_to_rgb;
  
  --module de la caméra
  capture: Camera_Capture
    Port map ( pclk     => CAMERA_PCLK,
               reset    => rst_VGA,
               href     => CAMERA_HS_q,
               vs_cam   => CAMERA_VS_q,
               data_in  => CAMERA_DATA_q,
               addr     => address_cam,
               data_out => data_cam,
               coord    => coord_cam,
               we       => we
               );
    
  --mémoire en écrite par la caméra et lue soit par VGA soit par HOG
  ram1: mem_lum
    Port map ( clka  => CAMERA_PCLK,
               wea   => we,
               addra => address_cam_tmp,
               dina  => data_cam_8,
               
               clkb  => clk_VGA,
               addrb => addr_switch, 
               doutb => data_switch				
               );
    
  --mémoire en ecriture par HOG et lue par VGA quand HOG actif
  ram2: mem_lum
    Port map ( clka  => clk_VGA,
               wea   => we_hog_not,
               addra => address_hog_out_tmp,
               dina  => data_hog_out_tmp,
               
               clkb  => clk_VGA,
               addrb => address_VGA_tmp,
               doutb => data_VGA_8s
               );

  --process permettant de passé en mode "sans module HOG"
  --utilise la mémoire d'entrée de la caméra comme entrée du module VGA
  mem_mux : process(switch_io,
                    address_hog_in_tmp,
                    address_VGA_tmp,
                    data_switch, data_VGA_8s
                    )
  begin
    data_hog_in <= data_switch;
    
    if (switch_io(2) = '1') then
      led_io(2)   <= '1';
      addr_switch <= address_VGA_tmp;
      data_VGA_8  <= data_switch;
    else
      led_io(2)   <= '0';
      addr_switch <= address_hog_in_tmp;
      data_VGA_8  <= data_VGA_8s;
    end if;

  end process mem_mux;
  
  
  mux: multiplexer_RGB
    Port map ( clk        => clk_VGA,
               sw0        => switch_io(0),
               btn0       => push_io(0),
               btn1       => push_io(1),	
               btn2       => push_io(2),
               coord      => coord_VGA,
               data       => data_VGA,
               activeArea => img_active,
               Hsync      => hs,
               Vsync      => vs,
               VGA_hs     => VGA_HS,
               VGA_vs     => VGA_VS,
               VGA_r      => RED,
               VGA_g      => GREEN,
               VGA_b      => BLUE
               );

  --fsm permettant l'arrêt du module Catapult C HOG
  fsm_stat : process(clk_VGA)
    type T_fsm is ( S_Idle,  S_start, S_done);
    variable fsm_state : T_fsm;
    
  begin
    if rising_edge(clk_VGA) then
      if rst_VGA='1' then
        fsm_state := S_Idle;
        start     <= '0';
        led_io(3) <= '0';
      else
        start <= '0';
        case fsm_state is
          when S_Idle =>
            if switch_io(3)='1' then
              fsm_state := S_start;
            end if;
            
          when S_start =>
            start <= '1';
            if done='1' then
              fsm_state := S_done;
            end if;
          
          when S_done =>
            start     <= '0';
            fsm_state := S_Idle;

          when others => null;
        end case;
        
        led_io(3) <= start;

      end if;
    end if;
  end process fsm_stat;

  --module Catapult C HOG
  main: Main_HOG
    Port map ( --démarre le module Catapult C
               start                                => start,
               done                                 => done,
               --permet d'activer la sortie "recopie" ou "histogramme" 
               actived_rsc_z                        => switch_io(1),
               --indique quel mode est actif
               mode_rsc_z                           => led_io(1),
               actived_triosy_lz                    => open,
               mode_triosy_lz                       => open,
               mem_Ram_Data_triosy_lz               => open,
               mem_Ram_Hog_triosy_lz                => open,
               clk                                  => clk_VGA, 
               rst                                  => rst_VGA,
               --mémoire de lecture Catapult C
               mem_Ram_Data_rsc_singleport_data_in  => open,
               mem_Ram_Data_rsc_singleport_addr     => address_hog_in,
               mem_Ram_Data_rsc_singleport_re       => open,
               mem_Ram_Data_rsc_singleport_we       => open,
               mem_Ram_Data_rsc_singleport_data_out => data_hog_in,
               --mémoire d'écriture Catapult C
               mem_Ram_Hog_rsc_singleport_data_in   => data_hog_out,
               mem_Ram_Hog_rsc_singleport_addr      => address_hog_out,
               mem_Ram_Hog_rsc_singleport_re        => open,
               mem_Ram_Hog_rsc_singleport_we        => we_hog(0),
               mem_Ram_Hog_rsc_singleport_data_out  => data_hog_out
               );
  

end architecture STRUCTURE;

