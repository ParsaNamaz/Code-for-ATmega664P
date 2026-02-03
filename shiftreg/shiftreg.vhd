library ieee;
use ieee.std_logic_1164.all;
entity shiftreg is
  port (
    clk_i       : in    std_logic;                          -- input
    res_n       : in    std_logic;                          -- input
    ena_i       : in    std_logic;                          -- input
    ser_in_i    : in    std_logic;                          -- input
    par_out_o   : out   std_logic_vector(7 downto 0)        -- output
  );
end shiftreg;

architecture rtl of shiftreg is

  -- enter signal declarations here
  signal shiftreg : std_logic_vector(7 downto 0);

begin

  shift_p: process(clk_i, res_n)
  begin
    if (res_n = '0') then
      shiftreg <= (others => '0');
    elsif (clk_i'event and clk_i = '1') then
      if (ena_i = '1') then
        shiftreg <= ser_in_i & shiftreg(7 downto 1); 
	--for left shift:
	--shiftreg <= shiftreg(6 downto 0) & ser_in_i;
      end if;
    end if;
  end process;

  par_out_o <= shiftreg;

end rtl;     -- of shiftreg


