#ifndef BLOCKT_H_INCLUDED
#define BLOCKT_H_INCLUDED
#include "BlockPiece.h"

class BlockT: public BlockPiece{
    public:
        BlockT();

        void Turn(int Block[20][10]);

};

#endif // BLOCKT_H_INCLUDED
