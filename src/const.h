#pragma once
#include <cstdint>

// boolean representation of a chessboard (1 - piece is present, 0 - is not)
// 2^0 is A1 square 2^63 is H8 square
typedef std::uint64_t bitboard;

// files and rank
constexpr bitboard AFILE                {0x0101010101010101};
constexpr bitboard BFILE                {0x0202020202020202};
constexpr bitboard CFILE                {0x0404040404040404};
constexpr bitboard DFILE                {0x0808080808080808};
constexpr bitboard EFILE                {0x1010101010101010};
constexpr bitboard FFILE                {0x2020202020202020};
constexpr bitboard GFILE                {0x4040404040404040};
constexpr bitboard HFILE                {0x8080808080808080};

constexpr bitboard FIRSTRANK            {0xFF};
constexpr bitboard SECONDRANK           {0xFF00};
constexpr bitboard THIRDRANK            {0xFF0000};
constexpr bitboard FOURTHRANK           {0xFF000000};
constexpr bitboard FIFTHRANK            {0xFF00000000};
constexpr bitboard SIXTHRANK            {0xFF0000000000};
constexpr bitboard SEVENTHRANK          {0xFF000000000000};
constexpr bitboard EIGHTRANK            {0xFF00000000000000};

// for checks
constexpr bitboard WCASTLEQUEENSIDE     {0x0E};
constexpr bitboard WCASTLEKINGSIDE      {0x60};
constexpr bitboard BCASTLEQUEENSIDE     {0x0E00000000000000};
constexpr bitboard BCASTLEKINGSIDE      {0x6000000000000000};

// rook position change while castling
constexpr bitboard WKINGSIDEROOKMOVE    {0x20};
constexpr bitboard WQUEENSIDEROOKMOVE   {0x08};
constexpr bitboard BKINGSIDEROOKMOVE    {0x2000000000000000};
constexpr bitboard BQUEENSIDEROOKMOVE   {0x0800000000000000};

// king position change while castling
constexpr bitboard WKINGSIDEKINGMOVE    {0x40};
constexpr bitboard WQUEENSIDEKINGMOVE   {0x04};
constexpr bitboard BKINGSIDEKINGMOVE    {0x4000000000000000};
constexpr bitboard BQUEENSIDEKINGMOVE   {0x0400000000000000};

// where the pieces are before castling
constexpr bitboard WKING                {0x10};
constexpr bitboard BKING                {0x1000000000000000};
constexpr bitboard WQUEENSIDEROOK       {0x01};
constexpr bitboard WKINGSIDEROOK        {0x80};
constexpr bitboard BQUEENSIDEROOK       {0x0100000000000000};
constexpr bitboard BKINGSIDEROOK        {0x8000000000000000};
