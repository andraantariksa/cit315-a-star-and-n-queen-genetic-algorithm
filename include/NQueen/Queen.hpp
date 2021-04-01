#pragma once

class Queen
{
public:
    int row, col;
    Queen(int r, int c) : row(r), col(c)
    {
    }

    [[nodiscard]]
    bool isConflicted(Queen q) const;
};
