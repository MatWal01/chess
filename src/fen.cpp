// #include <iostream>
// #include "gameLogic.h"


// std::string Position::returnFEN()
// {
//     // char emptySquares {'0'};

//     FEN.clear();
//     // for (int rank {7}; rank >= 0; rank--)
//     // {
//     //     for (size_t file {0}; file < 8; file++)
//     //     {
//     //         if (pieces.at(rank).at(file) != '\0')
//     //         {
//     //             if (emptySquares != '0')
//     //             {
//     //                 FEN.push_back(emptySquares);
//     //                 emptySquares = '0';
//     //             }
//     //             FEN.push_back(pieces.at(rank).at(file));
//     //         }
//     //         else
//     //         {
//     //             emptySquares++;
//     //         }
//     //     }
//     //     if (emptySquares != '0')
//     //     {
//     //         FEN.push_back(emptySquares);
//     //     }

//     //     FEN.push_back('/');

//     //     emptySquares = '0';
//     // }

//     // FEN.pop_back();         // remove last '/'
//     // FEN += ' ';

//     // FEN += tolower(tolower(onMove));
//     // FEN += ' ';

//     // bool noCastle {true};

//     // if (wKingside)
//     // {
//     //     FEN += 'K';
//     //     noCastle = false;
//     // }

//     // if (wQueenside)
//     // {
//     //     FEN += 'Q';
//     //     noCastle = false;
//     // }

//     // if (bKingside)
//     // {
//     //     FEN += 'k';
//     //     noCastle = false;
//     // }

//     // if (bQueenside)
//     // {
//     //     FEN += 'q';
//     //     noCastle = false;
//     // }

//     // if (noCastle)
//     // {
//     //     FEN += '-';
//     // }

//     // FEN += ' ';

//     // FEN += enpassant;

//     return FEN;
// }


// // sets a position 2D vector of chars from FEN
// void Position::setPosition(std::string FEN)
// {
//     this->FEN = FEN;
    
//     // size_t charCounter {0};
//     // int i {7};
//     // int j {0};
//     // char temp;

//     // // set pieces, skip '/' and numbers k times
//     // while (FEN.at(charCounter) != ' ')
//     // {
//     //     temp = FEN.at(charCounter);
//     //     if (temp - '0' > 0 && temp - '0' < 9)
//     //     {
//     //         temp = '0';
//     //     }
//     //     switch (temp)
//     //     {
//     //         case '/':
//     //             i--;
//     //             j = 0;
//     //             break;
//     //         case '0':
//     //             for (int k {0}; k < FEN.at(charCounter) - '0'; k++)
//     //             {
//     //                 pieces.at(i).at(j) = '\0';
//     //                 j++;
//     //             }
//     //             break;
//     //         default:
//     //             pieces.at(i).at(j) = temp;
//     //             j++;
//     //     }
//     //     charCounter++;
//     // }
//     // // skip whitespace
//     // charCounter++;

//     // if (FEN.at(charCounter) == 'w')
//     // {
//     //     onMove = 'W';
//     // }
//     // else
//     // {
//     //     onMove = 'b';
//     // }

//     // charCounter += 2;

//     // while (FEN.at(charCounter) != ' ')
//     // {
//     //     if (FEN.at(charCounter) == '-')
//     //     {
//     //         wKingside = false;
//     //         wQueenside = false;
//     //         bKingside = false;
//     //         bQueenside = false;
//     //         charCounter++;
//     //         break;
//     //     }

//     //     if (FEN.at(charCounter) == 'K')
//     //     {
//     //         wKingside = true;
//     //     }
//     //     else if (FEN.at(charCounter) == 'Q')
//     //     {
//     //         wQueenside = true;
//     //     }
//     //     else if (FEN.at(charCounter) == 'k')
//     //     {
//     //         bKingside = true;
//     //     }
//     //     else if (FEN.at(charCounter) == 'q')
//     //     {
//     //         bQueenside = true;
//     //     }

//     //     charCounter++;
//     // }
    
//     // charCounter++;
//     // // enpassant move
//     // if (FEN.at(charCounter) != '-')
//     // {
//     //     enpassant.at(0) = FEN.at(charCounter);
//     //     enpassant += FEN.at(charCounter + 1);

//     //     charCounter++;
//     // }
//     // charCounter++;
//     // // TODO: halfmoves counter

// }