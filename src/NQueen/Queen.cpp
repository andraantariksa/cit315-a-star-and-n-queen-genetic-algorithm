#pragma once

#include <NQueen/Queen.hpp>
#include <cmath>

bool Queen::isConflicted(Queen q) const
{
    return (row == q.row
    || col == q.col
    || std::abs(row - q.row) == std::abs(col - q.col));
}