#include "common.h"

enum eOVERLAP_TYPE
{
    OT_NONE,
    OT_OVERLAP,
    OT_COVER,
};

struct Rect
{
public:
    int X;
    int Y;
    int W;
    int H;

public:
    Rect(int X = 0, int Y = 0, int W = 0, int H = 0)
        : X(X), Y(Y), W(W), H(H){};
    Rect(const Rect &R) = default;
    ~Rect(){};

    eOVERLAP_TYPE iHasOverlap(const Rect &R) const
    {
        if (R.X > (X + W))
        {
            return OT_NONE;
        }
        if ((R.X + R.W) < X)
        {
            return OT_NONE;
        }
        if (R.Y > (Y + H))
        {
            return OT_NONE;
        }
        if ((R.Y + H) < Y)
        {
            return OT_NONE;
        }

        return OT_OVERLAP;
    }

    Rect iCalcOverlapRect(const Rect &R) const
    {
        Rect Overlap;

        if (iHasOverlap(R) != OT_NONE)
        {
        }

        return Overlap;
    }

    int iCalcSurface() const
    {
        return W * H;
    }
};

int main()
{
    vector<Rect> DataSet;

    while (true)
    {
        char Str[128];
        cin.getline(Str, 128);
        const string strItem = Str;

        if (strItem.empty())
        {
            break;
        }
    }

    for (const Rect &Instance : DataSet)
    {
    }

    return 0;
}