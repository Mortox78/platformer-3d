#pragma once

namespace Core
{
    namespace Maths
    {
        class Range
        {
            public:
                Range(){}
                ~Range(){}

                float min = 0.f;
                float max = 0.f;

                void AddValue(const float& valueToAdd);

                static bool IsRangesInterfere(const Range& range1, const Range& range2);
        };
    }
}