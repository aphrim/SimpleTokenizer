#ifndef chunkh
#define chunkh
#include <vector>

#include "token.hpp"

struct Chunk{
	std::vector<Token*> tokens;
};
#endif
