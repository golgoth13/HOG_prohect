-------------------------------------------------------------------------------
-- system_top.vhd 
-------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_UNSIGNED.all;

library UNISIM;
use UNISIM.VCOMPONENTS.ALL;

library work;
use work.packageVGA.all;

entity system_top is
  Port ( processing_system7_0_MIO :          inout std_logic_vector (53 downto 0);
         processing_system7_0_PS_SRSTB :     in    std_logic;
         processing_system7_0_PS_CLK :       in    std_logic;
         processing_system7_0_PS_PORB :      in    std_logic;
         processing_system7_0_DDR_Clk :      inout std_logic;
         processing_system7_0_DDR_Clk_n :    inout std_logic;
         processing_system7_0_DDR_CKE :      inout std_logic;
         processing_system7_0_DDR_CS_n :     inout std_logic;
         processing_system7_0_DDR_RAS_n :    inout std_logic;
         processing_system7_0_DDR_CAS_n :    inout std_logic;
         processing_system7_0_DDR_WEB :      out   std_logic;
         processing_system7_0_DDR_BankAddr : inout std_logic_vector (2  downto 0);
         processing_system7_0_DDR_Addr :     inout std_logic_vector (14 downto 0);
         processing_system7_0_DDR_ODT :      inout std_logic;
         processing_system7_0_DDR_DRSTB :    inout std_logic;
         processing_system7_0_DDR_DQ :       inout std_logic_vector (31 downto 0);
         processing_system7_0_DDR_DM :       inout std_logic_vector (3  downto 0);
         processing_system7_0_DDR_DQS :      inout std_logic_vector (3  downto 0);
         processing_system7_0_DDR_DQS_n :    inout std_logic_vector (3  downto 0);
         processing_system7_0_DDR_VRN :      inout std_logic;
         processing_system7_0_DDR_VRP :      inout std_logic;
         processing_system7_0_I2C0_SDA :     inout std_logic;
         processing_system7_0_I2C0_SCL :     inout std_logic;
         led_io :                            inout std_logic_vector (3  downto 0);
         push_io :                           in    std_logic_vector (3  downto 0);
         switch_io :                         in    std_logic_vector (3  downto 0);
         clk :                               in    std_logic;
         RED :                               out   std_logic_vector (4  downto 0);
         GREEN :                             out   std_logic_vector (5  downto 0);
         BLUE :                              out   std_logic_vector (4  downto 0);
         VGA_VS :                            out   std_logic;
         VGA_HS :                            out   std_logic;
         CAMERA_DATA :                       in    std_logic_vector (7  downto 0);
         CAMERA_XCLK :                       out   std_logic;
         CAMERA_PCLK :                       in    std_logic;
         CAMERA_HS :                         in    std_logic;
         CAMERA_VS :                         in    std_logic);
end system_top;

architecture STRUCTURE of system_top is

  component system is
    Port ( processing_system7_0_MIO :          inout std_logic_vector (53 downto 0);
           processing_system7_0_PS_SRSTB :     in    std_logic;
           processing_system7_0_PS_CLK :       in    std_logic;
           processing_system7_0_PS_PORB :      in    std_logic;
           processing_system7_0_DDR_Clk :      inout std_logic;
           processing_system7_0_DDR_Clk_n :    inout std_logic;
           processing_system7_0_DDR_CKE :      inout std_logic;
           processing_system7_0_DDR_CS_n :     inout std_logic;
           processing_system7_0_DDR_RAS_n :    inout std_logic;
           processing_system7_0_DDR_CAS_n :    inout std_logic;
           processing_system7_0_DDR_WEB :      out   std_logic;
           processing_system7_0_DDR_BankAddr : inout std_logic_vector (2  downto 0);
           processing_system7_0_DDR_Addr :     inout std_logic_vector (14 downto 0);
           processing_system7_0_DDR_ODT :      inout std_logic;
           processing_system7_0_DDR_DRSTB :    inout std_logic;
           processing_system7_0_DDR_DQ :       inout std_logic_vector (31 downto 0);
           processing_system7_0_DDR_DM :       inout std_logic_vector (3  downto 0);
           processing_system7_0_DDR_DQS :      inout std_logic_vector (3  downto 0);
           processing_system7_0_DDR_DQS_n :    inout std_logic_vector (3  downto 0);
           processing_system7_0_DDR_VRN :      inout std_logic;
           processing_system7_0_DDR_VRP :      inout std_logic;
           processing_system7_0_I2C0_SDA :     inout std_logic;
           processing_system7_0_I2C0_SCL :     inout std_logic);
  end component system;

  attribute BOX_TYPE           : STRING;
  attribute BOX_TYPE of system : component is "user_black_box";
  
  component clk_pll
    Port ( CLK_IN1 :  in  std_logic;
           CLK_OUT1 : out std_logic;
           CLK_OUT2 : out std_logic;
           RESET :    in  std_logic;
           LOCKED :   out std_logic);
  end component clk_pll;

  component VGA_generator
    Port ( clk :        in  std_logic;
           btn3 :       in  std_logic;
           Hsync :      out std_logic;
           Vsync :      out std_logic;
           addr :       out std_logic_vector (16 downto 0);
           coord :      out coordonnee;
           activeArea : out boolean;
           reset :      out std_logic);
  end component VGA_generator;

  component Camera_Capture
    Port ( pclk :     in  std_logic;
    	   reset :    in  std_logic;
           href :     in  std_logic;
           vs_cam :   in  std_logic;
           data_in :  in  std_logic_vector (7  downto 0);
           addr :     out std_logic_vector (16 downto 0);
           data_out : out std_logic_vector (15 downto 0);
           coord :    out coordonnee;
           we :       out std_logic_vector (0  downto 0));
  end component Camera_Capture;

  --memoire image
  component mem_lum
    Port ( clka :  in  std_logic;
           wea :   in  std_logic_vector (0  downto 0);
           addra : in  std_logic_vector (16 downto 0);
           dina :  in  std_logic_vector (7  downto 0);
           clkb :  in  std_logic;
           addrb : in  std_logic_vector (16 downto 0);
           doutb : out std_logic_vector (7  downto 0));
  end component mem_lum;

  --memoire sortie
  component mem_hog
    Port ( clka :  in  std_logic;
           wea :   in  std_logic_vector (0  downto 0);
           addra : in  std_logic_vector (16 downto 0);
           dina :  in  std_logic_vector (7  downto 0);
           clkb :  in  std_logic;
           addrb : in  std_logic_vector (16 downto 0);
           doutb : out std_logic_vector (7  downto 0));
  end component mem_hog;

  --main
  component Main_HOG
    PORT( actived_rsc_z :                        in  std_logic;
          clk :                                  in  std_logic;
          rst :                                  in  std_logic;
          mode_rsc_z :                           out std_logic;
          mem_Ram_Data_rsc_singleport_data_in :  out std_logic_vector (7  downto 0);
          mem_Ram_Data_rsc_singleport_addr :     out std_logic_vector (16 downto 0);
          mem_Ram_Data_rsc_singleport_re :       out std_logic;
          mem_Ram_Data_rsc_singleport_we :       out std_logic;
          mem_Ram_Data_rsc_singleport_data_out : in  std_logic_vector (7  downto 0);
          mem_Ram_Hog_rsc_singleport_data_in :   out std_logic_vector (7  downto 0);
          mem_Ram_Hog_rsc_singleport_addr :      out std_logic_vector (16 downto 0);
          mem_Ram_Hog_rsc_singleport_re :        out std_logic;
          mem_Ram_Hog_rsc_singleport_we :        out std_logic;
          mem_Ram_Hog_rsc_singleport_data_out :  in  std_logic_vector (7  downto 0));
  end component Main_HOG;
  

  component multiplexer_RGB is
    Port ( clk :        in  std_logic;
           sw0 :        in  std_logic;	
           btn0 :       in  std_logic;					
           btn1 :       in  std_logic;
           btn2 :       in  std_logic;
           coord :      in  coordonnee;
           data  :      in  std_logic_vector (15 downto 0);
           activeArea : in  boolean;
           Hsync :      in  std_logic;
           Vsync :      in  std_logic;
           VGA_hs :     out std_logic;
           VGA_vs :     out std_logic;
           VGA_r :      out std_logic_vector (4  downto 0);
           VGA_g :      out std_logic_vector (5  downto 0);
           VGA_b :      out std_logic_vector (4  downto 0));
  end component multiplexer_RGB;

  signal clk_VGA            : std_logic; 
  signal we                 : std_logic_vector (0  downto 0);
  signal we_h               : std_logic_vector (0  downto 0);
  signal address_cam        : std_logic_vector (16 downto 0);
  signal address_VGA        : std_logic_vector (16 downto 0);
  signal address_mem_lum    : std_logic_vector (16 downto 0);
  signal address_mem_hog    : std_logic_vector (16 downto 0);
  signal data_cam, data_VGA : std_logic_vector (15 downto 0);
  signal data_cam_8         : std_logic_vector (7  downto 0);
  signal data_VGA_8         : std_logic_vector (7  downto 0);
  signal data_lum           : std_logic_vector (7  downto 0);
  signal data_hog           : std_logic_vector (7  downto 0);
  signal coord_VGA          : coordonnee;
  signal coord_cam          : coordonnee;
  signal img_active         : boolean;
  signal hs                 : std_logic;
  signal vs                 : std_logic; 
  signal rst_VGA            : std_logic; 
  signal CAMERA_DATA_q      : std_logic_vector (7  downto 0);
  signal CAMERA_HS_q        : std_logic;
  signal CAMERA_VS_q        : std_logic;

begin

  led_io(3) <= '1';
  
  rgb_to_gray : process(data_cam)
  begin
    data_cam_8 <= ("000" & data_cam(15 downto 11)) +
                  data_cam(10 downto 5)  +
                  data_cam(4  downto 0);
  end process rgb_to_gray;

  gray_to_rgb : process(data_VGA_8)
  begin
    data_VGA   <= data_VGA_8(6 downto 2) &
                  data_VGA_8(6 downto 1) &
                  data_VGA_8(6 downto 2);
  end process gray_to_rgb;
  
  system_i: system
    Port map ( processing_system7_0_MIO          => processing_system7_0_MIO,
               processing_system7_0_PS_SRSTB     => processing_system7_0_PS_SRSTB,
               processing_system7_0_PS_CLK       => processing_system7_0_PS_CLK,
               processing_system7_0_PS_PORB      => processing_system7_0_PS_PORB,
               processing_system7_0_DDR_Clk      => processing_system7_0_DDR_Clk,
               processing_system7_0_DDR_Clk_n    => processing_system7_0_DDR_Clk_n,
               processing_system7_0_DDR_CKE      => processing_system7_0_DDR_CKE,
               processing_system7_0_DDR_CS_n     => processing_system7_0_DDR_CS_n,
               processing_system7_0_DDR_RAS_n    => processing_system7_0_DDR_RAS_n,
               processing_system7_0_DDR_CAS_n    => processing_system7_0_DDR_CAS_n,
               processing_system7_0_DDR_WEB      => processing_system7_0_DDR_WEB,
               processing_system7_0_DDR_BankAddr => processing_system7_0_DDR_BankAddr,
               processing_system7_0_DDR_Addr     => processing_system7_0_DDR_Addr,
               processing_system7_0_DDR_ODT      => processing_system7_0_DDR_ODT,
               processing_system7_0_DDR_DRSTB    => processing_system7_0_DDR_DRSTB,
               processing_system7_0_DDR_DQ       => processing_system7_0_DDR_DQ,
               processing_system7_0_DDR_DM       => processing_system7_0_DDR_DM,
               processing_system7_0_DDR_DQS      => processing_system7_0_DDR_DQS,
               processing_system7_0_DDR_DQS_n    => processing_system7_0_DDR_DQS_n,
               processing_system7_0_DDR_VRN      => processing_system7_0_DDR_VRN,
               processing_system7_0_DDR_VRP      => processing_system7_0_DDR_VRP,
               processing_system7_0_I2C0_SDA     => processing_system7_0_I2C0_SDA,
               processing_system7_0_I2C0_SCL     => processing_system7_0_I2C0_SCL );

  pll: clk_pll
    Port map ( CLK_IN1  => clk,	        -- 125 MHz
               CLK_OUT1 => clk_VGA,	-- 24 MHz
               CLK_OUT2 => CAMERA_XCLK, -- 24 MHz
               RESET    => push_io(3),
               LOCKED   => led_io(0) );
  

  sync_cam : process(CAMERA_PCLK)
  begin
    if rising_edge(CAMERA_PCLK) then
      CAMERA_DATA_q  <= CAMERA_DATA ;
      CAMERA_HS_q    <= CAMERA_HS;
      CAMERA_VS_q    <= CAMERA_VS;
    end if;
  end process sync_cam;
  
  vga: VGA_generator
    Port map ( clk        => clk_VGA,
               btn3       => push_io(3),
               Hsync      => hs,
               Vsync      => vs,
               addr       => address_VGA,
               coord      => coord_VGA,
               activeArea => img_active,
               reset      => rst_VGA );

  capture: Camera_Capture
    Port map ( pclk     => CAMERA_PCLK,
               reset    => rst_VGA,
               href     => CAMERA_HS_q,
               vs_cam   => CAMERA_VS_q,
               data_in  => CAMERA_DATA_q,
               addr     => address_cam,
               data_out => data_cam,
               coord    => coord_cam,
               we       => we );
  
  ram1: mem_lum
    Port map ( clka  => CAMERA_PCLK,
               wea   => we,
               addra => address_cam,
               dina  => data_cam_8,
               clkb  => CAMERA_PCLK, --clk_VGA,
               addrb => address_mem_lum,
               doutb => data_lum
               );

  ram2: mem_hog
    Port map ( clka  => CAMERA_PCLK, --clk_VGA,
               wea   => we_h,
               addra => address_mem_hog,
               dina  => data_hog,
               clkb  => clk_VGA,
               addrb => address_VGA,
               doutb => data_VGA_8
               );

  
  main: Main_HOG
    Port map( actived_rsc_z                        => switch_io(1), 
              clk                                  => clk_VGA,
              rst                                  => rst_VGA,
              mode_rsc_z                           => led_io(1),
              mem_Ram_Data_rsc_singleport_data_in  => open,
              mem_Ram_Data_rsc_singleport_addr     => address_mem_lum,
              mem_Ram_Data_rsc_singleport_re       => open,
              mem_Ram_Data_rsc_singleport_we       => open,
              mem_Ram_Data_rsc_singleport_data_out => data_lum,
              mem_Ram_Hog_rsc_singleport_data_in   => data_hog,
              mem_Ram_Hog_rsc_singleport_re        => open,
              mem_Ram_Hog_rsc_singleport_addr      => address_mem_hog,
              mem_Ram_Hog_rsc_singleport_data_out  => "00000000",
              mem_Ram_Hog_rsc_singleport_we        =>  we_h(0) );
  
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
               VGA_b      => BLUE );

end architecture STRUCTURE;

