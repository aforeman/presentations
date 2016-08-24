/// Section 6 - Multicolor Sprites

///
/// Starting
///


#include <cstdint>

constexpr uint8_t  SPRITE_STARTING_BANK = 192;


namespace {

  volatile uint8_t &memory(const uint16_t loc)
  {
    return *reinterpret_cast<uint8_t *>(loc);
  }

  void write_pixel(uint16_t)
  {
  }


  template<typename D1, typename D2, typename D3, typename D4, typename D5, typename D6, typename D7, typename D8, typename ...  D >
  void write_pixel(uint16_t loc, D1 d1, D2 d2, D3 d3, D4 d4, D5 d5, D6 d6, D7 d7, D8 d8, D ... d)
  {
    memory(loc) = (d1 << 7) | (d2 << 6) | (d3 << 5) | (d4 << 4) | (d5 << 3) | (d6 << 2) | (d7 << 1) | d8;
    write_pixel(loc + 1, d...);
  }


  template<typename ... D>
  void make_sprite(uint8_t memory_loc, D ... d)
  {
    write_pixel((SPRITE_STARTING_BANK + memory_loc) * 64, d...);
  }
  
}

int main()
{
  make_sprite(1,
              0,0,0,0,0,2,2,0,0,0,0,0,
              0,0,0,0,0,2,2,0,0,0,0,0,
              0,0,0,0,0,2,2,0,0,0,0,0,
              0,0,0,0,0,2,2,0,0,0,0,0,
              0,0,0,0,0,2,2,0,0,0,0,0,
              0,0,0,0,0,2,2,0,0,0,0,0,
              0,0,0,0,0,2,2,0,0,0,0,0,
              0,0,0,0,0,2,2,0,0,0,0,0,
              0,0,0,0,0,2,2,0,0,0,0,0,
              0,0,0,0,0,2,2,0,0,0,0,0,
              0,0,0,0,0,2,2,0,0,0,0,0,
              0,0,0,0,0,2,2,0,0,0,0,0,
              0,0,0,0,0,2,2,0,0,0,0,0,
              0,0,0,0,0,2,2,0,0,0,0,0,
              0,0,0,0,0,2,2,0,0,0,0,0,
              0,0,0,0,0,2,2,0,0,0,0,0,
              0,0,0,0,0,3,3,0,0,0,0,0,
              0,0,0,0,0,1,1,0,0,0,0,0,
              0,0,0,0,0,3,3,0,0,0,0,0,
              0,0,0,0,0,1,1,0,0,0,0,0,
              0,0,0,0,0,3,3,0,0,0,0,0
             );
}





///
/// Final code
///


#include <cstdint>
#include <array>
#include <utility>
#include <algorithm>

constexpr uint8_t  SPRITE_STARTING_BANK = 192;


namespace {

volatile uint8_t &memory(const uint16_t loc)
{
  return *reinterpret_cast<uint8_t *>(loc);
}

void write_multi_color_pixel(uint16_t)
{
}

void write_pixel(uint16_t)
{
}


template<typename D1, typename D2, typename D3, typename D4, typename ...  D >
  void write_multi_color_pixel(uint16_t loc, D1 d1, D2 d2, D3 d3, D4 d4, D ... d)
{
  memory(loc) = (d1 << 6) | (d2 << 4) | (d3 << 2) | d4;
  write_multi_color_pixel(loc + 1, d...);
}

template<typename D1, typename D2, typename D3, typename D4, typename D5, typename D6, typename D7, typename D8, typename ...  D >
  void write_pixel(uint16_t loc, D1 d1, D2 d2, D3 d3, D4 d4, D5 d5, D6 d6, D7 d7, D8 d8, D ... d)
{
  memory(loc) = (d1 << 7) | (d2 << 6) | (d3 << 5) | (d4 << 4) | (d5 << 3) | (d6 << 2) | (d7 << 1) | d8;
  write_pixel(loc + 1, d...);
}


template<typename ... D>
  void make_sprite(uint8_t memory_loc, D ... d)
{
  if constexpr (sizeof...(d) == 12 * 21) {
    write_multi_color_pixel((SPRITE_STARTING_BANK + memory_loc) * 64, d...);
  } else {
    write_pixel((SPRITE_STARTING_BANK + memory_loc) * 64, d...);
  }
}
  
}

int main()
{  
  make_sprite(1,
              0,0,0,0,0,2,2,0,0,0,0,0,
              0,0,0,0,0,2,2,0,0,0,0,0,
              0,0,0,0,0,2,2,0,0,0,0,0,
              0,0,0,0,0,2,2,0,0,0,0,0,
              0,0,0,0,0,2,2,0,0,0,0,0,
              0,0,0,0,0,2,2,0,0,0,0,0,
              0,0,0,0,0,2,2,0,0,0,0,0,
              0,0,0,0,0,2,2,0,0,0,0,0,
              0,0,0,0,0,2,2,0,0,0,0,0,
              0,0,0,0,0,2,2,0,0,0,0,0,
              0,0,0,0,0,2,2,0,0,0,0,0,
              0,0,0,0,0,2,2,0,0,0,0,0,
              0,0,0,0,0,2,2,0,0,0,0,0,
              0,0,0,0,0,2,2,0,0,0,0,0,
              0,0,0,0,0,2,2,0,0,0,0,0,
              0,0,0,0,0,2,2,0,0,0,0,0,
              0,0,0,0,0,3,3,0,0,0,0,0,
              0,0,0,0,0,1,1,0,0,0,0,0,
              0,0,0,0,0,3,3,0,0,0,0,0,
              0,0,0,0,0,1,1,0,0,0,0,0,
              0,0,0,0,0,3,3,0,0,0,0,0
             );




}



