#include <iostream> //std::cout
#include <fstream>  //std::ifstream
#include <string>   //std::string
#include <vector>   //std::vector

typedef enum direction {nomove, u, d, l, r} direction;

direction next_move(std::vector< std::string >& lines, int row, int col, direction dir) {
    switch( dir ) {       // preferred direction
    case u:
        if ( dir != d && row > 0 && lines[ row-1 ][ col ] != ' ') 
            return u;
    case d:
        if (dir != u && row < lines.size() - 1 && lines[ row+1 ][ col ] != ' ') 
            return d;
    case r:
        if (dir != l && col < lines[ row ].length() - 1 && lines[ row ][ col + 1 ] != ' ') 
            return r;
    case l:
        if (dir != r && col > 0 && lines[ row ][ col - 1 ] != ' ') 
            return l;
        if (dir != d && row > 0 && lines[ row - 1 ][ col ] != ' ') 
            return u;        // mop up any corners
        if (dir != u && row < lines.size() - 1 && lines[ row + 1 ][ col ] != ' ') 
            return d;
        if (dir != l && col < lines[ row ].length() - 1 && lines[ row ][ col + 1 ] != ' ') 
            return r;
    }
    return nomove;
}

std::string follow(std::vector< std::string >& lines, int& steps) {
    std::string letters;
    int row = 0;
    int col = 0;
    while (lines[ row ][ col ] != '|') 
        col++;         // find starting position
    direction dir = d;
    while (dir != nomove) {
        steps++;
        dir = next_move(lines, row, col, dir);
        switch( dir ) {
            case d: 
                row++; 
                break;
            case u: 
                row--; 
                break;
            case r: 
                col++; 
                break;
            case l: 
                col--; 
                break;
            case nomove:
                std::cout << "STUCK at row: " << row << " col: " << col << " in step: " << steps << std::endl;
        }
        if (lines[ row ][ col ] >= 'A' && lines[ row ][ col ] <= 'Z' && dir != nomove)
            letters+=lines[ row ][ col ];
    }
    return letters;
}

int main()
{
    std::vector< std::string > lines;
    std::ifstream ifs("puzzle_input",std::ifstream::in);
    std::string l;
    while (getline( ifs, l )) {
        lines.push_back( l );
        std::cout << l << std::endl;
    }
    int steps = 0;
    std::string letters = follow( lines, steps );
    std::cout << letters << std::endl;
    return 0;
}